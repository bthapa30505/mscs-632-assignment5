#ifndef RIDESHARINGSYSTEM_H
#define RIDESHARINGSYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>

//============================================================================
// Ride Sharing System in C++
// Demonstrating OOP principles: Encapsulation, Inheritance, and Polymorphism
//============================================================================

//============================================================================
// Base Ride class - demonstrates encapsulation and serves as base for inheritance
//============================================================================
class Ride {
private:
    // Private data members - demonstrating encapsulation
    int rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance;

public:
    // Constructor
    Ride(int id, const std::string& pickup, const std::string& dropoff, double dist);
    
    // Virtual destructor for proper polymorphic destruction
    virtual ~Ride() = default;
    
    // Public accessor methods - controlled access to private data
    int getRideID() const;
    std::string getPickupLocation() const;
    std::string getDropoffLocation() const;
    double getDistance() const;
    
    // Virtual methods for polymorphism - will be overridden in derived classes
    virtual double fare() const;
    virtual std::string rideDetails() const;
    virtual std::string getRideType() const;
};

//============================================================================
// StandardRide derived class - demonstrates inheritance and polymorphism
//============================================================================
class StandardRide : public Ride {
public:
    // Constructor
    StandardRide(int id, const std::string& pickup, const std::string& dropoff, double dist);
    
    // Override virtual methods - demonstrating polymorphism
    double fare() const override;
    std::string rideDetails() const override;
    std::string getRideType() const override;
};

//============================================================================
// PremiumRide derived class - demonstrates inheritance and polymorphism
//============================================================================
class PremiumRide : public Ride {
public:
    // Constructor
    PremiumRide(int id, const std::string& pickup, const std::string& dropoff, double dist);
    
    // Override virtual methods - demonstrating polymorphism
    double fare() const override;
    std::string rideDetails() const override;
    std::string getRideType() const override;
};

//============================================================================
// Driver class - demonstrates encapsulation with private ride collection
//============================================================================
class Driver {
private:
    // Private data members - demonstrating encapsulation
    int driverID;
    std::string name;
    double rating;
    std::vector<std::shared_ptr<Ride>> assignedRides; // Private collection

public:
    // Constructor
    Driver(int id, const std::string& driverName, double driverRating);
    
    // Public accessor methods
    int getDriverID() const;
    std::string getName() const;
    double getRating() const;
    
    // Methods for controlled access to private data
    void addRide(std::shared_ptr<Ride> ride);
    int getNumberOfRides() const;
    double getTotalEarnings() const;
    std::string getDriverInfo() const;
    void displayAssignedRides() const;
};

//============================================================================
// Rider class - demonstrates encapsulation and data management
//============================================================================
class Rider {
private:
    // Private data members
    int riderID;
    std::string name;
    std::vector<std::shared_ptr<Ride>> requestedRides; // Private collection

public:
    // Constructor
    Rider(int id, const std::string& riderName);
    
    // Public accessor methods
    int getRiderID() const;
    std::string getName() const;
    
    // Methods for ride management
    void requestRide(std::shared_ptr<Ride> ride);
    int getNumberOfRequestedRides() const;
    double getTotalSpending() const;
    std::string getRiderInfo() const;
    void viewRides() const;
};

//============================================================================
// RideSharingDemo class - demonstrates system functionality
//============================================================================
class RideSharingDemo {
public:
    static void runDemo();
private:
    static void demonstratePolymorphism();
    static void demonstrateEncapsulation();
    static void demonstrateSystemFunctionality();
};

#endif // RIDESHARINGSYSTEM_H 