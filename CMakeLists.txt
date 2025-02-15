cmake_minimum_required(VERSION 3.10)
project(ShuttleSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)


# Add all source files
set(SOURCES
    src/main.cpp
    src/Authentication.cpp
    src/Route.cpp
    src/ShuttleSystem.cpp
    src/Stop.cpp
    src/Student.cpp
    src/Wallet.cpp
    src/Booking.cpp
    src/BookingManager.cpp
    src/TransferManager.cpp
)

# Create the executable
add_executable(shuttle_system ${SOURCES})