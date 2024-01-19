// Header guard to prevent multiple inclusion of the same header
#ifndef FLIGHT_H
#define FLIGHT_H

// Function prototypes for managing flight-related functionalities

// Function to print information about a specific flight or all flights
// Takes a flight ID as a parameter; passing "0" will print all flight information
void printFlightInfo(const char *flightID);

// Function to add a new flight to the system
// Prompts the user for flight details and appends it to the flight data file
void addFlight();

// Function to delete a flight from the system
// Takes a flight ID as a parameter and removes the corresponding flight
void deleteFlight(const char *flightID);

// Function to update details of an existing flight
// Takes a flight ID as a parameter and allows the user to modify flight details
void updateFlight(const char *flightID);

// Function to search for flights based on various criteria
// Allows searching by ID, date, destination, type, and dates before/after a specific date
void searchFlights();

// Function to count the total number of flights in the system
// Counts and prints the number of entries in the flight data file
void countFlights();

#endif // FLIGHT_H
