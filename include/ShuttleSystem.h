#ifndef SHUTTLESYSTEM_H
#define SHUTTLESYSTEM_H

#include <vector>
#include <string>
#include <fstream>
#include "Route.h"

class ShuttleSystem
{
private:
    std::vector<Route> routes;                  
    const std::string routeFile = "routes.txt"; 

public:
    void addRoute(const Route &route);

    void removeRoute(const std::string &routeName);

    Route *findRoute(const std::string &routeName);

    void displayAllRoutes() const;

    void suggestOptimalRoutes() const;

    std::vector<Route> &getAllRoutes();

    void saveRoutesToFile() const;

    void loadRoutesFromFile();
};

#endif 