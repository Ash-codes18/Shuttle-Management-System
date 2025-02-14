cmake_minimum_required(VERSION 3.10)
project(ShuttleSystem)

set(CMAKE_CXX_STANDARD 17)

# Add all source files
set(SOURCES
    main.cpp
    Authentication.cpp
    Route.cpp
    ShuttleSystem.cpp
    Stop.cpp
    Student.cpp
    Wallet.cpp
)

# Create the executable
add_executable(shuttle_system ${SOURCES})