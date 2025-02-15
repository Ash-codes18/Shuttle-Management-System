#include "ShuttleSystem.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

void ShuttleSystem::addRoute(const Route &route)
{
    routes.push_back(route);
}

void ShuttleSystem::removeRoute(const std::string &routeName)
{
    routes.erase(std::remove_if(routes.begin(), routes.end(),
                                [&routeName](const Route &route)
                                { return route.getRouteName() == routeName; }),
                 routes.end());
}

Route *ShuttleSystem::findRoute(const std::string &routeName)
{
    for (auto &route : routes)
    {
        if (route.getRouteName() == routeName)
        {
            return &route;
        }
    }
    return nullptr;
}

void ShuttleSystem::displayAllRoutes() const
{
    for (const auto &route : routes)
    {
        route.displayRoute();
        std::cout << "---------------------" << std::endl;
    }
}

void ShuttleSystem::suggestOptimalRoutes() const
{
    if (routes.empty())
    {
        std::cout << "No routes available to suggest optimal routes." << std::endl;
        return;
    }

    std::cout << "===== Optimal Route Suggestions =====" << std::endl;

    // Sort routes based on peak hours and demand
    std::vector<Route> sortedRoutes = routes;
    std::sort(sortedRoutes.begin(), sortedRoutes.end(), [](const Route &a, const Route &b)
              {
        // Prioritize routes with higher demand and peak hours
        return a.getPeakHours() > b.getPeakHours(); });

    for (const auto &route : sortedRoutes)
    {
        std::cout << "Route: " << route.getRouteName() << std::endl;
        std::cout << "Peak Hours: " << route.getPeakHours() << std::endl;
        std::cout << "Class Schedule: " << route.getClassSchedule() << std::endl;
        std::cout << "Stops:" << std::endl;
        for (const auto &stop : route.getStops())
        {
            std::cout << "  - " << stop.getStopName() << " (Demand: " << stop.getDemandLevel() << ")" << std::endl;
        }
        std::cout << "---------------------" << std::endl;
    }
}

std::vector<Route> &ShuttleSystem::getAllRoutes()
{
    return routes;
}

void ShuttleSystem::saveRoutesToFile() const
{
    std::ofstream file(routeFile);
    if (file.is_open())
    {
        for (const auto &route : routes)
        {
            file << route.getRouteName() << ","
                 << route.getPeakHours() << ","
                 << route.getClassSchedule() << "\n";
            for (const auto &stop : route.getStops())
            {
                file << stop.getStopName() << ","
                     << stop.getDemandLevel() << "\n";
            }
            file << "---\n"; 
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to save routes to file!" << std::endl;
    }
}

void ShuttleSystem::loadRoutesFromFile()
{
    std::ifstream file(routeFile);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line == "---")
            {
                continue; 
            }

            std::stringstream ss(line);
            std::string routeName, peakHours, classSchedule;
            std::getline(ss, routeName, ',');
            std::getline(ss, peakHours, ',');
            std::getline(ss, classSchedule, ',');

            Route newRoute(routeName, peakHours, classSchedule);

            // Read stops
            while (std::getline(file, line))
            {
                if (line == "---")
                {
                    break; 
                }

                std::stringstream ssStop(line);
                std::string stopName;
                int demandLevel;
                std::getline(ssStop, stopName, ',');
                ssStop >> demandLevel;

                newRoute.addStop(Stop(stopName, demandLevel));
            }

            routes.push_back(newRoute);
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to load routes from file!" << std::endl;
    }
}