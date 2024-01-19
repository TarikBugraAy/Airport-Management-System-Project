// Including header files for employee, flight, and passenger functionalities
#include "employee.h"
#include "flight.h"
#include "passenger.h"
#include <stdio.h>

int main() {
    int choice; // Variable to store the user's menu choice
    char identifier[10];  // General purpose identifier 

    while(1) {  // Infinite loop to keep the program running until the user decides to exit
        // Displaying the main menu options to the user
        printf("\nChoose an option:\n");
        printf("1. Print Employee Information\n");
        printf("2. Delete Employee\n");
        printf("3. Add Employee\n");
        printf("4. Update Employee\n");
        printf("5. Search Employee\n");
        printf("6. Print Employee Counts\n");
        printf("7. Print Flight Information\n");
        printf("8. Add Flight\n");
        printf("9. Delete Flight\n");
        printf("10. Update Flight\n");
        printf("11. Search Flights\n");
        printf("12. Count Flights\n");
        printf("13. Add Passenger\n");
        printf("14. Update Passenger\n");
        printf("15. Delete Passenger\n");
        printf("16. Search Passengers\n");
        printf("17. List Passengers\n");
        printf("18. Count Passengers\n");

        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Reading the user's choice
        while (getchar() != '\n');  // Clearing the input buffer to avoid any unwanted behavior

        // Switch statement to handle different menu options based on the user's choice
        switch (choice) {
            case 1: // Option to print employee information
                printf("Enter Employee ID (or '0' for all): ");
                scanf("%9s", identifier); // Taking employee ID as input
                printEmployeeInfo(identifier); // Calling the function to print employee info
                break;
            case 2: // Option to delete an employee
                printf("Enter Employee ID: ");
                scanf("%9s", identifier);
                deleteEmployee(identifier); // Calling the function to delete employee
                break;
            case 3: // Option to add a new employee
                addEmployee(); // Calling the function to add employee
                break;
            case 4: // Option to update existing employee information
                printf("Enter Employee ID to update: ");
                scanf("%9s", identifier);
                updateEmployee(identifier); // Calling the function to update employee
                break;
            case 5: // Option to search for an employee
                searchEmployee(); // Calling the function to search employee
                break;
            case 6: // Option to print employee counts
                printEmployeeCounts(); // Calling the function to print employee counts
                break;
            case 7: // Option to print flight information
                printf("Enter Flight ID (or '0' for all): ");
                scanf("%9s", identifier);
                printFlightInfo(identifier); // Calling the function to print flight info
                break;
            case 8: // Option to add a new flight
                addFlight(); // Calling the function to add flight
                break;
                
            case 9: // Option to delete a flight
                 printf("Enter Flight ID to delete: ");
                 scanf("%9s", identifier);
                 deleteFlight(identifier); // Calling the function to delete flight
                 break;
            
            case 10: // Option to update flight information
                printf("Enter Flight ID to update: ");
                scanf("%9s", identifier);
                updateFlight(identifier); // Calling the function to update flight
                break;

            case 11: // Option to search flights
                searchFlights(); // Calling the function to search flights
                break;

            case 12: // Option to count the number of flights
                countFlights(); // Calling the function to count flights
                break;

            case 13: // Option to add a new passenger
                addPassenger(); // Calling the function to add passenger
                break;
            
            case 14: // Option to update passenger information
                updatePassenger(); // Calling the function to update passenger
                break;
            
            case 15: // Option to delete a passenger
                deletePassenger();  // Calling the function to delete passenger
                break;
            
            case 16: // Option to search for passengers
                searchPassengers(); // Calling the function to search passengers
                break;

            case 17: // Option to list all passengers
                listPassengers(); // Calling the function to list passengers
                break;

            case 18: // Option to count the number of passengers
                countPassengers(); // Calling the function to count passengers
                break;

            case 0: // Option to exit the program
                printf("Exiting the program.\n");
                return 0;  // Returning from main to exit the program
            default: // Handling invalid choices
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0; // End of main function
}
