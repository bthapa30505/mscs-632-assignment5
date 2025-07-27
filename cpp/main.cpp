#include "RideSharingSystem.h"

//============================================================================
// Main function - Entry point for the C++ Ride Sharing System demonstration
//============================================================================

int main() {
    try {
        // Run the comprehensive demonstration of OOP principles
        RideSharingDemo::runDemo();
        
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 1;
    }
} 