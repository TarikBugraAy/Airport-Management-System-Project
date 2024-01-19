#include "passenger.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSENGER_LINE_LENGTH 200

void addPassenger() {
    FILE *file = fopen("passengers.txt", "a+");
    if (!file) {
        printf("Error opening passengers file.\n");
        return;
    }

    char name[50], passportNumber[20], nationality[30], dateOfBirth[11], flightID[10];
    int maxID = 0;

    // Find the next PassengerID
    char line[MAX_PASSENGER_LINE_LENGTH];
    while (fgets(line, MAX_PASSENGER_LINE_LENGTH, file) != NULL) {
        int currentID;
        sscanf(line, "%d", &currentID);
        if (currentID > maxID) {
            maxID = currentID;
        }
    }

    int newID = maxID + 1;

    printf("Enter Passenger Name: ");
    scanf("%49[^\n]%*c", name);
    printf("Enter Passport Number: ");
    scanf("%19s", passportNumber);
    printf("Enter Nationality: ");
    scanf("%29s", nationality);
    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf("%10s", dateOfBirth);
    printf("Enter FlightID: ");
    scanf("%9s", flightID);

    if (!validateFlightID(flightID)) {
        printf("Invalid FlightID. Passenger not added.\n");
        fclose(file);
        return;
    }

    fprintf(file, "%04d, %s, %s, %s, %s, %s\n", newID, name, passportNumber, nationality, dateOfBirth, flightID);
    fclose(file);

    printf("Passenger added successfully.\n");
}

void updatePassenger() {
    FILE *file = fopen("passengers.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp_passengers.txt", "w");
    if (!tempFile) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[MAX_PASSENGER_LINE_LENGTH], passengerID[10];
    int found = 0;

    // Copy header line to the temporary file
    fgets(line, MAX_PASSENGER_LINE_LENGTH, file);
    fprintf(tempFile, "%s", line);

    printf("Enter Passenger ID to update: ");
    scanf("%9s", passengerID);

    while (fgets(line, MAX_PASSENGER_LINE_LENGTH, file) != NULL) {
        char currentID[10];
        sscanf(line, "%9[^,]", currentID);  // Parse the PassengerID

        if (strcmp(currentID, passengerID) == 0) {
            found = 1;

            // Collect new passenger details from user
            char newName[50], newPassportNumber[20], newNationality[30], newDateOfBirth[20], newFlightID[10];
            printf("Enter new Name: ");
            scanf(" %[^\n]", newName);  // Use space before % to skip leading whitespace
            printf("Enter new Passport Number: ");
            scanf(" %[^\n]", newPassportNumber);
            printf("Enter new Nationality: ");
            scanf(" %[^\n]", newNationality);
            printf("Enter new Date of Birth (YYYY-MM-DD): ");
            scanf(" %[^\n]", newDateOfBirth);
            
            do {
                printf("Enter new Flight ID: ");
                scanf(" %9s", newFlightID);
            } while (!validateFlightID(newFlightID));

            // Write the updated passenger details to the temp file
            fprintf(tempFile, "%s, %s, %s, %s, %s, %s\n", currentID, newName, newPassportNumber, newNationality, newDateOfBirth, newFlightID);
        } else {
            // Write the existing line to the temp file
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        // Replace the original file with the updated temporary file
        remove("passengers.txt");
        rename("temp_passengers.txt", "passengers.txt");
        printf("Passenger with ID %s updated successfully.\n", passengerID);
    } else {
        remove("temp_passengers.txt");
        printf("Passenger with ID %s not found.\n", passengerID);
    }
}



void deletePassenger() {
    FILE *file = fopen("passengers.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    FILE *tempFile = fopen("temp_passengers.txt", "w");
    if (!tempFile) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[MAX_PASSENGER_LINE_LENGTH], passengerID[10];
    int found = 0;

    // Copy header line to the temporary file
    fgets(line, MAX_PASSENGER_LINE_LENGTH, file);
    fprintf(tempFile, "%s", line);

    printf("Enter Passenger ID to delete: ");
    scanf("%9s", passengerID);

    while (fgets(line, MAX_PASSENGER_LINE_LENGTH, file) != NULL) {
        char currentID[10];
        sscanf(line, "%9[^,]", currentID);  // Parse the PassengerID

        if (strcmp(currentID, passengerID) != 0) {
            // Write all lines except the one to be deleted to the temp file
            fprintf(tempFile, "%s", line);
        } else {
            found = 1;  // Mark that the passenger was found and deleted
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        // Remove the original file and rename the temporary file
        remove("passengers.txt");
        rename("temp_passengers.txt", "passengers.txt");
        printf("Passenger with ID %s deleted successfully.\n", passengerID);
    } else {
        remove("temp_passengers.txt");
        printf("Passenger with ID %s not found.\n", passengerID);
    }
}

void searchPassengers() {
    FILE *file = fopen("passengers.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    int choice;
    char searchTerm[50], line[MAX_PASSENGER_LINE_LENGTH];

    printf("Search Passengers by:\n");
    printf("1. PassengerID\n2. Name\n3. PassportNumber\n4. Nationality\n5. DateOfBirth\n6. FlightID\nEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer

    printf("Enter search term: ");
    scanf("%49[^\n]", searchTerm);
    for (int i = 0; searchTerm[i]; ++i) {
        searchTerm[i] = tolower(searchTerm[i]); // Convert search term to lowercase for case-insensitive search
    }

    fgets(line, MAX_PASSENGER_LINE_LENGTH, file); // Skip header

    int found = 0;
    while (fgets(line, MAX_PASSENGER_LINE_LENGTH, file)) {
        char lowerCaseLine[MAX_PASSENGER_LINE_LENGTH];
        strcpy(lowerCaseLine, line);
        for (int i = 0; lowerCaseLine[i]; ++i) {
            lowerCaseLine[i] = tolower(lowerCaseLine[i]);
        }

        char *foundPtr = NULL;
        switch (choice) {
            case 1: // Search by PassengerID
            case 2: // Search by Name
            case 3: // Search by PassportNumber
            case 4: // Search by Nationality
            case 5: // Search by DateOfBirth
            case 6: // Search by FlightID
                foundPtr = strstr(lowerCaseLine, searchTerm);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                fclose(file);
                return;
        }

        if (foundPtr) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("No passengers found matching the criteria.\n");
    }

    fclose(file);
}

void listPassengers() {
    FILE *file = fopen("passengers.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    int choice;
    printf("List Passengers by:\n1. All\n2. FlightID\n3. Nationality\nEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer

    char searchTerm[50];
    if (choice == 2 || choice == 3) {
        printf("Enter search term: ");
        scanf("%49s", searchTerm);
        // Convert searchTerm to lowercase for case-insensitive comparison
        for (int i = 0; searchTerm[i]; ++i) {
            searchTerm[i] = tolower(searchTerm[i]);
        }
    }

    char line[MAX_PASSENGER_LINE_LENGTH];
    fgets(line, MAX_PASSENGER_LINE_LENGTH, file); // Skip header if necessary

    printf("\nList of Passengers:\n");
    while (fgets(line, MAX_PASSENGER_LINE_LENGTH, file) != NULL) {
        char currentFlightID[10], currentNationality[30];
        if (choice == 2) { // By FlightID
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%9[^,\n]", currentFlightID);
            char lowerCaseFlightID[10];
            for (int i = 0; currentFlightID[i]; ++i) {
                lowerCaseFlightID[i] = tolower(currentFlightID[i]);
            }
            lowerCaseFlightID[strlen(currentFlightID)] = '\0';

            if (strstr(lowerCaseFlightID, searchTerm) != NULL) {
                printf("%s", line);
            }
        } else if (choice == 3) { // By Nationality
            sscanf(line, "%*[^,],%*[^,],%*[^,],%29[^,]", currentNationality);
            char lowerCaseNationality[30];
            for (int i = 0; currentNationality[i]; ++i) {
                lowerCaseNationality[i] = tolower(currentNationality[i]);
            }
            lowerCaseNationality[strlen(currentNationality)] = '\0';

            if (strstr(lowerCaseNationality, searchTerm) != NULL) {
                printf("%s", line);
            }
        } else {
            // Print all passengers
            printf("%s", line);
        }
    }

    fclose(file);
}

void countPassengers() {
    int choice, count = 0;
    char searchTerm[50], line[MAX_PASSENGER_LINE_LENGTH];

    printf("Count Passengers by:\n1. All\n2. FlightID\n3. Nationality\nEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // Clear input buffer

    FILE *file = fopen("passengers.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    // Convert searchTerm to lowercase for case-insensitive comparison
    if (choice == 2 || choice == 3) {
        printf("Enter search term: ");
        scanf("%49s", searchTerm);
        for (int i = 0; searchTerm[i]; ++i) {
            searchTerm[i] = tolower(searchTerm[i]);
        }
    }

    fgets(line, MAX_PASSENGER_LINE_LENGTH, file); // Skip header

    while (fgets(line, MAX_PASSENGER_LINE_LENGTH, file)) {
        // Ignore empty lines
        if (strcmp(line, "\n") == 0 || strcmp(line, "\r\n") == 0) {
            continue;
        }

        char currentFlightID[10], currentNationality[30];
        if (choice == 2) { // Count by FlightID
            sscanf(line, "%*[^,],%*[^,],%*[^,],%*[^,],%*[^,],%9[^\n]", currentFlightID);
            for (int i = 0; currentFlightID[i]; ++i) {
                currentFlightID[i] = tolower(currentFlightID[i]);
            }
            currentFlightID[strlen(currentFlightID)] = '\0';
            if (strstr(currentFlightID, searchTerm) != NULL) {
                count++;
            }
        } else if (choice == 3) { // Count by Nationality
            sscanf(line, "%*[^,],%*[^,],%*[^,],%29[^,]", currentNationality);
            for (int i = 0; currentNationality[i]; ++i) {
                currentNationality[i] = tolower(currentNationality[i]);
            }
            currentNationality[strlen(currentNationality)] = '\0';
            if (strstr(currentNationality, searchTerm) != NULL) {
                count++;
            }
        } else {
            // Count all passengers
            count++;
        }
    }

    fclose(file);
    printf("Total number of passengers: %d\n", count);
}