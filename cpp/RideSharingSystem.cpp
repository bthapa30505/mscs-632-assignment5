#include "RideSharingSystem.h"
#include <sstream>

//============================================================================
// Base Ride class implementation
//============================================================================

Ride::Ride(int id, const std::string& pickup, const std::string& dropoff, double dist)
    : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {
}

// Accessor methods - demonstrating encapsulation
int Ride::getRideID() const {
    return rideID;
}

std::string Ride::getPickupLocation() const {
    return pickupLocation;
}

std::string Ride::getDropoffLocation() const {
    return dropoffLocation;
}

double Ride::getDistance() const {
    return distance;
}

// Base fare calculation - will be overridden in derived classes
double Ride::fare() const {
    // Base rate: $2.50 per mile
    return distance * 2.50;
}

// Base ride details method
std::string Ride::rideDetails() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Ride ID: " << rideID 
        << ", From: " << pickupLocation 
        << ", To: " << dropoffLocation 
        << ", Distance: " << distance << " miles"
        << ", Fare: $" << fare();
    return oss.str();
}

std::string Ride::getRideType() const {
    return "BASE";
}

//============================================================================
// StandardRide class implementation - demonstrates inheritance and polymorphism
//============================================================================

StandardRide::StandardRide(int id, const std::string& pickup, const std::string& dropoff, double dist)
    : Ride(id, pickup, dropoff, dist) {
}

// Override fare method - demonstrates polymorphism
double StandardRide::fare() const {
    // Standard rate: $2.00 per mile + $1.50 base fee
    return (getDistance() * 2.00) + 1.50;
}

// Override rideDetails to show ride type
std::string StandardRide::rideDetails() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "[STANDARD] Ride ID: " << getRideID() 
        << ", From: " << getPickupLocation() 
        << ", To: " << getDropoffLocation() 
        << ", Distance: " << getDistance() << " miles"
        << ", Fare: $" << fare();
    return oss.str();
}

std::string StandardRide::getRideType() const {
    return "STANDARD";
}

//============================================================================
// PremiumRide class implementation - demonstrates inheritance and polymorphism
//============================================================================

PremiumRide::PremiumRide(int id, const std::string& pickup, const std::string& dropoff, double dist)
    : Ride(id, pickup, dropoff, dist) {
}

// Override fare method - demonstrates polymorphism
double PremiumRide::fare() const {
    // Premium rate: $3.50 per mile + $5.00 base fee + 20% luxury surcharge
    double baseFare = (getDistance() * 3.50) + 5.00;
    return baseFare * 1.20; // Add 20% luxury surcharge
}

// Override rideDetails to show ride type
std::string PremiumRide::rideDetails() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "[PREMIUM] Ride ID: " << getRideID() 
        << ", From: " << getPickupLocation() 
        << ", To: " << getDropoffLocation() 
        << ", Distance: " << getDistance() << " miles"
        << ", Fare: $" << fare() << " (includes luxury surcharge)";
    return oss.str();
}

std::string PremiumRide::getRideType() const {
    return "PREMIUM";
}

//============================================================================
// Driver class implementation - demonstrates encapsulation
//============================================================================

Driver::Driver(int id, const std::string& driverName, double driverRating)
    : driverID(id), name(driverName), rating(driverRating) {
    // assignedRides vector is automatically initialized as empty
}

// Public accessor methods
int Driver::getDriverID() const {
    return driverID;
}

std::string Driver::getName() const {
    return name;
}

double Driver::getRating() const {
    return rating;
}

// Method to add a ride - demonstrates controlled access to private data
void Driver::addRide(std::shared_ptr<Ride> ride) {
    assignedRides.push_back(ride);
    std::cout << "Ride " << ride->getRideID() << " assigned to driver " << name << std::endl;
}

// Method to get number of completed rides
int Driver::getNumberOfRides() const {
    return static_cast<int>(assignedRides.size());
}

// Method to calculate total earnings
double Driver::getTotalEarnings() const {
    double total = 0.0;
    for (const auto& ride : assignedRides) {
        total += ride->fare();
    }
    return total;
}

// Method to get driver information - controlled access to internal data
std::string Driver::getDriverInfo() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Driver ID: " << driverID 
        << ", Name: " << name 
        << ", Rating: " << rating << " stars"
        << ", Completed Rides: " << getNumberOfRides()
        << ", Total Earnings: $" << getTotalEarnings();
    return oss.str();
}

// Method to display all assigned rides
void Driver::displayAssignedRides() const {
    std::cout << "Rides for driver " << name << ":" << std::endl;
    if (assignedRides.empty()) {
        std::cout << "  No rides assigned" << std::endl;
    } else {
        for (const auto& ride : assignedRides) {
            std::cout << "  - " << ride->rideDetails() << std::endl;
        }
    }
}

//============================================================================
// Rider class implementation - demonstrates encapsulation and data management
//============================================================================

Rider::Rider(int id, const std::string& riderName)
    : riderID(id), name(riderName) {
    // requestedRides vector is automatically initialized as empty
}

// Public accessor methods
int Rider::getRiderID() const {
    return riderID;
}

std::string Rider::getName() const {
    return name;
}

// Method to request a ride
void Rider::requestRide(std::shared_ptr<Ride> ride) {
    requestedRides.push_back(ride);
    std::cout << "Ride " << ride->getRideID() << " requested by " << name << std::endl;
}

// Method to get number of requested rides
int Rider::getNumberOfRequestedRides() const {
    return static_cast<int>(requestedRides.size());
}

// Method to calculate total spending
double Rider::getTotalSpending() const {
    double total = 0.0;
    for (const auto& ride : requestedRides) {
        total += ride->fare();
    }
    return total;
}

// Method to get rider information
std::string Rider::getRiderInfo() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << "Rider ID: " << riderID 
        << ", Name: " << name 
        << ", Requested Rides: " << getNumberOfRequestedRides()
        << ", Total Spending: $" << getTotalSpending();
    return oss.str();
}

// Method to view ride history
void Rider::viewRides() const {
    std::cout << "Ride history for " << name << ":" << std::endl;
    if (requestedRides.empty()) {
        std::cout << "  No rides requested" << std::endl;
    } else {
        for (const auto& ride : requestedRides) {
            std::cout << "  - " << ride->rideDetails() << std::endl;
        }
    }
}

//============================================================================
// RideSharingDemo class implementation - demonstrates system functionality
//============================================================================

void RideSharingDemo::runDemo() {
    // Demonstrate all OOP principles
    demonstratePolymorphism();
    demonstrateEncapsulation();
    demonstrateSystemFunctionality();
}

void RideSharingDemo::demonstratePolymorphism() {
    std::cout << "1. CREATING DIFFERENT RIDE TYPES (Inheritance & Polymorphism)" << std::endl;
    std::cout << "-----------------------------------------------------------" << std::endl;

    // Create rides of different types - demonstrates inheritance
    std::vector<std::shared_ptr<Ride>> rides;
    rides.push_back(std::make_shared<Ride>(101, "Downtown", "Airport", 15.0));
    rides.push_back(std::make_shared<StandardRide>(102, "Mall", "University", 8.0));
    rides.push_back(std::make_shared<StandardRide>(103, "Hotel", "Conference Center", 5.0));
    rides.push_back(std::make_shared<PremiumRide>(104, "Luxury Hotel", "Business District", 10.0));
    rides.push_back(std::make_shared<PremiumRide>(105, "Airport", "Resort", 20.0));

    // Demonstrate polymorphism - same method call, different behavior
    std::cout << "Polymorphic fare calculation and ride details:" << std::endl;
    for (const auto& ride : rides) {
        std::cout << "  " << ride->rideDetails() << std::endl;
    }
    std::cout << std::endl;

    // Polymorphism summary - same distance, different fares
    std::cout << "POLYMORPHISM SUMMARY - Same Distance, Different Fares" << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    
    double sampleDistance = 10.0;
    auto baseRide = std::make_shared<Ride>(999, "Point A", "Point B", sampleDistance);
    auto standardRide = std::make_shared<StandardRide>(998, "Point A", "Point B", sampleDistance);
    auto premiumRide = std::make_shared<PremiumRide>(997, "Point A", "Point B", sampleDistance);
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "For " << sampleDistance << " mile trips:" << std::endl;
    std::cout << "  Base Ride Fare: $" << baseRide->fare() << std::endl;
    std::cout << "  Standard Ride Fare: $" << standardRide->fare() << std::endl;
    std::cout << "  Premium Ride Fare: $" << premiumRide->fare() << std::endl;
    std::cout << std::endl;
}

void RideSharingDemo::demonstrateEncapsulation() {
    std::cout << "2. CREATED DRIVERS AND RIDERS (Encapsulation)" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    // Create drivers - demonstrating encapsulation
    Driver alice(501, "Alice Johnson", 4.8);
    Driver bob(502, "Bob Smith", 4.5);
    Driver charlie(503, "Charlie Brown", 4.9);

    // Create riders
    Rider emma(301, "Emma Wilson");
    Rider david(302, "David Lee");
    Rider sarah(303, "Sarah Davis");
}

void RideSharingDemo::demonstrateSystemFunctionality() {
    std::cout << "3. SYSTEM FUNCTIONALITY DEMONSTRATION" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    // Create rides
    auto ride1 = std::make_shared<Ride>(101, "Downtown", "Airport", 15.0);
    auto ride2 = std::make_shared<StandardRide>(102, "Mall", "University", 8.0);
    auto ride3 = std::make_shared<StandardRide>(103, "Hotel", "Conference Center", 5.0);
    auto ride4 = std::make_shared<PremiumRide>(104, "Luxury Hotel", "Business District", 10.0);
    auto ride5 = std::make_shared<PremiumRide>(105, "Airport", "Resort", 20.0);

    // Create drivers and riders
    Driver alice(501, "Alice Johnson", 4.8);
    Driver bob(502, "Bob Smith", 4.5);
    Driver charlie(503, "Charlie Brown", 4.9);
    
    Rider emma(301, "Emma Wilson");
    Rider david(302, "David Lee");
    Rider sarah(303, "Sarah Davis");

    std::cout << "Assigning rides to drivers:" << std::endl;
    alice.addRide(ride1);
    alice.addRide(ride2);
    bob.addRide(ride3);
    bob.addRide(ride4);
    charlie.addRide(ride5);
    std::cout << std::endl;

    std::cout << "Riders requesting rides:" << std::endl;
    emma.requestRide(ride1);
    emma.requestRide(ride2);
    david.requestRide(ride3);
    david.requestRide(ride4);
    sarah.requestRide(ride5);
    std::cout << std::endl;

    std::cout << "Final driver information:" << std::endl;
    std::cout << "  " << alice.getDriverInfo() << std::endl;
    std::cout << "  " << bob.getDriverInfo() << std::endl;
    std::cout << "  " << charlie.getDriverInfo() << std::endl;
    std::cout << std::endl;

    std::cout << "Final rider information:" << std::endl;
    std::cout << "  " << emma.getRiderInfo() << std::endl;
    std::cout << "  " << david.getRiderInfo() << std::endl;
    std::cout << "  " << sarah.getRiderInfo() << std::endl;
    std::cout << std::endl;

    std::cout << "Detailed driver assignments:" << std::endl;
    alice.displayAssignedRides();
    bob.displayAssignedRides();
    charlie.displayAssignedRides();
    std::cout << std::endl;

    std::cout << "Detailed rider history:" << std::endl;
    emma.viewRides();
    david.viewRides();
    sarah.viewRides();
    std::cout << std::endl;
} 