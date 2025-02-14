#include "Student.h"
#include <iostream>

Student::Student(const std::string& name, const std::string& email, const std::string& password)
    : name(name), email(email), password(password), walletBalance(0.0) {}

std::string Student::getName() const {
    return name;
}

std::string Student::getEmail() const {
    return email;
}

std::string Student::getPassword() const {
    return password;
}

double Student::getWalletBalance() const {
    return walletBalance;
}

void Student::setName(const std::string& name) {
    this->name = name;
}

void Student::setEmail(const std::string& email) {
    this->email = email;
}

void Student::setPassword(const std::string& password) {
    this->password = password;
}

void Student::setWalletBalance(double balance) {
    walletBalance = balance;
}

void Student::addFunds(double amount) {
    walletBalance += amount;
}

void Student::deductFunds(double amount) {
    if (walletBalance >= amount) {
        walletBalance -= amount;
    } else {
        std::cout << "Insufficient funds!" << std::endl;
    }
}

void Student::displayStudent() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Wallet Balance: " << walletBalance << std::endl;
}