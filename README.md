# Shuttle Management System

This program implements an interactive system for managing shuttle schedules and user interactions. It provides a simple console-based interface for student login, student registration, and administrator functions.

Case Study Problem Statement : [Case Study PDF](https://github.com/Ash-codes18/Shuttle-Management-System/blob/main/Shuttle%20Management%20System.pdf)

## Video Demonstration

[![Shuttle Management System.mp4](https://idealer.io/wp-content/themes/iDealer/images/aicar.png)]()

## Features

- **Student Login**: Secure authentication for students.
- **Student Registration**: New students can register to use the system.
- **Admin Login**: Administrators have a dedicated login for managing shuttle operations.
- **Interactive Menu**: A console menu allows users to choose options easily.

## Project Structure

```
Shuttle-Management-System/
├── include/                      # Header files for the project
├── src/                          # Source code files
├── CMakeLists.txt                # CMake configuration file
└── data.txt                      # Text files for persisent data storage
```

## Prerequisites

- **CMake** (version 3.10 or later)
- **C/C++ Compiler**:
  - gcc or clang
- **Make** (for Unix-like systems) or an appropriate build system for Windows

## Building the Project

### Using CMake

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/Ash-codes18/Shuttle-Management-System.git
   cd Shuttle-Management-System
   ```

2. **Create a Build Directory and Configure the Project:**

   ```bash
   cmake -G "MinGW Makefiles" -S . -B build
   ```

3. **Build the Executable:**

   ```bash
   cmake --build build
   ```

## Running the System

After a successful build, run the executable from your build output directory:

```bash
./shuttle_system
```

When the program runs, you will see a menu like the following:

```
===== Shuttle Management System =====
1. Student Login
2. Student Registration
3. Admin Login
4. Exit
```

Follow the on-screen prompts to interact with the system. For automated testing or CI purposes, you can pipe inputs to the executable.


#### Admin Acesss

- **Id       : admin**
- **Password : admin123**

## Continuous Integration

This repository is configured with GitHub Actions for continuous integration. The workflow files in the `.github/workflows` directory handle building and testing the project on both Ubuntu and Windows environments.