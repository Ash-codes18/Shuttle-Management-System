# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++17

# Source files
SRCS = main.cpp Authentication.cpp Route.cpp ShuttleSystem.cpp Stop.cpp Student.cpp Wallet.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = shuttle_system

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean