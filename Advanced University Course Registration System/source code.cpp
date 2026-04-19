#include <iostream>
#include <fstream>
using namespace std;

// ------------------ Course Class ------------------
class Course {
public:
    string name;
    int creditHours;
    int seats;

    Course() {}

    Course(string n, int c, int s) {
        name = n;
        creditHours = c;
        seats = s;
    }

    void display() {
        cout << "Course: " << name
             << " | Credits: " << creditHours
             << " | Seats: " << seats << endl;
    }
};

// ------------------ Registration Class ------------------
class Registration {
private:
    Course selectedCourses[5];
    int count;

public:
    Registration() {
        count = 0;
    }

    void addCourse(Course c) {
        if (count < 5) {
            selectedCourses[count++] = c;
            cout << "Course Added!\n";
        } else {
            cout << "Max courses reached!\n";
        }
    }

    void dropCourse() {
        if (count > 0) {
            count--;
            cout << "Course Dropped!\n";
        } else {
            cout << "No courses to drop!\n";
        }
    }

    void showCourses() {
        for (int i = 0; i < count; i++) {
            selectedCourses[i].display();
        }
    }

    int totalCredits() {
        int total = 0;
        for (int i = 0; i < count; i++) {
            total += selectedCourses[i].creditHours;
        }
        return total;
    }
};

// ------------------ Student Class ------------------
class Student {
private:
    string name;
    Registration reg;

public:
    Student(string n) {
        name = n;
    }

    void registerCourse(Course c) {
        reg.addCourse(c);
    }

    void dropCourse() {
        reg.dropCourse();
    }

    void viewRegistered() {
        reg.showCourses();
        cout << "Total Credits: " << reg.totalCredits() << endl;
    }
};

// ------------------ Admin Class ------------------
class Admin {
public:
    static int totalStudents;

    void generateReport(Student s) {
        cout << "Generating Report...\n";
        s.viewRegistered();
    }
};

int Admin::totalStudents = 0;

// ------------------ Main Function ------------------
int main() {
    Course c1("OOP", 3, 30);
    Course c2("Data Structures", 4, 25);

    Student s1("Ali");

    int choice;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. View Courses\n";
        cout << "2. Register Course\n";
        cout << "3. Drop Course\n";
        cout << "4. View Registered\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            c1.display();
            c2.display();
            break;

        case 2:
            s1.registerCourse(c1);
            break;

        case 3:
            s1.dropCourse();
            break;

        case 4:
            s1.viewRegistered();
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}