#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <ctime>

class Booking {
private:
    std::string studentEmail;
    std::string routeName;
    std::string startStop;
    std::string endStop;
    std::time_t bookingTime;
    double fare;
    bool active;

public:
    // Constructs a booking with student email, chosen route, fare,
    // and the start and end stops of the trip.
    Booking(const std::string& studentEmail, const std::string& routeName, double fare,
            const std::string& startStop, const std::string& endStop);

    // Default constructor for loading from file.
    Booking();

    std::string getStudentEmail() const;
    std::string getRouteName() const;
    std::string getStartStop() const;
    std::string getEndStop() const;
    std::time_t getBookingTime() const;
    double getFare() const;
    bool isActive() const;

    // Mark the booking as cancelled.
    void cancel();

    // Serialize the booking as a CSV string:
    // studentEmail,routeName,startStop,endStop,bookingTime,fare,active
    std::string serialize() const;

    // Deserialize booking data from a CSV string.
    void deserialize(const std::string& data);
};

#endif // BOOKING_H