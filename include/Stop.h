#ifndef STOP_H
#define STOP_H

#include <string>

class Stop
{
private:
    std::string stopName; 
    int demandLevel;      

public:
    Stop(const std::string &name, int demand);

    std::string getStopName() const;
    int getDemandLevel() const;

    void setStopName(const std::string &name);
    void setDemandLevel(int demand);

    void displayStop() const;
};

#endif 