#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <fstream>
#include <string>
#include <vector>

#include "Student.h"

class Authentication
{
private:
    std::vector<Student> students;                  
    const std::string studentFile = "students.txt"; 
    const std::string logFile = "logs.txt";         
    const std::string adminUsername = "admin";      
    const std::string adminPassword = "admin123";   

public:

bool registerStudent(const std::string &name, const std::string &email,
                         const std::string &password);

    Student *loginStudent(const std::string &email, const std::string &password);

    Student *findStudentByEmail(const std::string &email);

    bool loginAdmin(const std::string &username, const std::string &password) const;

    bool studentExists(const std::string &email) const;

    std::vector<Student> &getAllStudents();

    void saveStudentsToFile() const;

    void loadStudentsFromFile();

    void logEvent(const std::string &event) const;

    void viewLogs() const;
};

#endif 