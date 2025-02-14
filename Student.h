#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
private:
    std::string name;
    std::string email;
    std::string password;
    double walletBalance; // Only wallet balance is used

public:
    // Constructor
    Student(const std::string& name, const std::string& email, const std::string& password);

    // Getters
    std::string getName() const;
    std::string getEmail() const;
    std::string getPassword() const;
    double getWalletBalance() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);
    void setPassword(const std::string& password);
    void setWalletBalance(double balance);

    // Add funds to the wallet
    void addFunds(double amount);

    // Deduct funds from the wallet
    void deductFunds(double amount);

    // Display student details
    void displayStudent() const;
};

#endif // STUDENT_H