#include <iostream>
#include <string>
using namespace std;

const int MAX_EMPLOYEES = 20;

int employeeIDs[MAX_EMPLOYEES];
string employeeNames[MAX_EMPLOYEES];
string employeeDepartments[MAX_EMPLOYEES];
double employeeSalaries[MAX_EMPLOYEES];
int employeeAttendance[MAX_EMPLOYEES]; // Number of days attended
int employeeLeaves[MAX_EMPLOYEES]; // Number of leave days taken
string employeeTasks[MAX_EMPLOYEES]; // Current task assignment
string employeePerformance[MAX_EMPLOYEES]; // Performance evaluations
int employeeCount = 0;

void addEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        cout << "Employee list is full!\n";
        return;
    }

    cout << "Enter ID: ";
    cin >> employeeIDs[employeeCount];
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, employeeNames[employeeCount]);
    cout << "Enter Department: ";
    getline(cin, employeeDepartments[employeeCount]);
    cout << "Enter Salary: ";
    cin >> employeeSalaries[employeeCount];
    cin.ignore();

    employeeAttendance[employeeCount] = 0;
    employeeLeaves[employeeCount] = 0;
    employeeTasks[employeeCount] = "";
    employeePerformance[employeeCount] = "";
    employeeCount++;
    cout << "Employee added successfully!\n";
}

void viewEmployees() {
    if (employeeCount == 0) {
        cout << "No employees to display!\n";
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        cout << "ID: " << employeeIDs[i] << "\n";
        cout << "Name: " << employeeNames[i] << "\n";
        cout << "Department: " << employeeDepartments[i] << "\n";
        cout << "Salary: " << employeeSalaries[i] << "\n";
        cout << "Attendance: " << employeeAttendance[i] << "\n";
        cout << "Leaves: " << employeeLeaves[i] << "\n";
        cout << "Task: " << employeeTasks[i] << "\n";
        cout << "Performance: " << employeePerformance[i] << "\n";
        cout << "-----------------------\n";
    }
}

void deleteEmployee() {
    if (employeeCount == 0) {
        cout << "No employees to delete!\n";
        return;
    }

    int id;
    cout << "Enter the ID of the employee to delete: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Employee not found!\n";
        return;
    }

    for (int i = index; i < employeeCount - 1; i++) {
        employeeIDs[i] = employeeIDs[i + 1];
        employeeNames[i] = employeeNames[i + 1];
        employeeDepartments[i] = employeeDepartments[i + 1];
        employeeSalaries[i] = employeeSalaries[i + 1];
        employeeAttendance[i] = employeeAttendance[i + 1];
        employeeLeaves[i] = employeeLeaves[i + 1];
        employeeTasks[i] = employeeTasks[i + 1];
        employeePerformance[i] = employeePerformance[i + 1];
    }

    employeeCount--;
    cout << "Employee deleted successfully!\n";
}

void updateAttendance() {
    int id, days;
    cout << "Enter the ID of the employee to update attendance: ";
    cin >> id;
    cout << "Enter the number of days attended: ";
    cin >> days;

    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            employeeAttendance[i] = days;
            cout << "Attendance updated successfully!\n";
            return;
        }
    }

    cout << "Employee not found!\n";
}

void updateLeaves() {
    int id, days;
    cout << "Enter the ID of the employee to update leaves: ";
    cin >> id;
    cout << "Enter the number of leave days taken: ";
    cin >> days;

    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            employeeLeaves[i] = days;
            cout << "Leaves updated successfully!\n";
            return;
        }
    }

    cout << "Employee not found!\n";
}

void assignTask() {
    int id;
    string task;
    cout << "Enter the ID of the employee to assign a task: ";
    cin >> id;
    cin.ignore();
    cout << "Enter the task description: ";
    getline(cin, task);

    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            employeeTasks[i] = task;
            cout << "Task assigned successfully!\n";
            return;
        }
    }

    cout << "Employee not found!\n";
}

void updatePerformance() {
    int id;
    string performance;
    cout << "Enter the ID of the employee to update performance: ";
    cin >> id;
    cin.ignore();
    cout << "Enter the performance evaluation: ";
    getline(cin, performance);

    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            employeePerformance[i] = performance;
            cout << "Performance updated successfully!\n";
            return;
        }
    }

    cout << "Employee not found!\n";
}

void searchEmployee() {
    int id;
    cout << "Enter the ID of the employee to search: ";
    cin >> id;

    for (int i = 0; i < employeeCount; i++) {
        if (employeeIDs[i] == id) {
            cout << "Employee found:\n";
            cout << "ID: " << employeeIDs[i] << "\n";
            cout << "Name: " << employeeNames[i] << "\n";
            cout << "Department: " << employeeDepartments[i] << "\n";
            cout << "Salary: " << employeeSalaries[i] << "\n";
            cout << "Attendance: " << employeeAttendance[i] << "\n";
            cout << "Leaves: " << employeeLeaves[i] << "\n";
            cout << "Task: " << employeeTasks[i] << "\n";
            cout << "Performance: " << employeePerformance[i] << "\n";
            return;
        }
    }

    cout << "Employee not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\nEmployee Management System\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Delete Employee\n";
        cout << "4. Update Attendance\n";
        cout << "5. Update Leaves\n";
        cout << "6. Assign Task\n";
        cout << "7. Update Performance\n";
        cout << "8. Search Employee\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            viewEmployees();
            break;
        case 3:
            deleteEmployee();
            break;
        case 4:
            updateAttendance();
            break;
        case 5:
            updateLeaves();
            break;
        case 6:
            assignTask();
            break;
        case 7:
            updatePerformance();
            break;
        case 8:
            searchEmployee();
            break;
        case 9:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 9);

    return 0;
}
