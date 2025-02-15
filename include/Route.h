#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <string>
#include <fstream>
#include "Stop.h"

class Route
{
private:
    std::string routeName;
    std::vector<Stop> stops;
    std::string peakHours;
    std::string classSchedule;
    const std::string routeFile = "routes.txt"; // File to store route data

public:
    // Constructor
    Route(const std::string &name, const std::string &peak, const std::string &schedule);

    // Copy constructor
    Route(const Route &other);

    // Copy assignment operator
    Route &operator=(const Route &other);

    // Move constructor
    Route(Route &&other) noexcept;

    // Move assignment operator
    Route &operator=(Route &&other) noexcept;

    // Add a stop to the route
    void addStop(const Stop &stop);

    // Remove a stop by name
    void removeStop(const std::string &stopName);

    // Modify a stop's demand level
    void modifyStopDemand(const std::string &stopName, int newDemand);

    // Display route details
    void displayRoute() const;

    // Getters
    std::string getRouteName() const;
    std::vector<Stop> getStops() const;
    std::string getPeakHours() const;
    std::string getClassSchedule() const;

    // Save route to file
    void saveRouteToFile() const;

    // Load route from file
    void loadRouteFromFile();

    // New member functions for TransferManager
    // Returns true if the route contains a stop with the given name.
    bool hasStop(const std::string &stopName) const;
    // Returns the index of the stop in the stops vector; returns -1 if not found.
    int getStopIndex(const std::string &stopName) const;
};

#endif // ROUTE_H