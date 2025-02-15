#ifndef STOP_H
#define STOP_H

#include <string>

class Stop {
private:
    std::string stopName; // Name of the stop
    int demandLevel;      // Demand level (e.g., high, medium, low)

public:
    // Constructor
    Stop(const std::string& name, int demand);

    // Getters
    std::string getStopName() const;
    int getDemandLevel() const;

    // Setters
    void setStopName(const std::string& name);
    void setDemandLevel(int demand);

    // Display stop details
    void displayStop() const;
};

#endif // STOP_H