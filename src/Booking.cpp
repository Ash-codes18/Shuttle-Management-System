#include "Booking.h"
#include <sstream>
#include <ctime>

Booking::Booking(const std::string& studentEmail, const std::string& routeName, double fare,
                 const std::string& startStop, const std::string& endStop)
    : studentEmail(studentEmail), routeName(routeName), startStop(startStop), endStop(endStop),
      fare(fare), active(true) {
    bookingTime = std::time(nullptr);
}

Booking::Booking() : studentEmail(""), routeName(""), startStop(""), endStop(""),
                     bookingTime(0), fare(0.0), active(false) { }

std::string Booking::getStudentEmail() const {
    return studentEmail;
}

std::string Booking::getRouteName() const {
    return routeName;
}

std::string Booking::getStartStop() const {
    return startStop;
}

std::string Booking::getEndStop() const {
    return endStop;
}

std::time_t Booking::getBookingTime() const {
    return bookingTime;
}

double Booking::getFare() const {
    return fare;
}

bool Booking::isActive() const {
    return active;
}

void Booking::cancel() {
    active = false;
}

std::string Booking::serialize() const {
    std::ostringstream oss;
    oss << studentEmail << ","
        << routeName << ","
        << startStop << ","
        << endStop << ","
        << bookingTime << ","
        << fare << ","
        << active;
    return oss.str();
}

void Booking::deserialize(const std::string& data) {
    std::istringstream iss(data);
    std::string token;
    if (std::getline(iss, token, ',')) {
        studentEmail = token;
    }
    if (std::getline(iss, token, ',')) {
        routeName = token;
    }
    if (std::getline(iss, token, ',')) {
        startStop = token;
    }
    if (std::getline(iss, token, ',')) {
        endStop = token;
    }
    if (std::getline(iss, token, ',')) {
        bookingTime = std::stol(token);
    }
    if (std::getline(iss, token, ',')) {
        fare = std::stod(token);
    }
    if (std::getline(iss, token, ',')) {
        active = (token == "1") || (token == "true");
    }
}