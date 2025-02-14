#include "Route.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

// Constructor
Route::Route(const std::string& name, const std::string& peak, const std::string& schedule)
    : routeName(name), peakHours(peak), classSchedule(schedule) {}

// Copy constructor
Route::Route(const Route& other)
    : routeName(other.routeName),
      stops(other.stops),
      peakHours(other.peakHours),
      classSchedule(other.classSchedule) {}

// Copy assignment operator
Route& Route::operator=(const Route& other) {
    if (this != &other) {
        routeName = other.routeName;
        stops = other.stops;
        peakHours = other.peakHours;
        classSchedule = other.classSchedule;
    }
    return *this;
}

// Move constructor
Route::Route(Route&& other) noexcept
    : routeName(std::move(other.routeName)),
      stops(std::move(other.stops)),
      peakHours(std::move(other.peakHours)),
      classSchedule(std::move(other.classSchedule)) {}

// Move assignment operator
Route& Route::operator=(Route&& other) noexcept {
    if (this != &other) {
        routeName = std::move(other.routeName);
        stops = std::move(other.stops);
        peakHours = std::move(other.peakHours);
        classSchedule = std::move(other.classSchedule);
    }
    return *this;
}

void Route::addStop(const Stop& stop) {
    stops.push_back(stop);
}

void Route::removeStop(const std::string& stopName) {
    stops.erase(std::remove_if(stops.begin(), stops.end(),
        [&stopName](const Stop& stop) { return stop.getStopName() == stopName; }),
        stops.end());
}

void Route::modifyStopDemand(const std::string& stopName, int newDemand) {
    for (auto& stop : stops) {
        if (stop.getStopName() == stopName) {
            stop.setDemandLevel(newDemand);
            break;
        }
    }
}

void Route::displayRoute() const {
    std::cout << "Route: " << routeName << std::endl;
    std::cout << "Peak Hours: " << peakHours << std::endl;
    std::cout << "Class Schedule: " << classSchedule << std::endl;
    std::cout << "Stops:" << std::endl;
    for (const auto& stop : stops) {
        stop.displayStop();
    }
}

std::string Route::getRouteName() const {
    return routeName;
}

std::vector<Stop> Route::getStops() const {
    return stops;
}

std::string Route::getPeakHours() const {
    return peakHours;
}

std::string Route::getClassSchedule() const {
    return classSchedule;
}

void Route::saveRouteToFile() const {
    std::ofstream file(routeFile);
    if (file.is_open()) {
        file << routeName << "," << peakHours << "," << classSchedule << "\n";
        for (const auto& stop : stops) {
            file << stop.getStopName() << "," << stop.getDemandLevel() << "\n";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to save route to file!" << std::endl;
    }
}

void Route::loadRouteFromFile() {
    std::ifstream file(routeFile);
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        std::stringstream ss(line);
        std::getline(ss, routeName, ',');
        std::getline(ss, peakHours, ',');
        std::getline(ss, classSchedule, ',');

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string stopName;
            int demandLevel;
            std::getline(ss, stopName, ',');
            ss >> demandLevel;

            stops.push_back(Stop(stopName, demandLevel));
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to load route from file!" << std::endl;
    }
}