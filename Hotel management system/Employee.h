#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
#include <ctime>

using namespace std;

class Employee : public Person
{
protected:
    string employeeID;
    string department;
    double salary;
    string joinDate;
    bool isActive;

public:
    Employee();
    Employee(string id, string n, string e, string p, string a,
             string empID, string dept, double sal, string jDate);
    
    string getEmployeeID() const;
    string getDepartment() const;
    double getSalary() const;
    string getJoinDate() const;
    bool getIsActive() const;
    
    void setSalary(double sal);
    void setDepartment(string dept);
    void setActive(bool active);
    
    virtual double calculateBonus() const;
    virtual void display() const override;
    virtual ~Employee();
};

// Receptionist class - specialization of Employee
class Receptionist : public Employee
{
private:
    int checkinsProcessed;
    int checkoutsProcessed;

public:
    Receptionist();
    Receptionist(string id, string n, string e, string p, string a,
                 string empID, double sal, string jDate);
    
    int getCheckinsProcessed() const;
    int getCheckoutsProcessed() const;
    
    void incrementCheckIn();
    void incrementCheckOut();
    double calculateBonus() const override;
    void display() const override;
};

// Manager class - specialization of Employee
class Manager : public Employee
{
private:
    string managerType; // Front Desk Manager, Food & Beverage Manager, etc.
    int staffManaged;

public:
    Manager();
    Manager(string id, string n, string e, string p, string a,
            string empID, double sal, string jDate, string mType);
    
    string getManagerType() const;
    int getStaffManaged() const;
    void setStaffManaged(int count);
    double calculateBonus() const override;
    void display() const override;
};

// HouseKeeping class - specialization of Employee
class HouseKeeping : public Employee
{
private:
    int roomsCleaned;
    string shiftType; // Morning, Afternoon, Night

public:
    HouseKeeping();
    HouseKeeping(string id, string n, string e, string p, string a,
                 string empID, double sal, string jDate, string shift);
    
    int getRoomsCleaned() const;
    string getShiftType() const;
    
    void incrementRoomsCleaned();
    double calculateBonus() const override;
    void display() const override;
};

#endif
