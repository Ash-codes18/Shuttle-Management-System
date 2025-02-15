#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <ctime>

class Booking
{
private:
    std::string studentEmail;
    std::string routeName;
    std::string startStop;
    std::string endStop;
    std::time_t bookingTime;
    double fare;
    bool active;

public:
    Booking(const std::string &studentEmail, const std::string &routeName, double fare,
            const std::string &startStop, const std::string &endStop);

    Booking();

    std::string getStudentEmail() const;
    std::string getRouteName() const;
    std::string getStartStop() const;
    std::string getEndStop() const;
    std::time_t getBookingTime() const;
    double getFare() const;
    bool isActive() const;

    void cancel();

    std::string serialize() const;

    void deserialize(const std::string &data);
};

#endif 