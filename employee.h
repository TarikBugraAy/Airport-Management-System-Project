// Header file defining the Employee structure and related functions for the airport management system

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

// Definition of the Employee structure
typedef struct {
    int id;            // Unique identifier for the employee
    char name[50];     // Name of the employee
    int age;           // Age of the employee
    char role[50];     // Role or position of the employee within the organization
} Employee;

// Function declarations for employee management

// Prints information of a specific employee or all employees if ID is "0"
void printEmployeeInfo(const char *employeeID);

// Deletes the record of an employee based on the given ID
void deleteEmployee(const char *employeeID);

// Adds a new employee to the system, prompting user for details
void addEmployee();

// Updates the details of an existing employee based on the given ID
void updateEmployee(const char *employeeID);

// Searches and prints employee(s) based on various criteria entered by the user
void searchEmployee();

// Prints the total count of employees and optionally, count by specific role
void printEmployeeCounts();

#endif // EMPLOYEE_H
