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
    const std::string routeFile = "routes.txt"; 

public:

    Route(const std::string &name, const std::string &peak, const std::string &schedule);

    Route(const Route &other);

    Route &operator=(const Route &other);

    Route(Route &&other) noexcept;

    Route &operator=(Route &&other) noexcept;

    void addStop(const Stop &stop);

    void removeStop(const std::string &stopName);

    void modifyStopDemand(const std::string &stopName, int newDemand);

    void displayRoute() const;

    std::string getRouteName() const;
    std::vector<Stop> getStops() const;
    std::string getPeakHours() const;
    std::string getClassSchedule() const;

    void saveRouteToFile() const;

    void loadRouteFromFile();

    bool hasStop(const std::string &stopName) const;

    int getStopIndex(const std::string &stopName) const;
};

#endif 