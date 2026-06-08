#include "Person.h"

Person::Person()
    : personID(""), name(""), email(""), phone(""), address("")
{
}

Person::Person(string id, string n, string e, string p, string a)
    : personID(id), name(n), email(e), phone(p), address(a)
{
}

string Person::getPersonID() const { return personID; }
string Person::getName() const { return name; }
string Person::getEmail() const { return email; }
string Person::getPhone() const { return phone; }
string Person::getAddress() const { return address; }

void Person::setName(string n) { name = n; }
void Person::setEmail(string e) { email = e; }
void Person::setPhone(string p) { phone = p; }
void Person::setAddress(string a) { address = a; }

void Person::display() const
{
    cout << "===== Person Information =====" << endl;
    cout << "ID: " << personID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
    cout << "=============================" << endl;
}

Person::~Person()
{
}
