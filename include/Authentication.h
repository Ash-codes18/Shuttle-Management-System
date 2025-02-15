#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <fstream>
#include <string>
#include <vector>

#include "Student.h"

class Authentication
{
private:
    std::vector<Student> students;                  // List of registered students
    const std::string studentFile = "students.txt"; // File to store student data
    const std::string logFile = "logs.txt";         // File to store logs
    const std::string adminUsername = "admin";      // Admin username
    const std::string adminPassword = "admin123";   // Admin password

public:
    // Register a new student
    bool registerStudent(const std::string &name, const std::string &email,
                         const std::string &password);

    // Login a student
    Student *loginStudent(const std::string &email, const std::string &password);

    // Find a student by email (without password verification)
    Student *findStudentByEmail(const std::string &email);

    // Login as admin
    bool loginAdmin(const std::string &username, const std::string &password) const;

    // Check if a student exists
    bool studentExists(const std::string &email) const;

    // Get all students
    std::vector<Student> &getAllStudents();

    // Save students to file
    void saveStudentsToFile() const;

    // Load students from file
    void loadStudentsFromFile();

    // Log an event (e.g., registration, login, error)
    void logEvent(const std::string &event) const;

    // View logs (for admin)
    void viewLogs() const;
};

#endif // AUTHENTICATION_H