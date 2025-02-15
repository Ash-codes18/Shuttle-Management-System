#include "BookingManager.h"
#include "Wallet.h"
#include "Route.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <map>

// Helper: Calculate fare using peak hour logic.
double BookingManager::calculateCurrentFare() const
{
    std::time_t now = std::time(nullptr);
    std::tm *localTime = std::localtime(&now);
    int currentHour = localTime->tm_hour;
    int currentMinute = localTime->tm_min;

    bool isMorningPeak = (currentHour == 7) || (currentHour == 8) || (currentHour == 9 && currentMinute == 0);
    bool isEveningPeak = (currentHour == 17) || (currentHour == 18) || (currentHour == 19 && currentMinute == 0);

    return (isMorningPeak || isEveningPeak) ? 10.0 : 5.0;
}

BookingManager::BookingManager(ShuttleSystem *shuttleSystem)
    : shuttleSystem(shuttleSystem)
{
    loadBookings();
}

void BookingManager::showAvailableRoutes() const
{
    std::cout << "\nAvailable Routes:\n"
              << std::endl;
    shuttleSystem->displayAllRoutes();
}

bool BookingManager::bookTrip(Student &student, const std::string &routeName,
                              const std::string &startStop, const std::string &endStop)
{
    // Verify that the chosen route exists.
    Route *route = shuttleSystem->findRoute(routeName);
    if (!route)
    {
        std::cout << "Route not found!" << std::endl;
        return false;
    }

    double fare = calculateCurrentFare();
    if (student.getWalletBalance() < fare)
    {
        std::cout << "Insufficient funds! Please recharge your wallet." << std::endl;
        return false;
    }

    Wallet::deductFunds(student, fare);
    Booking newBooking(student.getEmail(), routeName, fare, startStop, endStop);
    bookings.push_back(newBooking);

    logEvent("Booking made by " + student.getEmail() + " for route: " + routeName +
             " from " + startStop + " to " + endStop +
             " with fare: " + std::to_string(fare));
    std::cout << "Booking successful for route: " << routeName << std::endl;

    saveBookings();
    return true;
}

bool BookingManager::cancelBooking(Student &student, bool isLastMinute)
{
    for (auto &booking : bookings)
    {
        if (booking.getStudentEmail() == student.getEmail() && booking.isActive())
        {
            booking.cancel();
            double refundAmount = booking.getFare();
            if (isLastMinute)
            {
                refundAmount *= 0.5;
            }
            student.addFunds(refundAmount);
            logEvent("Booking cancelled by " + student.getEmail() + " for route: " + booking.getRouteName() +
                     " from " + booking.getStartStop() + " to " + booking.getEndStop() +
                     ". Refund amount: " + std::to_string(refundAmount));
            std::cout << "Booking cancelled. Refund amount: " << refundAmount << std::endl;

            saveBookings();
            return true;
        }
    }
    std::cout << "No active booking found for cancellation." << std::endl;
    return false;
}

void BookingManager::displayTripHistory(const Student &student) const
{
    std::cout << "\n----- Trip History for " << student.getEmail() << " -----\n"
              << std::endl;
    for (const auto &booking : bookings)
    {
        if (booking.getStudentEmail() == student.getEmail())
        {
            std::time_t bookingTime = booking.getBookingTime();
            std::tm *timeInfo = std::localtime(&bookingTime); // Fixed: use local variable to take its address.
            char buffer[80];
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
            std::cout << "Date & Time : " << buffer << "\n"
                      << "Route       : " << booking.getRouteName() << "\n"
                      << "Start Stop  : " << booking.getStartStop() << "\n"
                      << "End Stop    : " << booking.getEndStop() << "\n"
                      << "Fare        : " << booking.getFare() << "\n"
                      << "Status      : " << (booking.isActive() ? "Active" : "Cancelled") << "\n"
                      << "---------------------------------------\n";
        }
    }
}

void BookingManager::displayFrequentRoutes(const Student &student) const
{
    std::map<std::string, int> routeFrequency;
    for (const auto &booking : bookings)
    {
        if (booking.getStudentEmail() == student.getEmail())
        {
            routeFrequency[booking.getRouteName()]++;
        }
    }
    std::cout << "\n----- Frequent Route Suggestions -----\n"
              << std::endl;
    for (const auto &route : routeFrequency)
    {
        std::cout << "Route: " << route.first << " - Booked " << route.second << " times" << std::endl;
    }
    if (routeFrequency.empty())
    {
        std::cout << "No routes booked yet." << std::endl;
    }
}

void BookingManager::generateExpenseReport(const Student &student) const
{
    double totalExpense = 0.0;
    double weeklyExpense = 0.0;
    double monthlyExpense = 0.0;
    std::time_t now = std::time(nullptr);
    for (const auto &booking : bookings)
    {
        if (booking.getStudentEmail() == student.getEmail() && booking.isActive())
        {
            totalExpense += booking.getFare();
            double diff = std::difftime(now, booking.getBookingTime());
            if (diff <= 7 * 24 * 3600)
            { // 7 days
                weeklyExpense += booking.getFare();
            }
            if (diff <= 30 * 24 * 3600)
            { // 30 days
                monthlyExpense += booking.getFare();
            }
        }
    }
    std::cout << "\n----- Expense Report for " << student.getEmail() << " -----\n"
              << std::endl;
    std::cout << "Total Expense    : " << totalExpense << std::endl;
    std::cout << "Weekly Expense   : " << weeklyExpense << std::endl;
    std::cout << "Monthly Expense  : " << monthlyExpense << std::endl;
}

void BookingManager::logEvent(const std::string &event) const
{
    std::time_t now = std::time(nullptr);
    std::cout << std::ctime(&now) << ": " << event << std::endl;
}

void BookingManager::saveBookings() const
{
    std::ofstream outFile(bookingFile);
    if (!outFile)
    {
        std::cerr << "Error: Unable to open file for saving bookings." << std::endl;
        return;
    }
    for (const auto &booking : bookings)
    {
        outFile << booking.serialize() << std::endl;
    }
    outFile.close();
}

void BookingManager::loadBookings()
{
    std::ifstream inFile(bookingFile);
    if (!inFile)
    {
        return;
    }
    std::string line;
    bookings.clear();
    while (std::getline(inFile, line))
    {
        if (line.empty())
            continue;
        Booking booking;
        booking.deserialize(line);
        bookings.push_back(booking);
    }
    inFile.close();
}