#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H

#include "Booking.h"
#include "Student.h"
#include "ShuttleSystem.h"
#include <vector>
#include <string>
#include <map>

class BookingManager
{
private:
    std::vector<Booking> bookings;
    ShuttleSystem *shuttleSystem;                   
    const std::string bookingFile = "bookings.txt"; 

    double calculateCurrentFare() const;

public:

BookingManager(ShuttleSystem *shuttleSystem);

    void showAvailableRoutes() const;

    bool bookTrip(Student &student, const std::string &routeName,
                  const std::string &startStop, const std::string &endStop);

    bool cancelBooking(Student &student, bool isLastMinute);

    void displayTripHistory(const Student &student) const;

    void displayFrequentRoutes(const Student &student) const;

    void generateExpenseReport(const Student &student) const;

    void logEvent(const std::string &event) const;

    void saveBookings() const;

    void loadBookings();
};

#endif // BOOKINGMANAGER_H