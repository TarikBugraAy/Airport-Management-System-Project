#include "flight.h"
#include <ctype.h>  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"



#define MAX_FLIGHT_LINE_LENGTH 200



void printFlightInfo(const char *flightID) {
    FILE *file = fopen("flights.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_FLIGHT_LINE_LENGTH];
    int found = 0;

    // Read the header line and ignore
    fgets(line, MAX_FLIGHT_LINE_LENGTH, file);

    if (strcmp(flightID, "0") == 0) {
        printf("All Flights Information:\n");
        while (fgets(line, MAX_FLIGHT_LINE_LENGTH, file) != NULL) {
            printf("%s", line);
        }
        found = 1;
    } else {
        while (fgets(line, MAX_FLIGHT_LINE_LENGTH, file) != NULL) {
            char currentID[10];
            sscanf(line, "%9[^,]", currentID);  // Parse the FlightID

            if (strcmp(currentID, flightID) == 0) {
                printf("Flight Information:\n%s", line);
                found = 1;
                break;
            }
        }
    }

    fclose(file);

    if (!found) {
        printf("Flight with ID %s not found.\n", flightID);
    }
}

void addFlight() {
    FILE *file = fopen("flights.txt", "a"); // Append mode
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    char flightID[10], aircraftModel[50], pilot[50], date[20], type[20], destination[50], airline[50], departureTime[10], arrivalTime[10];
    int passengerCapacity;

    printf("Enter Flight ID: ");
    scanf("%9s", flightID);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Aircraft Model: ");
    scanf("%49s", aircraftModel);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Pilot: ");
    scanf("%49s", pilot);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%19s", date);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Type (Departure/Arrival): ");
    scanf("%19s", type);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Destination: ");
    scanf("%49s", destination);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Airline: ");
    scanf("%49s", airline);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Departure Time (HH:MM): ");
    scanf("%9s", departureTime);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Arrival Time (HH:MM): ");
    scanf("%9s", arrivalTime);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter Passenger Capacity: ");
    scanf("%d", &passengerCapacity);
    while (getchar() != '\n'); // Clear input buffer

    fprintf(file, "%s, %s, %s, %s, %s, %s, %s, %s, %s, %d\n", flightID, aircraftModel, pilot, date, type, destination, airline, departureTime, arrivalTime, passengerCapacity);
    
    printf("Flight %s added successfully.\n", flightID);

    fclose(file);
}

void deleteFlight(const char *flightID) {
    FILE *file = fopen("flights.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp_flights.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[MAX_FLIGHT_LINE_LENGTH];
    int found = 0;

    // Copy header line to the temporary file
    fgets(line, MAX_FLIGHT_LINE_LENGTH, file);
    fprintf(tempFile, "%s", line);

    while (fgets(line, MAX_FLIGHT_LINE_LENGTH, file) != NULL) {
        char currentID[10];
        sscanf(line, "%9[^,]", currentID);  // Parse the FlightID

        if (strcmp(currentID, flightID) != 0) {
            fprintf(tempFile, "%s", line);
        } else {
            found = 1;  // Mark that the flight was found and deleted
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        // Remove the original file and rename the temporary file
        remove("flights.txt");
        rename("temp_flights.txt", "flights.txt");
        printf("Flight with ID %s deleted successfully.\n", flightID);
    } else {
        remove("temp_flights.txt");
        printf("Flight with ID %s not found.\n", flightID);
    }
}


void updateFlight(const char *flightID) {
    FILE *file = fopen("flights.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp_flights.txt", "w");
    if (!tempFile) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[MAX_FLIGHT_LINE_LENGTH];
    int found = 0;

    // Copy header line to the temporary file
    fgets(line, MAX_FLIGHT_LINE_LENGTH, file);
    fprintf(tempFile, "%s", line);

    while (fgets(line, MAX_FLIGHT_LINE_LENGTH, file) != NULL) {
        char currentID[10];
        sscanf(line, "%9[^,]", currentID);  // Parse the FlightID

        if (strcmp(currentID, flightID) == 0) {
            found = 1;

            // Collect new flight details from user
            char newAircraftModel[50], newPilot[50], newDate[20], newType[20], newDestination[50], newAirline[50], newDepartureTime[10], newArrivalTime[10];
            int newPassengerCapacity;
            printf("Enter new Aircraft Model: ");
            scanf("%49s", newAircraftModel);
            printf("Enter new Date (YYYY-MM-DD): ");
            scanf("%19s", newDate);
            printf("Enter new Type (Departure/Arrival): ");
            scanf("%19s", newType);
            printf("Enter new Destination: ");
            scanf("%49s", newDestination);
            printf("Enter new Airline: ");
            scanf("%49s", newAirline);
            
          
            printf("Enter new Passenger Capacity: ");
            scanf("%d", &newPassengerCapacity);
             printf("Enter new Pilot: ");
            scanf("%49s", newPilot);
            printf("Enter new Departure Time (HH:MM): ");
            scanf("%9s", newDepartureTime);
              printf("Enter new Arrival Time (HH:MM): ");
            scanf("%9s", newArrivalTime);

            // Write the updated flight details to the temp file
            fprintf(tempFile, "%s, %s, %s, %s, %s, %s, %s, %s, %s, %d\n", flightID, newAircraftModel, newPilot, newDate, newType, newDestination, newAirline, newDepartureTime, newArrivalTime, newPassengerCapacity);
        } else {
            // Write the existing line to the temp file
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        // Replace the original file with the updated temporary file
        remove("flights.txt");
        rename("temp_flights.txt", "flights.txt");
        printf("Flight with ID %s updated successfully.\n", flightID);
    } else {
        remove("temp_flights.txt");
        printf("Flight with ID %s not found.\n", flightID);
    }
}



void searchFlights() {
    FILE *file = fopen("flights.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    int choice;
    char searchTerm[50], line[MAX_FLIGHT_LINE_LENGTH];

    printf("Search Flights by:\n");
    printf("1. FlightID\n2. Date\n3. Destination\n4. Type (Departure/Arrival)\n5. Flights After a Date\n6. Flights Before a Date\nEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter search term: ");
    scanf("%49s", searchTerm);
    for (int i = 0; searchTerm[i]; ++i) {
        searchTerm[i] = tolower(searchTerm[i]); // Convert search term to lowercase
    }

    fgets(line, MAX_FLIGHT_LINE_LENGTH, file); // Skip header

    while (fgets(line, MAX_FLIGHT_LINE_LENGTH, file)) {
        char flightID[10], date[20], destination[50], type[20], lowerCaseDestination[50], lowerCaseType[20];
        sscanf(line, "%9[^,],%*[^,],%*[^,],%19[^,],%19[^,],%49[^,]", flightID, date, type, destination);

        // Convert to lowercase for case-insensitive comparison
        for (int i = 0; destination[i]; ++i) {
            lowerCaseDestination[i] = tolower(destination[i]);
        }
        lowerCaseDestination[strlen(destination)] = '\0';

        for (int i = 0; type[i]; ++i) {
            lowerCaseType[i] = tolower(type[i]);
        }
        lowerCaseType[strlen(type)] = '\0';

        int meetsCriteria = 0;
        switch (choice) {
            case 1: // Search by FlightID
                for (int i = 0; flightID[i]; ++i) {
                    flightID[i] = tolower(flightID[i]);
                }
                meetsCriteria = strcmp(flightID, searchTerm) == 0;
                break;
            case 2: // Search by date
                meetsCriteria = strstr(date, searchTerm) != NULL;
                break;
            case 3: // Search by destination
                meetsCriteria = strstr(lowerCaseDestination, searchTerm) != NULL;
                break;
            case 4: // Search by type
                meetsCriteria = strstr(lowerCaseType, searchTerm) != NULL;
                break;
            case 5: // Search flights after a date
                if (compareDates(date, searchTerm) > 0) {
                    meetsCriteria = 1;
                }
                break;
            case 6: // Search flights before a date
                if (compareDates(date, searchTerm) < 0) {
                    meetsCriteria = 1;
                }
                break;
        }

        if (meetsCriteria) {
            printf("%s", line);
        }
    }

    fclose(file);
}

void countFlights() {
    FILE *file = fopen("flights.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    int count = 0;
    char line[MAX_FLIGHT_LINE_LENGTH];

    // Skip the header line
    fgets(line, MAX_FLIGHT_LINE_LENGTH, file);

    while (fgets(line, MAX_FLIGHT_LINE_LENGTH, file)) {
        if (strcmp(line, "\n") != 0) {
            // Increment count for each non-empty line
            count++;
        }
    }

    fclose(file);
    printf("Total number of flights: %d\n", count);
}

