#ifndef SHUTTLESYSTEM_H
#define SHUTTLESYSTEM_H

#include <vector>
#include <string>
#include <fstream>
#include "Route.h"

class ShuttleSystem {
private:
    std::vector<Route> routes; // List of all routes
    const std::string routeFile = "routes.txt"; // File to store route data

public:
    // Add a new route
    void addRoute(const Route& route);

    // Remove a route by name
    void removeRoute(const std::string& routeName);

    // Find a route by name
    Route* findRoute(const std::string& routeName);

    // Display all routes
    void displayAllRoutes() const;

    // Suggest optimal routes based on demand and peak hours
    void suggestOptimalRoutes() const;

    // Get all routes
    std::vector<Route>& getAllRoutes();

    // Save routes to file
    void saveRoutesToFile() const;

    // Load routes from file
    void loadRoutesFromFile();
};

#endif // SHUTTLESYSTEM_H