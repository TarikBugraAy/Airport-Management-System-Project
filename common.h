// Guard to prevent multiple inclusions of this header file
#ifndef COMMON_H
#define COMMON_H

// Including standard libraries
#include <stdio.h>  // For input and output functions
#include <ctype.h>  // For character handling functions
#include <stddef.h> // For defining NULL
#include <stdbool.h> // For using boolean data types and values

// Function declaration for case-insensitive substring search
// haystack: The string to be searched
// needle: The substring to search for within haystack
char* stristr(const char *haystack, const char *needle);

// Function declaration to parse a date string in YYYY-MM-DD format into separate year, month, and day components
// dateStr: Input string containing the date
// year: Pointer to store the extracted year
// month: Pointer to store the extracted month
// day: Pointer to store the extracted day
void parseDate(const char *dateStr, int *year, int *month, int *day);

// Function declaration to compare two date strings in YYYY-MM-DD format
// date1: First date string
// date2: Second date string
// Returns: Negative value if date1 < date2, zero if date1 = date2, positive value if date1 > date2
int compareDates(const char *date1, const char *date2);

// Function declaration to validate a flight ID
// flightID: The flight ID to validate
// Returns: true if the flight ID is valid, false otherwise
bool validateFlightID(const char* flightID);

#endif // COMMON_H
