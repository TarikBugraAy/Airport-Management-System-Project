# Airport Management System Project

## Overview
This project is designed to manage various aspects of an airport. It includes functionalities to manage employees, flights, and passengers.

## Features
The program provides the following features accessible through a menu-driven interface:

### Menu Options

1. **Print Employee Information**
   - Input Employee ID or '0' for all employees.
2. **Delete Employee**
   - Input Employee ID.
3. **Add Employee**
   - Follow prompts to input employee details.
4. **Update Employee**
   - Input Employee ID.
   - Follow prompts to update details.
5. **Search Employee**
   - Various search criteria options.
6. **Print Employee Counts**
   - Total number of employees.
   - Number of employees in a specific role.
7. **Print Flight Information**
   - Input Flight ID or '0' for all flights.
8. **Add Flights**
   - Follow prompts to input flight details.
9. **Delete Flight**
   - Input Flight ID.
10. **Update Flight**
   - Input Flight ID.
   - Follow prompts to update details.
11. **Search Flights**
    - Search by FlightID, Date, Destination, Type, Flights After a Date, Flights Before a Date.
12. **Count Flights**
   - Search by FlightID, Date, Destination, Type, Flights After a Date, Flights Before a Date.
13. **Add Passenger**
    - Follow prompts to input passenger details.
14. **Update Passenger**
    - Input Passenger ID.
    - Follow prompts to update details.
15. **Delete Passenger**
    - Input Passenger ID.
16. **Search Passengers**
    - Search by PassengerID, Name, PassportNumber, Nationality, DateOfBirth, FlightID.
17. **List Passengers**
    - 1. All: List all passengers.
    - 2. FlightID: Input a Flight ID to list passengers on that flight.
    - 3. Nationality: Input a nationality to list passengers of that nationality.
18. **Count Passengers**
    - Count all passengers, by FlightID, or by Nationality.
0. **Exit**
    - Exit the program.

## Compilation and Execution

To compile and run the program, you need to have GCC compiler installed on your system.

### Compile the Program

1. Open the terminal (Command Prompt or PowerShell on Windows).
2. Navigate to the project directory.
3. Run the following command to compile:
  - gcc -o airport_mgmt main.c employee.c flight.c passenger.c common.c
4. This will compile the source files and generate an executable named `airport_mgmt`.

### Run the Program

After compilation, you can run the program by executing the following in the terminal:

- On Windows: .\airport_mgmt

- On Linux/Unix: ./airport_mgmt


