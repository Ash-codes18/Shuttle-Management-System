#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include <string>
#include "ShuttleSystem.h"
#include "Student.h"

class TransferManager
{
private:
    ShuttleSystem *shuttleSystem;

public:
    TransferManager(ShuttleSystem *shuttleSystem);

    std::string suggestTransferPlan(const std::string &originStop, const std::string &destinationStop);

    bool bookMultiLegJourney(Student &student, const std::string &originStop, const std::string &destinationStop);
};

#endif 