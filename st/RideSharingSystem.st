"============================================================================
 Ride Sharing System in Smalltalk
 Demonstrating OOP principles: Encapsulation, Inheritance, and Polymorphism
============================================================================"

"Base Ride class - demonstrates encapsulation"
Object subclass: Ride [
    | rideID pickupLocation dropoffLocation distance |
    
    "Class method to create a new ride"
    Ride class >> newWithID: anID pickup: pickup dropoff: dropoff distance: dist [
        ^(self new)
            initializeWithID: anID pickup: pickup dropoff: dropoff distance: dist;
            yourself
    ]
    
    "Initialize instance variables"
    initializeWithID: anID pickup: pickup dropoff: dropoff distance: dist [
        rideID := anID.
        pickupLocation := pickup.
        dropoffLocation := dropoff.
        distance := dist.
    ]
    
    "Accessor methods - demonstrating encapsulation"
    rideID [
        ^rideID
    ]
    
    pickupLocation [
        ^pickupLocation
    ]
    
    dropoffLocation [
        ^dropoffLocation
    ]
    
    distance [
        ^distance
    ]
    
    "Base fare calculation method - will be overridden in subclasses"
    fare [
        "Base rate: $2.50 per mile"
        ^distance * 2.50
    ]
    
    "Method to display ride details"
    rideDetails [
        | fareAmount |
        fareAmount := self fare.
        ^'Ride ID: ', rideID printString, 
         ', From: ', pickupLocation, 
         ', To: ', dropoffLocation, 
         ', Distance: ', distance printString, ' miles',
         ', Fare: $', (fareAmount printString)
    ]
    
    "Display method for easy printing"
    printOn: aStream [
        aStream nextPutAll: self rideDetails
    ]
]

"============================================================================
 StandardRide subclass - demonstrates inheritance and polymorphism
============================================================================"

Ride subclass: StandardRide [
    "Inherits all instance variables from Ride"
    
    "Override fare method - demonstrates polymorphism"
    fare [
        "Standard rate: $2.00 per mile + $1.50 base fee"
        ^(distance * 2.00) + 1.50
    ]
    
    "Override rideDetails to show ride type"
    rideDetails [
        | fareAmount |
        fareAmount := self fare.
        ^'[STANDARD] Ride ID: ', rideID printString, 
         ', From: ', pickupLocation, 
         ', To: ', dropoffLocation, 
         ', Distance: ', distance printString, ' miles',
         ', Fare: $', (fareAmount printString)
    ]
]

"============================================================================
 PremiumRide subclass - demonstrates inheritance and polymorphism
============================================================================"

Ride subclass: PremiumRide [
    "Inherits all instance variables from Ride"
    
    "Override fare method - demonstrates polymorphism"
    fare [
        "Premium rate: $3.50 per mile + $5.00 base fee + 20% luxury surcharge"
        | baseFare |
        baseFare := (distance * 3.50) + 5.00.
        ^baseFare * 1.20  "Add 20% luxury surcharge"
    ]
    
    "Override rideDetails to show ride type"
    rideDetails [
        | fareAmount |
        fareAmount := self fare.
        ^'[PREMIUM] Ride ID: ', rideID printString, 
         ', From: ', pickupLocation, 
         ', To: ', dropoffLocation, 
         ', Distance: ', distance printString, ' miles',
         ', Fare: $', (fareAmount printString), ' (includes luxury surcharge)'
    ]
]

"============================================================================
 Driver class - demonstrates encapsulation with private assignedRides collection
============================================================================"

Object subclass: Driver [
    | driverID name rating assignedRides |
    
    "Class method to create a new driver"
    Driver class >> newWithID: anID name: aName rating: aRating [
        ^(self new)
            initializeWithID: anID name: aName rating: aRating;
            yourself
    ]
    
    "Initialize driver - assignedRides is private (encapsulated)"
    initializeWithID: anID name: aName rating: aRating [
        driverID := anID.
        name := aName.
        rating := aRating.
        assignedRides := OrderedCollection new.  "Private collection"
    ]
    
    "Public accessor methods"
    driverID [
        ^driverID
    ]
    
    name [
        ^name
    ]
    
    rating [
        ^rating
    ]
    
    "Method to add a ride - demonstrates controlled access to private data"
    addRide: aRide [
        assignedRides add: aRide.
        ^'Ride ', aRide rideID printString, ' assigned to driver ', name
    ]
    
    "Method to get number of completed rides"
    numberOfRides [
        ^assignedRides size
    ]
    
    "Method to calculate total earnings"
    totalEarnings [
        | total |
        total := 0.
        assignedRides do: [:ride | total := total + ride fare].
        ^total
    ]
    
    "Method to get driver information - controlled access to internal data"
    getDriverInfo [
        | info earnings ratingDisplay |
        earnings := self totalEarnings.
        ratingDisplay := (rating // 10) printString, '.', ((rating \\ 10) printString).
        info := 'Driver ID: ', driverID printString, 
                ', Name: ', name, 
                ', Rating: ', ratingDisplay, ' stars',
                ', Completed Rides: ', self numberOfRides printString,
                ', Total Earnings: $', (earnings printString).
        ^info
    ]
    
    "Method to display all assigned rides"
    displayAssignedRides [
        | result |
        result := 'Rides for driver ', name, ':'.
        assignedRides isEmpty
            ifTrue: [result := result, ' No rides assigned']
            ifFalse: [
                assignedRides do: [:ride | 
                    result := result, Character nl asString, '  - ', ride rideDetails
                ]
            ].
        ^result
    ]
    
    "Display method for easy printing"
    printOn: aStream [
        aStream nextPutAll: self getDriverInfo
    ]
]

"============================================================================
 Rider class - demonstrates encapsulation and data management
============================================================================"

Object subclass: Rider [
    | riderID name requestedRides |
    
    "Class method to create a new rider"
    Rider class >> newWithID: anID name: aName [
        ^(self new)
            initializeWithID: anID name: aName;
            yourself
    ]
    
    "Initialize rider with empty ride history"
    initializeWithID: anID name: aName [
        riderID := anID.
        name := aName.
        requestedRides := OrderedCollection new.
    ]
    
    "Public accessor methods"
    riderID [
        ^riderID
    ]
    
    name [
        ^name
    ]
    
    "Method to request a ride"
    requestRide: aRide [
        requestedRides add: aRide.
        ^'Ride ', aRide rideID printString, ' requested by ', name
    ]
    
    "Method to get number of requested rides"
    numberOfRequestedRides [
        ^requestedRides size
    ]
    
    "Method to calculate total spending"
    totalSpending [
        | total |
        total := 0.
        requestedRides do: [:ride | total := total + ride fare].
        ^total
    ]
    
    "Method to view ride history"
    viewRides [
        | result |
        result := 'Ride history for ', name, ':'.
        requestedRides isEmpty
            ifTrue: [result := result, ' No rides requested']
            ifFalse: [
                requestedRides do: [:ride | 
                    result := result, Character nl asString, '  - ', ride rideDetails
                ]
            ].
        ^result
    ]
    
    "Method to get rider information"
    getRiderInfo [
        | info spending |
        spending := self totalSpending.
        info := 'Rider ID: ', riderID printString, 
                ', Name: ', name, 
                ', Requested Rides: ', self numberOfRequestedRides printString,
                ', Total Spending: $', (spending printString).
        ^info
    ]
    
    "Display method for easy printing"
    printOn: aStream [
        aStream nextPutAll: self getRiderInfo
    ]
]

"============================================================================
 MAIN DEMONSTRATION PROGRAM
 Demonstrates all three OOP principles: Encapsulation, Inheritance, Polymorphism
============================================================================"

Object subclass: RideSharingDemo [
    "Main demonstration class"
    
    RideSharingDemo class >> runDemo [
        "Main method to demonstrate the ride sharing system"
        | rides drivers riders alice bob charlie ride1 ride2 ride3 ride4 ride5 sampleDistance baseRide standardRide premiumRide |
        
        "============================================================================
         1. INHERITANCE & POLYMORPHISM DEMONSTRATION
         Create different types of rides that inherit from base Ride class
        ============================================================================"
        
        Transcript show: '1. CREATING DIFFERENT RIDE TYPES (Inheritance & Polymorphism)'; nl.
        Transcript show: '-----------------------------------------------------------'; nl.
        
        "Create rides of different types"
        ride1 := Ride newWithID: 101 pickup: 'Downtown' dropoff: 'Airport' distance: 15.
        ride2 := StandardRide newWithID: 102 pickup: 'Mall' dropoff: 'University' distance: 8.
        ride3 := StandardRide newWithID: 103 pickup: 'Hotel' dropoff: 'Conference Center' distance: 5.
        ride4 := PremiumRide newWithID: 104 pickup: 'Luxury Hotel' dropoff: 'Business District' distance: 10.
        ride5 := PremiumRide newWithID: 105 pickup: 'Airport' dropoff: 'Resort' distance: 20.
        
        "Store all rides in a collection - demonstrating polymorphism"
        rides := OrderedCollection new.
        rides add: ride1; add: ride2; add: ride3; add: ride4; add: ride5.
        
        "Demonstrate polymorphism - same method call, different behavior"
        Transcript show: 'Polymorphic fare calculation and ride details:'; nl.
        rides do: [:ride |
            Transcript show: '  ', ride rideDetails; nl.
        ].
        Transcript nl.
        
        "============================================================================
         2. ENCAPSULATION DEMONSTRATION
         Create drivers and riders with private data and controlled access
        ============================================================================"
        
        Transcript show: '2. CREATING DRIVERS AND RIDERS (Encapsulation)'; nl.
        Transcript show: '----------------------------------------------'; nl.
        
        "Create drivers - demonstrating encapsulation"
        alice := Driver newWithID: 501 name: 'Alice Johnson' rating: 48.
        bob := Driver newWithID: 502 name: 'Bob Smith' rating: 45.
        charlie := Driver newWithID: 503 name: 'Charlie Brown' rating: 49.
        
        drivers := OrderedCollection new.
        drivers add: alice; add: bob; add: charlie.
        
        "Create riders"
        riders := OrderedCollection new.
        riders add: (Rider newWithID: 301 name: 'Emma Wilson');
               add: (Rider newWithID: 302 name: 'David Lee');
               add: (Rider newWithID: 303 name: 'Sarah Davis').
        
        Transcript show: 'Initial driver information:'; nl.
        drivers do: [:driver |
            Transcript show: '  ', driver printString; nl.
        ].
        Transcript nl.
        
        "============================================================================
         3. SYSTEM FUNCTIONALITY DEMONSTRATION
         Assign rides to drivers and riders (demonstrating encapsulation)
        ============================================================================"
        
        Transcript show: '3. ASSIGNING RIDES (System Functionality)'; nl.
        Transcript show: '----------------------------------------'; nl.
        
        "Assign rides to drivers - accessing private data through public methods"
        Transcript show: (alice addRide: ride1); nl.
        Transcript show: (alice addRide: ride2); nl.
        Transcript show: (bob addRide: ride3); nl.
        Transcript show: (bob addRide: ride4); nl.
        Transcript show: (charlie addRide: ride5); nl.
        Transcript nl.
        
        "Assign rides to riders"
        Transcript show: ((riders at: 1) requestRide: ride1); nl.
        Transcript show: ((riders at: 1) requestRide: ride2); nl.
        Transcript show: ((riders at: 2) requestRide: ride3); nl.
        Transcript show: ((riders at: 2) requestRide: ride4); nl.
        Transcript show: ((riders at: 3) requestRide: ride5); nl.
        Transcript nl.
        
        "============================================================================
         4. FINAL SYSTEM STATE
         Display updated information using encapsulated data access
        ============================================================================"
        
        Transcript show: '4. FINAL SYSTEM STATE'; nl.
        Transcript show: '--------------------'; nl.
        
        Transcript show: 'Updated Driver Information:'; nl.
        drivers do: [:driver |
            Transcript show: '  ', driver printString; nl.
        ].
        Transcript nl.
        
        Transcript show: 'Rider Information:'; nl.
        riders do: [:rider |
            Transcript show: '  ', rider printString; nl.
        ].
        Transcript nl.
        
        "Detailed ride assignments"
        Transcript show: 'Detailed Driver Assignments:'; nl.
        drivers do: [:driver |
            Transcript show: driver displayAssignedRides; nl.
        ].
        Transcript nl.
        
        "Detailed rider history"
        Transcript show: 'Detailed Rider History:'; nl.
        riders do: [:rider |
            Transcript show: rider viewRides; nl.
        ].
        Transcript nl.
        
        "============================================================================
         5. POLYMORPHISM SUMMARY
         Show how different ride types calculate fares differently
        ============================================================================"
        
        Transcript show: '5. POLYMORPHISM SUMMARY - Same Distance, Different Fares'; nl.
        Transcript show: '-------------------------------------------------------'; nl.
        
        "Create rides of same distance but different types"
        sampleDistance := 10.
        baseRide := Ride newWithID: 999 pickup: 'Point A' dropoff: 'Point B' distance: sampleDistance.
        standardRide := StandardRide newWithID: 998 pickup: 'Point A' dropoff: 'Point B' distance: sampleDistance.
        premiumRide := PremiumRide newWithID: 997 pickup: 'Point A' dropoff: 'Point B' distance: sampleDistance.
        
        Transcript show: 'For ', sampleDistance printString, ' mile trips:'; nl.
        Transcript show: '  Base Ride Fare: $', (baseRide fare printString); nl.
        Transcript show: '  Standard Ride Fare: $', (standardRide fare printString); nl.
        Transcript show: '  Premium Ride Fare: $', (premiumRide fare printString); nl.
        Transcript nl.
        
        ^'Demo completed successfully!'
    ]
] 