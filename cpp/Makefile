# Makefile for C++ Ride Sharing System
# Demonstrates OOP principles: Encapsulation, Inheritance, and Polymorphism

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -pedantic -O2

# Target executable
TARGET = RideSharingSystem

# Source files
SOURCES = main.cpp RideSharingSystem.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Header files
HEADERS = RideSharingSystem.h

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Build object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the executable (default)"
	@echo "  run     - Build and run the program"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"

# Phony targets
.PHONY: all run clean help 