#include "Employee.h"

// ========== Employee Base Class Implementation ==========
Employee::Employee()
    : Person(), employeeID(""), department(""), salary(0.0), joinDate(""), isActive(true)
{
}

Employee::Employee(string id, string n, string e, string p, string a,
                   string empID, string dept, double sal, string jDate)
    : Person(id, n, e, p, a), employeeID(empID), department(dept),
      salary(sal), joinDate(jDate), isActive(true)
{
}

string Employee::getEmployeeID() const { return employeeID; }
string Employee::getDepartment() const { return department; }
double Employee::getSalary() const { return salary; }
string Employee::getJoinDate() const { return joinDate; }
bool Employee::getIsActive() const { return isActive; }

void Employee::setSalary(double sal) { salary = sal; }
void Employee::setDepartment(string dept) { department = dept; }
void Employee::setActive(bool active) { isActive = active; }

double Employee::calculateBonus() const
{
    return salary * 0.05; // 5% bonus
}

void Employee::display() const
{
    cout << "\n===== Employee Information =====" << endl;
    cout << "Person ID: " << personID << endl;
    cout << "Employee ID: " << employeeID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Department: " << department << endl;
    cout << "Salary: Rs. " << salary << endl;
    cout << "Join Date: " << joinDate << endl;
    cout << "Bonus: Rs. " << calculateBonus() << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    cout << "================================" << endl;
}

Employee::~Employee()
{
}

// ========== Receptionist Implementation ==========
Receptionist::Receptionist()
    : Employee(), checkinsProcessed(0), checkoutsProcessed(0)
{
}

Receptionist::Receptionist(string id, string n, string e, string p, string a,
                           string empID, double sal, string jDate)
    : Employee(id, n, e, p, a, empID, "Front Desk", sal, jDate),
      checkinsProcessed(0), checkoutsProcessed(0)
{
}

int Receptionist::getCheckinsProcessed() const { return checkinsProcessed; }
int Receptionist::getCheckoutsProcessed() const { return checkoutsProcessed; }

void Receptionist::incrementCheckIn() { checkinsProcessed++; }
void Receptionist::incrementCheckOut() { checkoutsProcessed++; }

double Receptionist::calculateBonus() const
{
    double baseBonus = salary * 0.05;
    int totalOperations = checkinsProcessed + checkoutsProcessed;
    double operationBonus = totalOperations * 10.0; // Rs. 10 per operation
    return baseBonus + operationBonus;
}

void Receptionist::display() const
{
    cout << "\n===== Receptionist Information =====" << endl;
    cout << "Person ID: " << personID << endl;
    cout << "Employee ID: " << employeeID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Department: " << department << endl;
    cout << "Salary: Rs. " << salary << endl;
    cout << "Check-ins Processed: " << checkinsProcessed << endl;
    cout << "Check-outs Processed: " << checkoutsProcessed << endl;
    cout << "Bonus: Rs. " << calculateBonus() << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    cout << "====================================" << endl;
}

// ========== Manager Implementation ==========
Manager::Manager()
    : Employee(), managerType(""), staffManaged(0)
{
}

Manager::Manager(string id, string n, string e, string p, string a,
                 string empID, double sal, string jDate, string mType)
    : Employee(id, n, e, p, a, empID, "Management", sal, jDate),
      managerType(mType), staffManaged(0)
{
}

string Manager::getManagerType() const { return managerType; }
int Manager::getStaffManaged() const { return staffManaged; }
void Manager::setStaffManaged(int count) { staffManaged = count; }

double Manager::calculateBonus() const
{
    double baseBonus = salary * 0.10; // 10% base bonus
    double teamBonus = staffManaged * 500.0; // Rs. 500 per staff member
    return baseBonus + teamBonus;
}

void Manager::display() const
{
    cout << "\n===== Manager Information =====" << endl;
    cout << "Person ID: " << personID << endl;
    cout << "Employee ID: " << employeeID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Manager Type: " << managerType << endl;
    cout << "Salary: Rs. " << salary << endl;
    cout << "Staff Managed: " << staffManaged << endl;
    cout << "Bonus: Rs. " << calculateBonus() << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    cout << "===============================" << endl;
}

// ========== HouseKeeping Implementation ==========
HouseKeeping::HouseKeeping()
    : Employee(), roomsCleaned(0), shiftType("")
{
}

HouseKeeping::HouseKeeping(string id, string n, string e, string p, string a,
                           string empID, double sal, string jDate, string shift)
    : Employee(id, n, e, p, a, empID, "Housekeeping", sal, jDate),
      roomsCleaned(0), shiftType(shift)
{
}

int HouseKeeping::getRoomsCleaned() const { return roomsCleaned; }
string HouseKeeping::getShiftType() const { return shiftType; }

void HouseKeeping::incrementRoomsCleaned() { roomsCleaned++; }

double HouseKeeping::calculateBonus() const
{
    double baseBonus = salary * 0.05;
    double cleaningBonus = roomsCleaned * 50.0; // Rs. 50 per room cleaned
    return baseBonus + cleaningBonus;
}

void HouseKeeping::display() const
{
    cout << "\n===== HouseKeeping Staff Information =====" << endl;
    cout << "Person ID: " << personID << endl;
    cout << "Employee ID: " << employeeID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Shift: " << shiftType << endl;
    cout << "Salary: Rs. " << salary << endl;
    cout << "Rooms Cleaned: " << roomsCleaned << endl;
    cout << "Bonus: Rs. " << calculateBonus() << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    cout << "==========================================" << endl;
}
