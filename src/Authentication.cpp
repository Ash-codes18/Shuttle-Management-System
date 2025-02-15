#include "Authentication.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

bool Authentication::registerStudent(const std::string &name, const std::string &email, const std::string &password)
{
    if (studentExists(email))
    {
        logEvent("Registration failed: Email " + email + " already exists.");
        return false; // Student already exists
    }
    students.push_back(Student(name, email, password));
    logEvent("Registration successful: " + name + " (" + email + ")");
    return true;
}

Student *Authentication::loginStudent(const std::string &email, const std::string &password)
{
    for (auto &student : students)
    {
        if (student.getEmail() == email && student.getPassword() == password)
        {
            logEvent("Login successful: " + email);
            return &student;
        }
    }
    logEvent("Login failed: Invalid email or password for " + email);
    return nullptr;
}

Student *Authentication::findStudentByEmail(const std::string &email)
{
    for (auto &student : students)
    {
        if (student.getEmail() == email)
        {
            return &student;
        }
    }
    return nullptr;
}

bool Authentication::loginAdmin(const std::string &username, const std::string &password) const
{
    if (username == adminUsername && password == adminPassword)
    {
        logEvent("Admin login successful: " + username);
        return true;
    }
    logEvent("Admin login failed: Invalid username or password for " + username);
    return false;
}

bool Authentication::studentExists(const std::string &email) const
{
    for (const auto &student : students)
    {
        if (student.getEmail() == email)
        {
            return true;
        }
    }
    return false;
}

std::vector<Student> &Authentication::getAllStudents()
{
    return students;
}

void Authentication::saveStudentsToFile() const
{
    std::ofstream file(studentFile);
    if (file.is_open())
    {
        for (const auto &student : students)
        {
            file << student.getName() << ","
                 << student.getEmail() << ","
                 << student.getPassword() << ","
                 << student.getWalletBalance() << "\n";
        }
        file.close();
    }
    else
    {
        logEvent("Error: Unable to save students to file.");
    }
}

void Authentication::loadStudentsFromFile()
{
    std::ifstream file(studentFile);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string name, email, password;
            double balance;
            std::getline(ss, name, ',');
            std::getline(ss, email, ',');
            std::getline(ss, password, ',');
            ss >> balance;

            students.push_back(Student(name, email, password));
            students.back().setWalletBalance(balance);
        }
        file.close();
    }
    else
    {
        logEvent("Error: Unable to load students from file.");
    }
}

void Authentication::logEvent(const std::string &event) const
{
    std::ofstream file(logFile, std::ios::app); // Append mode
    if (file.is_open())
    {
        // Add timestamp to the log
        std::time_t now = std::time(nullptr);
        file << std::ctime(&now) << ": " << event << "\n";
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to log event!" << std::endl;
    }
}

void Authentication::viewLogs() const
{
    std::ifstream file(logFile);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Error: Unable to view logs!" << std::endl;
    }
}