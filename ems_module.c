#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define FILENAME "employees.txt"

struct Employee {
    char name[100];
    char position[100];
    char contact_info[100];
};

// Function prototypes
void displayMenu();
void addEmployee(struct Employee employees[], int *numEmployees);
void editEmployee(struct Employee employees[], int numEmployees);
void displayAllEmployees(const struct Employee employees[], int numEmployees);
void writeEmployeesToFile(const struct Employee employees[], int numEmployees);
void readEmployeesFromFile(struct Employee employees[], int *numEmployees);

int main() {
    struct Employee employees[MAX_EMPLOYEES];
    int numEmployees = 0;
    int choice;

    readEmployeesFromFile(employees, &numEmployees);

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &numEmployees);
                break;
            case 2:
                editEmployee(employees, numEmployees);
                break;
            case 3:
                displayAllEmployees(employees, numEmployees);
                break;
            case 4:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    writeEmployeesToFile(employees, numEmployees);

    return 0;
}

void displayMenu() {
    printf("\nEmployee Management System\n");
    printf("1. Add Employee\n");
    printf("2. Edit Employee\n");
    printf("3. Display All Employees\n");
    printf("4. Exit\n");
}

void addEmployee(struct Employee employees[], int *numEmployees) {
    if (*numEmployees < MAX_EMPLOYEES) {
        struct Employee newEmployee;

        printf("Enter employee name: ");
        scanf("%s", newEmployee.name);

        printf("Enter employee position: ");
        scanf("%s", newEmployee.position);

        printf("Enter employee contact information: ");
        scanf("%s", newEmployee.contact_info);

        employees[*numEmployees] = newEmployee;
        (*numEmployees)++;

        printf("Employee added successfully!\n");
    } else {
        printf("Maximum number of employees reached. Cannot add more employees.\n");
    }
}

void editEmployee(struct Employee employees[], int numEmployees) {
    char searchName[100];
    printf("Enter the name of the employee to edit: ");
    scanf("%s", searchName);

    int found = 0;
    for (int i = 0; i < numEmployees; i++) {
        if (strcmp(employees[i].name, searchName) == 0) {
            printf("Employee found. Editing details:\n");
            displayAllEmployees(&employees[i], 1);

            printf("Enter updated position: ");
            scanf("%s", employees[i].position);

            printf("Enter updated contact information: ");
            scanf("%s", employees[i].contact_info);

            printf("Employee details updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with name %s not found.\n", searchName);
    }
}

void displayAllEmployees(const struct Employee employees[], int numEmployees) {
    if (numEmployees > 0) {
        printf("\nEmployee List:\n");
        printf("Name\tPosition\tContact Information\n");

        for (int i = 0; i < numEmployees; i++) {
            printf("%s\t%s\t%s\n", employees[i].name, employees[i].position, employees[i].contact_info);
        }
    } else {
        printf("No employees to display.\n");
    }
}

void writeEmployeesToFile(const struct Employee employees[], int numEmployees) {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < numEmployees; i++) {
        fprintf(fp, "%s,%s,%s\n", employees[i].name, employees[i].position, employees[i].contact_info);
    }

    fclose(fp);
}

void readEmployeesFromFile(struct Employee employees[], int *numEmployees) {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("File does not exist or cannot be opened for reading. Starting with an empty employee list.\n");
        return;
    }

    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", employees[*numEmployees].name, employees[*numEmployees].position, employees[*numEmployees].contact_info) != EOF) {
        (*numEmployees)++;
        if (*numEmployees >= MAX_EMPLOYEES) {
            printf("Maximum number of employees reached while reading from file.\n");
            break;
        }
    }

    fclose(fp);
}
