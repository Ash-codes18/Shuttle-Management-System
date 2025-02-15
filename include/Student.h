#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student
{
private:
    std::string name;
    std::string email;
    std::string password;
    double walletBalance; 

public:
    Student(const std::string &name, const std::string &email, const std::string &password);

    std::string getName() const;
    std::string getEmail() const;
    std::string getPassword() const;
    double getWalletBalance() const;

    void setName(const std::string &name);
    void setEmail(const std::string &email);
    void setPassword(const std::string &password);
    void setWalletBalance(double balance);

    void addFunds(double amount);

    void deductFunds(double amount);

    void displayStudent() const;
};

#endif 