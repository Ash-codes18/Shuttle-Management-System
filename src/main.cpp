#include <iostream>
#include "Authentication.h"
#include "Wallet.h"
#include "ShuttleSystem.h"
#include "BookingManager.h"
#include "TransferManager.h"

void displayStudentMenu()
{
    std::cout << "\n===== Student Menu =====" << std::endl;
    std::cout << "1. View Wallet Balance" << std::endl;
    std::cout << "2. Add Funds to Wallet" << std::endl;
    std::cout << "3. Book a Trip" << std::endl;
    std::cout << "4. Cancel Booking" << std::endl;
    std::cout << "5. View Trip History" << std::endl;
    std::cout << "6. View Frequent Route Suggestions" << std::endl;
    std::cout << "7. Generate Expense Report" << std::endl;
    std::cout << "8. Bus Transfer & Best Route Suggestion" << std::endl;
    std::cout << "9. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

void displayAdminMenu()
{
    std::cout << "\n===== Admin Menu =====" << std::endl;
    std::cout << "1. Create a New Route" << std::endl;
    std::cout << "2. Add a Stop to a Route" << std::endl;
    std::cout << "3. Remove a Stop from a Route" << std::endl;
    std::cout << "4. Modify Stop Demand" << std::endl;
    std::cout << "5. Display All Routes" << std::endl;
    std::cout << "6. Suggest Optimal Routes" << std::endl;
    std::cout << "7. Allocate Funds to Student" << std::endl;
    std::cout << "8. Deduct Funds for Violation" << std::endl;
    std::cout << "9. View All Students" << std::endl;
    std::cout << "10. View Logs" << std::endl;
    std::cout << "11. Logout" << std::endl;
    std::cout << "Enter your choice: ";
}

int main()
{
    Authentication auth;
    ShuttleSystem shuttleSystem;
    // Create BookingManager instance with pointer to shuttleSystem.
    BookingManager bookingManager(&shuttleSystem);
    TransferManager transferManager(&shuttleSystem);

    // Load persistent data.
    auth.loadStudentsFromFile();
    shuttleSystem.loadRoutesFromFile();

    int choice;
    std::string name, email, password;
    double amount;

    while (true)
    {
        std::cout << "\n===== Shuttle Management System =====" << std::endl;
        std::cout << "1. Student Login" << std::endl;
        std::cout << "2. Student Registration" << std::endl;
        std::cout << "3. Admin Login" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(); // Clear newline

        if (choice == 1)
        {
            std::cout << "Enter your email: ";
            std::getline(std::cin, email);
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);

            Student *student = auth.loginStudent(email, password);
            if (student)
            {
                int studentChoice;
                do
                {
                    displayStudentMenu();
                    std::cin >> studentChoice;
                    std::cin.ignore();

                    switch (studentChoice)
                    {
                    case 1:
                    {
                        Wallet::displayBalance(*student);
                        break;
                    }
                    case 2:
                    {
                        std::cout << "Enter amount to add: ";
                        std::cin >> amount;
                        std::cin.ignore();
                        Wallet::addFunds(*student, amount);
                        std::cout << "Funds added successfully!" << std::endl;
                        break;
                    }
                    case 3:
                    {
                        // Book a trip: prompt for route, start stop, and end stop.
                        bookingManager.showAvailableRoutes();
                        std::cout << "Enter the route name to book a trip: ";
                        std::string routeName, startStop, endStop;
                        std::getline(std::cin, routeName);
                        std::cout << "Enter start stop: ";
                        std::getline(std::cin, startStop);
                        std::cout << "Enter destination (end stop): ";
                        std::getline(std::cin, endStop);
                        bookingManager.bookTrip(*student, routeName, startStop, endStop);
                        break;
                    }
                    case 4:
                    {
                        std::cout << "Is this a last minute cancellation? (y/n): ";
                        char response;
                        std::cin >> response;
                        std::cin.ignore();
                        bool lastMinute = (response == 'y' || response == 'Y');
                        bookingManager.cancelBooking(*student, lastMinute);
                        break;
                    }
                    case 5:
                    {
                        bookingManager.displayTripHistory(*student);
                        break;
                    }
                    case 6:
                    {
                        bookingManager.displayFrequentRoutes(*student);
                        break;
                    }
                    case 7:
                    {
                        bookingManager.generateExpenseReport(*student);
                        break;
                    }
                    case 8:
                    {
                        // Bus Transfer & Best Route Suggestion using TransferManager.
                        std::string originStop, destinationStop;
                        std::cout << "Enter origin stop: ";
                        std::getline(std::cin, originStop);
                        std::cout << "Enter destination stop: ";
                        std::getline(std::cin, destinationStop);
                        std::string transferPlan = transferManager.suggestTransferPlan(originStop, destinationStop);
                        std::cout << transferPlan << std::endl;
                        std::cout << "Do you want to book this multi-leg journey? (y/n): ";
                        char bookResponse;
                        std::cin >> bookResponse;
                        std::cin.ignore();
                        if (bookResponse == 'y' || bookResponse == 'Y')
                        {
                            transferManager.bookMultiLegJourney(*student, originStop, destinationStop);
                        }
                        break;
                    }
                    case 9:
                    {
                        std::cout << "Logging out..." << std::endl;
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid choice! Please try again." << std::endl;
                        break;
                    }
                    }
                } while (studentChoice != 9);
            }
            else
            {
                std::cout << "Invalid email or password!" << std::endl;
            }
        }
        else if (choice == 2)
        {
            std::cout << "Enter your name: ";
            std::getline(std::cin, name);
            std::cout << "Enter your email: ";
            std::getline(std::cin, email);
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);

            if (auth.registerStudent(name, email, password))
            {
                std::cout << "Registration successful!" << std::endl;
            }
            else
            {
                std::cout << "Registration failed. Email already exists." << std::endl;
            }
        }
        else if (choice == 3)
        {
            std::string username;
            std::cout << "Enter admin username: ";
            std::getline(std::cin, username);
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);

            if (auth.loginAdmin(username, password))
            {
                int adminChoice;
                do
                {
                    displayAdminMenu();
                    std::cin >> adminChoice;
                    std::cin.ignore();

                    switch (adminChoice)
                    {
                    case 1:
                    {
                        std::string routeName, peakHours, classSchedule;
                        std::cout << "Enter route name: ";
                        std::getline(std::cin, routeName);
                        std::cout << "Enter peak hours (e.g., 7:00 AM - 9:00 AM): ";
                        std::getline(std::cin, peakHours);
                        std::cout << "Enter class schedule (e.g., 8:00 AM Classes): ";
                        std::getline(std::cin, classSchedule);
                        Route newRoute(routeName, peakHours, classSchedule);
                        shuttleSystem.addRoute(newRoute);
                        std::cout << "Route created successfully!" << std::endl;
                        break;
                    }
                    case 2:
                    {
                        std::string routeName, stopName;
                        int demandLevel;
                        std::cout << "Enter route name: ";
                        std::getline(std::cin, routeName);
                        std::cout << "Enter stop name: ";
                        std::getline(std::cin, stopName);
                        std::cout << "Enter demand level (1-5): ";
                        std::cin >> demandLevel;
                        std::cin.ignore();
                        Route *route = shuttleSystem.findRoute(routeName);
                        if (route)
                        {
                            Stop newStop(stopName, demandLevel);
                            route->addStop(newStop);
                            std::cout << "Stop added successfully!" << std::endl;
                        }
                        else
                        {
                            std::cout << "Route not found!" << std::endl;
                        }
                        break;
                    }
                    case 3:
                    {
                        std::string routeName, stopName;
                        std::cout << "Enter route name: ";
                        std::getline(std::cin, routeName);
                        std::cout << "Enter stop name to remove: ";
                        std::getline(std::cin, stopName);
                        Route *route = shuttleSystem.findRoute(routeName);
                        if (route)
                        {
                            route->removeStop(stopName);
                            std::cout << "Stop removed successfully!" << std::endl;
                        }
                        else
                        {
                            std::cout << "Route not found!" << std::endl;
                        }
                        break;
                    }
                    case 4:
                    {

                        std::string routeName, stopName;
                        int newDemand;
                        std::cout << "Enter route name: ";
                        std::getline(std::cin, routeName);
                        std::cout << "Enter stop name to modify: ";
                        std::getline(std::cin, stopName);
                        std::cout << "Enter new demand level (1-5): ";
                        std::cin >> newDemand;
                        std::cin.ignore();
                        Route *route = shuttleSystem.findRoute(routeName);
                        if (route)
                        {
                            route->modifyStopDemand(stopName, newDemand);
                            std::cout << "Stop demand updated successfully!" << std::endl;
                        }
                        else
                        {
                            std::cout << "Route not found!" << std::endl;
                        }
                        break;
                    }
                    case 5:
                    {
                        shuttleSystem.displayAllRoutes();
                        break;
                    }
                    case 6:
                    {
                        shuttleSystem.suggestOptimalRoutes();
                        break;
                    }
                    case 7:
                    {
                        std::cout << "Enter student email: ";
                        std::getline(std::cin, email);
                        Student *student = auth.findStudentByEmail(email);
                        if (student)
                        {
                            std::cout << "Enter amount to allocate: ";
                            std::cin >> amount;
                            std::cin.ignore();
                            Wallet::addFunds(*student, amount);
                            std::cout << "Funds allocated successfully!" << std::endl;
                        }
                        else
                        {
                            std::cout << "Student not found!" << std::endl;
                        }
                        break;
                    }
                    case 8:
                    {
                        std::cout << "Enter student email: ";
                        std::getline(std::cin, email);
                        Student *student = auth.findStudentByEmail(email);
                        if (student)
                        {
                            double penalty;
                            std::cout << "Enter penalty amount: ";
                            std::cin >> penalty;
                            std::cin.ignore();
                            Wallet::deductForViolation(*student, penalty);
                        }
                        else
                        {
                            std::cout << "Student not found!" << std::endl;
                        }
                        break;
                    }
                    case 9:
                    {
                        std::vector<Student> &students = auth.getAllStudents();
                        for (const auto &stud : students)
                        {
                            stud.displayStudent();
                            std::cout << "---------------------" << std::endl;
                        }
                        break;
                    }
                    case 10:
                    {
                        auth.viewLogs();
                        break;
                    }
                    case 11:
                    {
                        std::cout << "Logging out..." << std::endl;
                        break;
                    }
                    default:
                    {
                        std::cout << "Invalid choice! Please try again." << std::endl;
                        break;
                    }
                    }
                } while (adminChoice != 11);
            }
            else
            {
                std::cout << "Invalid username or password!" << std::endl;
            }
        }
        else if (choice == 4)
        {
            auth.saveStudentsToFile();
            shuttleSystem.saveRoutesToFile();
            std::cout << "Exiting the system. Goodbye!" << std::endl;
            break;
        }
        else
        {
            std::cout << "Invalid choice! Please try again." << std::endl;
        }
    }

    return 0;
}