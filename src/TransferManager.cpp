#include "TransferManager.h"
#include "Wallet.h"
#include <sstream>
#include <iostream>
#include <ctime>

TransferManager::TransferManager(ShuttleSystem *shuttleSystem) : shuttleSystem(shuttleSystem) {}

std::string TransferManager::suggestTransferPlan(const std::string &originStop, const std::string &destinationStop)
{
    auto &routes = shuttleSystem->getAllRoutes();

    for (const auto &route : routes)
    {
        if (route.hasStop(originStop) && route.hasStop(destinationStop))
        {
            int originIndex = route.getStopIndex(originStop);
            int destIndex = route.getStopIndex(destinationStop);
            if (originIndex < destIndex)
            {
                std::ostringstream oss;
                oss << "Direct route available on " << route.getRouteName()
                    << ". Estimated travel time: 25 minutes.";
                return oss.str();
            }
        }
    }

    for (const auto &firstRoute : routes)
    {
        if (firstRoute.hasStop(originStop))
        {
            int originIndex = firstRoute.getStopIndex(originStop);
            std::vector<Stop> stops = firstRoute.getStops();
            // Look for a potential transfer stop on firstRoute.
            for (size_t i = originIndex + 1; i < stops.size(); i++)
            {
                std::string transferStop = stops[i].getStopName();
                // Check if a different route offers a connection from the transfer stop to the destination.
                for (const auto &secondRoute : routes)
                {
                    if (secondRoute.getRouteName() == firstRoute.getRouteName())
                        continue; 
                    if (secondRoute.hasStop(transferStop) && secondRoute.hasStop(destinationStop))
                    {
                        int transferIndex = secondRoute.getStopIndex(transferStop);
                        int destIndex = secondRoute.getStopIndex(destinationStop);
                        if (transferIndex < destIndex)
                        {
                            std::ostringstream oss;
                            oss << "Transfer plan: Take " << firstRoute.getRouteName()
                                << " from " << originStop << " to " << transferStop
                                << ", then transfer to " << secondRoute.getRouteName()
                                << " from " << transferStop << " to " << destinationStop
                                << ". Estimated travel time: 30 minutes (includes approximately 5 minutes waiting time).";
                            return oss.str();
                        }
                    }
                }
            }
        }
    }

    return "No transfer plan available for the selected stops.";
}


bool TransferManager::bookMultiLegJourney(Student &student, const std::string &originStop, const std::string &destinationStop)
{
    double fare = 5.0;
    if (student.getWalletBalance() < fare)
    {
        std::cout << "Insufficient funds for a multi-leg journey." << std::endl;
        return false;
    }
    
    Wallet::deductFunds(student, fare);
    std::cout << "Multi-leg journey booked from " << originStop << " to " << destinationStop
              << " with a single fare deduction of " << fare << " points." << std::endl;
    return true;
}