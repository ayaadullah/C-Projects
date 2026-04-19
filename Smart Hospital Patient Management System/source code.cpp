#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ===================== PATIENT CLASS =====================
class Patient {
private:
    string name;
    int age;
    string disease;
    string status;

public:
    Patient() {
        name = "";
        age = 0;
        disease = "";
        status = "Admitted";
    }

    Patient(string n, int a, string d) {
        name = n;
        age = a;
        disease = d;
        status = "Admitted";
    }

    void updateDisease(string d) {
        disease = d;
    }

    void discharge() {
        status = "Discharged";
    }

    string getName() { return name; }
    string getStatus() { return status; }

    void display() {
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nDisease: " << disease;
        cout << "\nStatus: " << status << endl;
    }

    void saveToFile() {
        ofstream file("patients.txt", ios::app);
        file << name << "," << age << "," << disease << "," << status << endl;
        file.close();
    }
};

// ===================== RECORD CLASS (COMPOSITION) =====================
class Record {
private:
    vector<Patient> patients;

public:
    void addPatient(Patient p) {
        patients.push_back(p);
        p.saveToFile();
    }

    void showAll() {
        for (auto &p : patients) {
            p.display();
        }
    }
};

// ===================== DOCTOR CLASS =====================
class Doctor {
public:
    void diagnose(Patient &p, string newDisease) {
        p.updateDisease(newDisease);
    }
};

// ===================== ADMIN CLASS =====================
class Admin {
public:
    static int totalPatients;
    static int activePatients;

    void updateStats() {
        totalPatients++;
        activePatients++;
    }

    void dischargePatient() {
        activePatients--;
    }

    void showStats() {
        cout << "\nTotal Patients: " << totalPatients;
        cout << "\nActive Patients: " << activePatients << endl;
    }
};

int Admin::totalPatients = 0;
int Admin::activePatients = 0;

// ===================== MAIN SYSTEM =====================
int main() {
    Record record;
    Doctor doctor;
    Admin admin;

    vector<Patient> patientList;

    int choice;

    do {
        cout << "\n===== SMART HOSPITAL SYSTEM =====";
        cout << "\n1. Add Patient";
        cout << "\n2. View Patients";
        cout << "\n3. Update Disease";
        cout << "\n4. Discharge Patient";
        cout << "\n5. View Stats";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name, disease;
            int age;

            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Age: ";
            cin >> age;
            cout << "Enter Disease: ";
            cin >> disease;

            Patient p(name, age, disease);
            patientList.push_back(p);
            record.addPatient(p);
            admin.updateStats();

        } 
        else if (choice == 2) {
            for (auto &p : patientList)
                p.display();
        } 
        else if (choice == 3) {
            int index;
            string disease;

            cout << "Enter patient index: ";
            cin >> index;

            cout << "Enter new disease: ";
            cin >> disease;

            if (index < patientList.size())
                doctor.diagnose(patientList[index], disease);

        } 
        else if (choice == 4) {
            int index;
            cout << "Enter patient index: ";
            cin >> index;

            if (index < patientList.size()) {
                patientList[index].discharge();
                admin.dischargePatient();
            }

        } 
        else if (choice == 5) {
            admin.showStats();
        }

    } while (choice != 0);

    return 0;
}