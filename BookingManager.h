#ifndef BOOKINGMANAGER_H
#define BOOKINGMANAGER_H

#include "Booking.h"
#include "Student.h"
#include "ShuttleSystem.h"
#include <vector>
#include <string>
#include <map>

class BookingManager {
private:
    std::vector<Booking> bookings;
    ShuttleSystem* shuttleSystem; // Pointer to access available routes.
    const std::string bookingFile = "bookings.txt"; // Persistent storage file.

    // Helper: Calculate current fare based on peak hours.
    double calculateCurrentFare() const;

public:
    // Constructor takes a pointer to an existing ShuttleSystem instance.
    BookingManager(ShuttleSystem* shuttleSystem);

    // Display all available routes.
    void showAvailableRoutes() const;

    // Book a trip for a student on a given route with start and end stops.
    // Returns true if booking succeeds; false otherwise.
    bool bookTrip(Student& student, const std::string& routeName,
                  const std::string& startStop, const std::string& endStop);

    // Cancel a booking for a student.
    // isLastMinute: if true, partial refund; if false, full refund.
    bool cancelBooking(Student& student, bool isLastMinute);

    // Display trip history for a student.
    void displayTripHistory(const Student& student) const;

    // Display frequent route suggestions for a student.
    void displayFrequentRoutes(const Student& student) const;

    // Generate an expense report for a student.
    void generateExpenseReport(const Student& student) const;

    // Log booking events.
    void logEvent(const std::string& event) const;

    // Save all booking records to file.
    void saveBookings() const;

    // Load booking records from file.
    void loadBookings();
};

#endif // BOOKINGMANAGER_H