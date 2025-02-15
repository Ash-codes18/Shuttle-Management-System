#include "Wallet.h"
#include <iostream>
#include <ctime>

void Wallet::addFunds(Student& student, double amount) {
    student.addFunds(amount);
}

void Wallet::deductFunds(Student& student, double amount) {
    student.deductFunds(amount);
}

bool Wallet::isPeakHour() {
    // Get the current time
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);

    int currentHour = localTime->tm_hour; // Current hour (0-23)
    int currentMinute = localTime->tm_min; // Current minute (0-59)

    // Define peak hours (7:00 AM - 9:00 AM and 5:00 PM - 7:00 PM)
    bool isMorningPeak = (currentHour == 7 && currentMinute >= 0) ||
                         (currentHour == 8 && currentMinute >= 0) ||
                         (currentHour == 9 && currentMinute == 0);

    bool isEveningPeak = (currentHour == 17 && currentMinute >= 0) ||
                         (currentHour == 18 && currentMinute >= 0) ||
                         (currentHour == 19 && currentMinute == 0);

    return isMorningPeak || isEveningPeak;
}

void Wallet::deductFare(Student& student) {
    double fare = isPeakHour() ? 10.0 : 5.0; // Dynamic pricing
    if (student.getWalletBalance() >= fare) {
        student.deductFunds(fare);
        std::cout << "Fare deducted: " << fare << std::endl;
    } else {
        std::cout << "Insufficient funds! Please recharge." << std::endl;
    }
}

void Wallet::deductForViolation(Student& student, double penalty) {
    if (student.getWalletBalance() >= penalty) {
        student.deductFunds(penalty);
        std::cout << "Penalty deducted: " << penalty << std::endl;
    } else {
        std::cout << "Insufficient funds to deduct penalty!" << std::endl;
    }
}

void Wallet::displayBalance(const Student& student) {
    std::cout << "Wallet Balance: " << student.getWalletBalance() << std::endl;
}