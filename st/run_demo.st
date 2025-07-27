"============================================================================
 Smalltalk Ride Sharing System - Demo Runner
 Load and execute the ride sharing system demonstration
============================================================================"

"File-in the main system"
FileStream fileIn: 'RideSharingSystem.st'.

"Run the demonstration"
RideSharingDemo runDemo.

"Exit gracefully"
ObjectMemory quit. 