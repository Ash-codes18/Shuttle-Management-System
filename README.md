# Shuttle Management System

Welcome to the Shuttle Management System repository! This project implements an interactive system for managing shuttle schedules and user interactions. It provides a simple console-based interface for student login, student registration, and administrator functions.

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
  - Linux: gcc or clang
  - Windows: MSVC (Visual Studio recommended)
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
   mkdir build
   cd build
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```

3. **Build the Executable:**

   ```bash
   cmake --build . --config Release
   ```

   *Note*: On Windows, if using a multi-configuration generator (e.g., Visual Studio), the executable will be located inside a subdirectory such as `Release`.

### Using the Makefile (Unix-like Systems)

You can also build the project with the provided Makefile:

```bash
make
```

## Running the System

After a successful build, run the executable from your build output directory:

### On Linux/Ubuntu

```bash
./shuttle_system
```

### On Windows

If built with Visual Studio or via CMake with a multi-config generator, the executable might be located in the `Release` folder:

```powershell
.\Release\shuttle_system.exe
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


## Continuous Integration

This repository is configured with GitHub Actions for continuous integration. The workflow files in the `.github/workflows` directory handle building and testing the project on both Ubuntu and Windows environments.