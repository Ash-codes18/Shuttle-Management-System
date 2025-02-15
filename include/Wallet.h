#ifndef WALLET_H
#define WALLET_H

#include "Student.h"

class Wallet
{
public:
    static void addFunds(Student &student, double amount);

    static void deductFunds(Student &student, double amount);

    static void deductFare(Student &student);

    static void deductForViolation(Student &student, double penalty);

    static void displayBalance(const Student &student);

private:
    static bool isPeakHour();
};

#endif 