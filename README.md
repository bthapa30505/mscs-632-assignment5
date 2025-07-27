# MSCS-632 Assignment 5: Ride Sharing System

This project implements a comprehensive Ride Sharing System in both **Smalltalk** and **C++** to demonstrate the three fundamental Object-Oriented Programming principles:

- **Encapsulation**: Private data members with controlled public access
- **Inheritance**: Base classes with derived classes that extend functionality  
- **Polymorphism**: Virtual methods with runtime method dispatch

## Project Structure

```
mscs-632-assignment5/
├── README.md                 # This file
├── cpp/                      # C++ Implementation
│   ├── RideSharingSystem.h   # Header file with class declarations
│   ├── RideSharingSystem.cpp # Implementation file
│   ├── main.cpp              # Main function
│   ├── Makefile              # Build configuration
│   ├── cpp_readme.md         # Detailed C++ documentation
│   └── RideSharingSystem*    # Compiled executable
└── st/                       # Smalltalk Implementation
    ├── RideSharingSystem.st  # Complete Smalltalk implementation
    └── run_demo.st           # Demo runner script
```

## How to Run

### C++ Implementation
```bash
cd cpp
make run       # Compile and run
# or
make           # Just compile
./RideSharingSystem
```

### Smalltalk Implementation  
```bash
cd st
gst -f run_demo.st
# or
gst -f RideSharingSystem.st
# then in Smalltalk: RideSharingDemo runDemo
```

## Features Implemented

### Core Classes
- **Ride (Base Class)**: Core ride attributes and virtual methods
- **StandardRide**: Inherits from Ride with standard pricing
- **PremiumRide**: Inherits from Ride with luxury pricing and surcharge
- **Driver**: Manages assigned rides with encapsulated collections
- **Rider**: Manages requested rides with controlled access
- **Demo Classes**: Comprehensive demonstrations of all OOP principles

### Fare Calculations (Polymorphic)
- **Base Ride**: $2.50 per mile
- **Standard Ride**: $2.00 per mile + $1.50 base fee
- **Premium Ride**: $3.50 per mile + $5.00 base fee + 20% luxury surcharge

## OOP Principles Demonstrated

Both implementations showcase:
1. **Encapsulation** through private data members and public accessor methods
2. **Inheritance** with base Ride class and derived StandardRide/PremiumRide classes
3. **Polymorphism** via virtual methods (C++) and method overriding (Smalltalk)

See individual implementation documentation for language-specific details:
- `cpp/cpp_readme.md` for C++ implementation details
- Smalltalk implementation includes comprehensive inline documentation

## Requirements Met

✅ Base Ride class with core attributes and methods  
✅ StandardRide and PremiumRide derived classes with overridden fare methods  
✅ Driver class with encapsulated ride management  
✅ Rider class with ride request functionality  
✅ Polymorphic collections demonstrating runtime method dispatch  
✅ Comprehensive demonstrations of all three OOP principles  
✅ Complete working implementations in both languages