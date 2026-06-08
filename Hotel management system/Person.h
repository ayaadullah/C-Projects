#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

class Person
{
protected:
    string personID;
    string name;
    string email;
    string phone;
    string address;

public:
    Person();
    Person(string id, string n, string e, string p, string a);
    
    // Getters
    string getPersonID() const;
    string getName() const;
    string getEmail() const;
    string getPhone() const;
    string getAddress() const;
    
    // Setters
    void setName(string n);
    void setEmail(string e);
    void setPhone(string p);
    void setAddress(string a);
    
    // Virtual function for polymorphism
    virtual void display() const;
    virtual ~Person();
};

#endif
