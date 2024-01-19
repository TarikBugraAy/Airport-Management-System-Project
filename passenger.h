// passenger.h

// Header guard to prevent multiple inclusions of this header file
#ifndef PASSENGER_H
#define PASSENGER_H

// Definition of the Passenger struct
typedef struct {
    int passengerID;                   // Unique identifier for a passenger
    char name[100];                    // Passenger's name
    char passportNumber[20];           // Passport number of the passenger
    char nationality[50];              // Nationality of the passenger
    char dateOfBirth[10];              // Date of birth in YYYY-MM-DD format
    char flightID[10];                 // ID of the flight the passenger is on
} Passenger;

// Function declarations

// Adds a new passenger to the passengers database
void addPassenger();

// Updates details of an existing passenger
void updatePassenger();

// Deletes a passenger from the passengers database
void deletePassenger();

// Searches for passengers based on different criteria
void searchPassengers();

// Lists all passengers or filters them based on certain criteria
void listPassengers();

// Counts the number of passengers based on specific criteria
void countPassengers();

// End of header guard
#endif // PASSENGER_H
