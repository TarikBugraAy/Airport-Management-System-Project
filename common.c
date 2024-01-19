// Implementation of common functions used across the project

#include "common.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h> // Included for strcmp function

// Definitions for the flight data file and maximum line length
#define FLIGHT_DATA_FILE "flights.txt"
#define MAX_FLIGHT_LINE_LENGTH 200

// Implementation of the case-insensitive substring search function
char* stristr(const char *haystack, const char *needle) {
    do {
        const char *h = haystack; // Pointer to traverse haystack
        const char *n = needle;   // Pointer to traverse needle

        // Compare characters case-insensitively
        while (tolower((unsigned char)*h) == tolower((unsigned char)*n) && *n) {
            h++;
            n++;
        }

        // If entire needle is found in haystack, return pointer to its position
        if (*n == 0) {
            return (char *)haystack;
        }
    } while (*haystack++);

    return NULL; // Return NULL if needle is not found in haystack
}

// Function to parse a date string into year, month, and day components
void parseDate(const char *dateStr, int *year, int *month, int *day) {
    sscanf(dateStr, "%4d-%2d-%2d", year, month, day); // Use sscanf to extract date components
}

// Function to compare two dates in YYYY-MM-DD format
int compareDates(const char *date1, const char *date2) {
    int year1, month1, day1, year2, month2, day2;

    // Parse both dates
    parseDate(date1, &year1, &month1, &day1);
    parseDate(date2, &year2, &month2, &day2);

    // Compare year, then month, then day
    if (year1 != year2) return year1 - year2;
    if (month1 != month2) return month1 - month2;
    return day1 - day2;
}

// Function to validate the existence of a flight ID in the flights dataset
bool validateFlightID(const char* flightID) {
    FILE *file = fopen(FLIGHT_DATA_FILE, "r");
    if (!file) {
        printf("Unable to open flight data file.\n");
        return false;
    }

    char line[MAX_FLIGHT_LINE_LENGTH];
    char currentID[10]; // Buffer to store the flight ID read from the file

    // Read and ignore the header line if present
    fgets(line, MAX_FLIGHT_LINE_LENGTH, file);

    // Iterate through each line in the file
    while (fgets(line, MAX_FLIGHT_LINE_LENGTH, file) != NULL) {
        sscanf(line, "%9[^,]", currentID); // Extract flight ID from the line

        // Check if the current flight ID matches the target flight ID
        if (strcmp(currentID, flightID) == 0) {
            fclose(file);
            return true; // Return true if flight ID is found
        }
    }

    fclose(file);
    return false; // Return false if flight ID is not found
}
