#ifndef TRANSFERMANAGER_H
#define TRANSFERMANAGER_H

#include <string>
#include "ShuttleSystem.h"
#include "Student.h"

// TransferManager provides smart transfer suggestions and supports multi-leg journey bookings.
class TransferManager {
private:
    ShuttleSystem* shuttleSystem;
public:
    // Constructor that accepts a pointer to the ShuttleSystem instance.
    TransferManager(ShuttleSystem* shuttleSystem);

    // Suggest the best transfer plan given an origin and destination stop.
    // Returns a string with the transfer details and estimated travel times.
    std::string suggestTransferPlan(const std::string &originStop, const std::string &destinationStop);

    // Book a multi-leg journey using a one-ticket system where only a single fare is deducted.
    // Returns true if booking is successful; false otherwise.
    bool bookMultiLegJourney(Student &student, const std::string &originStop, const std::string &destinationStop);
};

#endif // TRANSFERMANAGER_H