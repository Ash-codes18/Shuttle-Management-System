#ifndef WALLET_H
#define WALLET_H

#include "Student.h"
#include <ctime> // For time functions

class Wallet
{
public:
    // Add funds to a student's wallet
    static void addFunds(Student &student, double amount);

    // Deduct funds from a student's wallet
    static void deductFunds(Student &student, double amount);

    // Deduct fare based on dynamic pricing
    static void deductFare(Student &student);

    // Deduct funds for violations (e.g., cancellations, no-shows)
    static void deductForViolation(Student &student, double penalty);

    // Display wallet balance
    static void displayBalance(const Student &student);

private:
    // Check if it is peak hour
    static bool isPeakHour();
};

#endif // WALLET_H