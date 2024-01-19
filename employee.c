// employee.c

// Including necessary headers
#include <ctype.h>
#include "employee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

#define MAX_LINE_LENGTH 100 // Define maximum line length for file operations

// Function to print employee information based on employee ID
void printEmployeeInfo(const char *employeeID) {
    // Open the employees file in read mode
    FILE *file = fopen("employees.txt", "r");
    // Check if the file was successfully opened
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH]; // Buffer to store each line from the file
    int found = 0; // Flag to indicate if employee is found

    fgets(line, MAX_LINE_LENGTH, file); // Read the header line and ignore

    // If '0' is passed as ID, print all employee information
    if (strcmp(employeeID, "0") == 0) {
        printf("All Employees Information:\n");
        // Read each line from the file and print
        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            printf("%s", line);
        }
    } else {
        // Loop through each line to find the specified employee
        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            char currentID[5];
            // Extract the employee ID from the current line
            sscanf(line, "%4s", currentID);

            // If the current ID matches the specified ID, print the employee info
            if (strcmp(currentID, employeeID) == 0) {
                printf("Employee Information:\n%s", line);
                found = 1;
                break; // Break the loop once the employee is found
            }
        }
    }

    // Close the file
    fclose(file);

    // If the employee was not found and '0' was not passed, print an error message
    if (!found && strcmp(employeeID, "0") != 0) {
        printf("Employee with ID %s not found.\n", employeeID);
    }
}


// Function to delete an employee record based on the given employee ID
void deleteEmployee(const char *employeeID) {
    // Open the existing employee file in read mode
    FILE *file = fopen("employees.txt", "r");
    // If the file can't be opened, display an error and exit the function
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH]; // Buffer to hold each line read from the file
    int found = 0; // Flag to check if the employee is found

    // Open a temporary file in write mode to store updated data
    FILE *tempFile = fopen("temp.txt", "w");
    // If the temporary file can't be opened, display an error, close the original file and exit the function
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file); // Closing the original file before returning
        return;
    }

    // Copy the header line from the original file to the temporary file
    fgets(line, MAX_LINE_LENGTH, file);
    fprintf(tempFile, "%s", line);

    // Read each line from the original file
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char currentID[5]; // Buffer to hold the ID extracted from the line
        sscanf(line, "%4s", currentID); // Extract the ID from the line

        // Check if the current line's ID matches the given employee ID
        if (strcmp(currentID, employeeID) != 0) {
            // If it doesn't match, copy the line to the temporary file
            fprintf(tempFile, "%s", line);
        } else {
            // If a match is found, set the found flag to 1 (true)
            found = 1;
        }
    }

    // Close both the original and temporary files
    fclose(file);
    fclose(tempFile);

    // Remove the original file and rename the temporary file to the original file's name
    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    // If the employee ID was not found in the file, print a message
    if (!found) {
        printf("Employee with ID %s not found.\n", employeeID);
    }
}

// Function to add a new employee record to the file
void addEmployee() {
    // Open the employees.txt file in append mode to add new entries
    FILE *file = fopen("employees.txt", "a+");
    // If unable to open the file, display an error message and return
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE_LENGTH]; // Buffer to hold each line read from the file
    int maxID = 0; // Variable to track the highest employee ID

    // Read the first line (header) and ignore it
    fgets(line, MAX_LINE_LENGTH, file);

    // Loop through each line in the file to find the highest employee ID
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        int currentID; // Variable to store the ID found in the current line
        sscanf(line, "%d", &currentID); // Extract the ID from the line

        // Update maxID if the current ID is greater
        if (currentID > maxID) {
            maxID = currentID;
        }
    }

    // Increment maxID to get the new ID for the new employee
    int newID = maxID + 1;
    char name[50]; // Buffer to store the employee's name
    int age;       // Variable to store the employee's age
    char role[50]; // Buffer to store the employee's role

    // Prompt for and read the employee's details from the user
    printf("Enter Employee Age: ");
    scanf("%d", &age);
    // Clear the input buffer to avoid any issues with subsequent inputs
    while (getchar() != '\n'); 

    printf("Enter Employee Role: ");
    scanf("%49[^\n]%*c", role); // Read a line of text, including spaces, until a newline is encountered

    printf("Enter Employee Name (Firstname Surname): ");
    scanf("%49[^\n]%*c", name); // Same as above for the name

    // Write the new employee's data to the file
    fprintf(file, "%04d %s %d %s\n", newID, name, age, role);

    // Close the file
    fclose(file);
    // Confirm to the user that the employee has been added
    printf("Employee added successfully.\n");
}


// Function to update an existing employee's information
void updateEmployee(const char *employeeID) {
    // Open the existing employees.txt file in read mode
    FILE *file = fopen("employees.txt", "r");
    // If unable to open the file, display an error message and return
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Create a temporary file to store the updated information
    FILE *tempFile = fopen("temp.txt", "w");
    // If unable to create the temporary file, display an error message and return
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file);
        return;
    }

    char line[MAX_LINE_LENGTH]; // Buffer to hold each line read from the file
    int found = 0; // Flag to indicate if the employee ID was found

    // Read each line from the original file
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char currentID[5]; // Buffer to hold the ID extracted from the line
        sscanf(line, "%4s", currentID); // Extract the ID from the line

        // Check if the current line's ID matches the one we're updating
        if (strcmp(currentID, employeeID) == 0) {
            found = 1; // Mark that we've found the employee to update

            // Collect updated details from the user
            char name[50];
            int age;
            char role[50];

            printf("Enter updated Employee Age: ");
            scanf("%d", &age);
            while (getchar() != '\n'); // Clear input buffer
            printf("Enter updated Employee Role: ");
            scanf("%49[^\n]%*c", role);
            printf("Enter updated Employee Name (Firstname Surname): ");
            scanf("%49[^\n]%*c", name);

            // Write the updated details to the temporary file
            fprintf(tempFile, "%04d %s %d %s\n", atoi(currentID), name, age, role);
        } else {
            // If not the employee we're updating, just copy the line as is
            fprintf(tempFile, "%s", line);
        }
    }

    // Close both the original and temporary files
    fclose(file);
    fclose(tempFile);

    // Check if the employee ID was found and updated
    if (found) {
        // Replace the original file with the updated information
        remove("employees.txt");
        rename("temp.txt", "employees.txt");
        printf("Employee updated successfully.\n");
    } else {
        // If the employee wasn't found, inform the user and remove the temporary file
        printf("Employee with ID %s not found.\n", employeeID);
        remove("temp.txt");
    }
}



// Function to search for employees based on different criteria
void searchEmployee() {
    // Open the employee data file
    FILE *file = fopen("employees.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    int choice;
    printf("Search by:\n1. Name\n2. Age\n3. Role\nEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');  // Clear input buffer

    char searchTerm[50]; // Used for name and role search
    int age; // Used for age search

    // Get the search term or age from the user based on the choice
    if (choice == 2) {  // Age is an integer
        printf("Enter age to search: ");
        scanf("%d", &age);
    } else {  // Name or Role as string
        printf("Enter term to search: ");
        scanf("%49[^\n]%*c", searchTerm);
    }

    char line[MAX_LINE_LENGTH];
    int found = 0;
    fgets(line, MAX_LINE_LENGTH, file);  // Skip header

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char name[50], role[50];
        int id, empAge;
        // Parse each line to extract employee details
        sscanf(line, "%d %49[^0-9] %d %49s", &id, name, &empAge, role);

        // Search logic based on the chosen option
        if ((choice == 1 && stristr(name, searchTerm)) || 
            (choice == 2 && empAge == age) || 
            (choice == 3 && stristr(role, searchTerm))) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("No employees found matching the criteria.\n");
    }

    fclose(file);
}

// Function to print the count of employees
void printEmployeeCounts() {
    // Open the employee data file
    FILE *file = fopen("employees.txt", "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    int totalEmployees = 0, roleCount = 0, choice;
    char roleToFind[50], line[MAX_LINE_LENGTH], role[50];

    printf("Choose an option:\n1. Total number of employees\n2. Total number of employees in a specific role\nEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');  // Clear input buffer

    // Get the role to count if the user selects option 2
    if (choice == 2) {
        printf("Enter role to count: ");
        scanf("%49[^\n]%*c", roleToFind);
        for (int i = 0; roleToFind[i]; i++) {
            roleToFind[i] = tolower(roleToFind[i]);
        }
    }

    fgets(line, MAX_LINE_LENGTH, file);  // Skip header

    // Iterate through each line in the file
    while (fgets(line, MAX_LINE_LENGTH, file)) {
        if (strcmp(line, "\n") != 0) {  // Ignore empty lines
            // Parsing the line for the role
            char *lastField = strrchr(line, ' '); // Find the last space
            if (lastField != NULL) {
                strcpy(role, lastField + 1); // Copy everything after the last space
                role[strcspn(role, "\n")] = '\0'; // Remove newline character
                for (int i = 0; role[i]; i++) {
                    role[i] = tolower(role[i]);
                }
            } else {
                continue; // Skip line if parsing fails
            }

            totalEmployees++; // Counting total employees
            if (choice == 2 && strcmp(role, roleToFind) == 0) {
                roleCount++; // Counting employees in the specified role
            }
        }
    }

    fclose(file);

    // Print the total count of employees
    printf("Total number of employees: %d\n", totalEmployees);
    // Print the count of employees in the specified role, if requested
    if (choice == 2) {
        printf("Total number of employees in role '%s': %d\n", roleToFind, roleCount);
    }
}
