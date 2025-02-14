#include "Stop.h"
#include <iostream>

Stop::Stop(const std::string& name, int demand) : stopName(name), demandLevel(demand) {}

std::string Stop::getStopName() const {
    return stopName;
}

int Stop::getDemandLevel() const {
    return demandLevel;
}

void Stop::setStopName(const std::string& name) {
    stopName = name;
}

void Stop::setDemandLevel(int demand) {
    demandLevel = demand;
}

void Stop::displayStop() const {
    std::cout << "Stop: " << stopName << ", Demand Level: " << demandLevel << std::endl;
}