# 🎓 OOP Concepts - Complete Documentation

## Overview
This document explains all OOP concepts implemented in the Smart Hotel Management System with real code examples from the project.

---

## 1️⃣ ENCAPSULATION

**Definition**: Bundling data members and methods together, hiding internal details.

### Implementation in Person.h
```cpp
class Person
{
private:
    string personID;      // Private - hidden from outside
    string name;
    string email;
    string phone;
    string address;

public:
    // Controlled access through public methods
    string getPersonID() const;
    void setEmail(string e);
    string getEmail() const;
};
```

### Benefits
- ✓ Data protection
- ✓ Controlled access
- ✓ Easy to modify implementation
- ✓ Prevents unauthorized access

### Real Example
```cpp
Guest guest("G001", "Ahmed Khan", "ahmed@email.com", "03001234567", "Islamabad", "Pakistan", "PK123456");

// Can only access through public methods
cout << guest.getName();           // ✓ Allowed
guest.setEmail("newemail@gmail.com"); // ✓ Allowed
// guest.personID = "G002";         // ✗ Compilation Error!
```

---

## 2️⃣ INHERITANCE

**Definition**: Creating new classes based on existing ones, inheriting properties and methods.

### Single Inheritance Example

```cpp
// Base Class
class Person
{
protected:
    string personID;
    string name;
    string email;
    // ... more members
public:
    virtual void display() const;
    virtual ~Person();
};

// Derived Class
class Guest : public Person  // Guest inherits from Person
{
private:
    string nationality;
    int loyaltyPoints;
    vector<string> bookingHistory;
public:
    void addLoyaltyPoints(int points);
    double getLoyaltyDiscount() const;
    void display() const override;  // Overrides base class method
};
```

### Inheritance Hierarchy

```
Person (Base Class)
├── Guest (Derived)
│   ├── Methods from Person (inherited)
│   ├── Additional methods
│   └── Overridden methods
│
└── Employee (Derived)
    ├── Methods from Person (inherited)
    ├── Additional properties
    │
    ├── Receptionist (Derived from Employee)
    │   ├── Inherits Person & Employee
    │   └── Specific methods
    │
    ├── Manager (Derived from Employee)
    │   ├── Inherits Person & Employee
    │   └── Specific methods
    │
    └── HouseKeeping (Derived from Employee)
        ├── Inherits Person & Employee
        └── Specific methods
```

### Benefits
- ✓ Code reusability
- ✓ Logical hierarchy
- ✓ Easier maintenance
- ✓ DRY principle (Don't Repeat Yourself)

### Room Inheritance Hierarchy

```cpp
class Room {
protected:
    string roomID;
    double basePrice;
    // ... common room properties
    virtual double calculatePrice() const;
};

class StandardRoom : public Room {
public:
    double calculatePrice() const override;
};

class DeluxeRoom : public Room {
public:
    double calculatePrice() const override;
};

class ExecutiveRoom : public Room {
public:
    double calculatePrice() const override;
};

class SuiteRoom : public Room {
public:
    double calculatePrice() const override;
};
```

---

## 3️⃣ POLYMORPHISM

**Definition**: Objects of different classes can be used through the same interface.

### Method Overriding (Runtime Polymorphism)

```cpp
// Base class with virtual method
class Service
{
public:
    virtual double calculateBill() = 0;  // Pure virtual
    virtual void display() const = 0;
};

// Different implementations
class RestaurantService : public Service
{
public:
    double calculateBill() override {
        double subtotal = dishPrice * quantity;
        double serviceCharge = subtotal * 0.10;
        double gst = (subtotal + serviceCharge) * 0.17;
        return subtotal + serviceCharge + gst;
    }
};

class LaundryService : public Service
{
public:
    double calculateBill() override {
        double subtotal = numberOfItems * pricePerItem;
        double extraCharge = 0.0;
        if (laundryType == "Dry Cleaning")
            extraCharge = subtotal * 0.25;
        return subtotal + extraCharge;
    }
};

class SpaService : public Service
{
public:
    double calculateBill() override {
        double treatmentCost = durationMinutes * pricePerMinute;
        double serviceCharge = treatmentCost * 0.15;
        return treatmentCost + serviceCharge;
    }
};
```

### Polymorphic Usage

```cpp
// Vector of base class pointers
vector<Service*> services;

// Can store derived class objects
services.push_back(new RestaurantService(...));
services.push_back(new LaundryService(...));
services.push_back(new SpaService(...));

// Each calls its own implementation!
for (auto service : services) {
    double bill = service->calculateBill();  // Polymorphic call
    service->display();                      // Polymorphic call
}
```

### Room Polymorphism Example

```cpp
vector<Room*> rooms;
rooms.push_back(new StandardRoom("STD1", 1));
rooms.push_back(new DeluxeRoom("DLX1", 2));
rooms.push_back(new ExecutiveRoom("EXE1", 3));
rooms.push_back(new SuiteRoom("SUI1", 4));

// Each room calculates its price differently
for (auto room : rooms) {
    cout << "Price: " << room->calculatePrice() << endl;  // Polymorphic
    cout << "Service Charge: " << room->getServiceCharge() << endl;
}
```

### Benefits
- ✓ Flexible code
- ✓ Easy to extend
- ✓ Cleaner implementations
- ✓ Easier testing

---

## 4️⃣ ABSTRACTION

**Definition**: Hiding complex implementation details and showing only essential features.

### Abstract Service Class

```cpp
// Abstract base class - cannot be instantiated
class Service
{
protected:
    string serviceID;
    string guestID;
    double baseCost;
    string serviceDate;
    string status;

public:
    Service();
    
    // Pure virtual method - MUST be implemented by derived classes
    virtual double calculateBill() = 0;
    virtual void display() const = 0;
    virtual ~Service();
};
```

### Why Abstraction?

```cpp
// ✗ Cannot do this - abstract class!
// Service service("S001", "G001", 1000, "2024-06-08");

// ✓ Must use concrete implementations
RestaurantService restaurant("S001", "G001", "Biryani", 2, 500, "Lunch", "2024-06-08");
double bill = restaurant.calculateBill();  // Valid!
```

### Benefits
- ✓ Enforces contract
- ✓ Prevents misuse
- ✓ Clear interface definition
- ✓ Compile-time safety

---

## 5️⃣ COMPOSITION

**Definition**: Objects containing other objects (Has-A relationship).

### Hotel Composition Pattern

```cpp
class Hotel
{
private:
    // Hotel CONTAINS (Has-A) multiple objects
    vector<Room*> rooms;              // Hotel has Rooms
    vector<Guest> guests;              // Hotel has Guests
    vector<Employee*> employees;       // Hotel has Employees
    vector<Booking> bookings;          // Hotel has Bookings
    vector<Bill> bills;                // Hotel has Bills
    vector<Service*> services;         // Hotel has Services

public:
    // Methods to manage composed objects
    void addRoom(Room* room);
    void addGuest(Guest guest);
    void hireEmployee(Employee* employee);
    void createBooking(Booking booking);
    void generateBill(Bill bill);
    void addService(Service* service);
};
```

### Composition vs Inheritance

```cpp
// Composition: Hotel "has-a" Room
class Hotel {
    vector<Room*> rooms;  // Contains rooms
};

// Inheritance: Receptionist "is-a" Employee
class Receptionist : public Employee {
    // Inherits all Employee properties
};
```

### Benefits
- ✓ Flexible relationships
- ✓ Easier to modify
- ✓ No tight coupling
- ✓ Better encapsulation

---

## 6️⃣ FRIEND FUNCTIONS

**Definition**: Functions that can access private/protected members of a class.

### Bill and Guest Friendship

```cpp
class Guest : public Person
{
private:
    int loyaltyPoints;
    double totalSpent;

public:
    // Friend function declaration
    friend double calculateGuestDiscount(const Guest& guest, double billAmount);
};

// Friend function implementation (defined outside class)
double calculateGuestDiscount(const Guest& guest, double billAmount)
{
    // Can access private members of Guest!
    double discount = billAmount * (guest.loyaltyPoints * 0.001);
    return (discount > billAmount * 0.1) ? billAmount * 0.1 : discount;
}
```

### Bill's Friend Functions

```cpp
class Bill
{
private:
    double roomCharges;
    double totalAmount;

public:
    // Friend function access declaration
    friend void printBillDetails(const Bill& bill);
    friend double calculateGuestDiscount(const Bill& bill, double loyaltyPoints);
};

// Can access private Bill members
void printBillDetails(const Bill& bill)
{
    cout << "Room Charges: " << bill.roomCharges << endl;
    cout << "Total: " << bill.totalAmount << endl;
}
```

### When to Use Friend Functions
- ✓ Binary operators that need access to both operands
- ✓ Logging/debugging functions
- ✓ Strategic access to private data
- ⚠️ Use sparingly to maintain encapsulation

---

## 7️⃣ OPERATOR OVERLOADING

**Definition**: Defining custom behavior for operators like +, -, ==, etc.

### Bill Operator Overloading

```cpp
class Bill
{
public:
    // Equality operator
    bool operator==(const Bill& other) const {
        return billID == other.billID;
    }

    // Comparison operators
    bool operator>(const Bill& other) const {
        return totalAmount > other.totalAmount;
    }

    bool operator<(const Bill& other) const {
        return totalAmount < other.totalAmount;
    }

    // Arithmetic operators (return new object)
    Bill operator+(double amount) const {
        Bill temp = *this;
        temp.otherCharges += amount;
        temp.calculateTotal();
        return temp;
    }

    Bill operator-(double amount) const {
        Bill temp = *this;
        temp.discountPercentage += (amount / calculateSubtotal()) * 100;
        temp.calculateTotal();
        return temp;
    }

    // Compound assignment operators (modify object)
    Bill& operator+=(double amount) {
        otherCharges += amount;
        calculateTotal();
        return *this;
    }

    Bill& operator-=(double amount) {
        discountPercentage += (amount / calculateSubtotal()) * 100;
        calculateTotal();
        return *this;
    }
};
```

### Using Operator Overloading

```cpp
Bill bill1("BILL001", "G001", "BK001");
bill1.setRoomCharges(6000);

Bill bill2 = bill1 + 500;      // Add charges using +
Bill bill3 = bill1 - 1000;     // Apply discount using -

bill1 += 500;                  // Compound assignment
bill1 -= 1000;

// Compare bills
if (bill1 > bill2) {
    cout << "Bill1 is more expensive";
}

if (bill1 == bill2) {
    cout << "Same bill ID";
}
```

### Booking Operators

```cpp
class Booking
{
public:
    // Equality check
    bool operator==(const Booking& other) const {
        return bookingID == other.bookingID;
    }

    // Sorting by date
    bool operator<(const Booking& other) const {
        return bookingDate < other.bookingDate;
    }
};

// Usage
vector<Booking> bookings;
// ... add bookings
sort(bookings.begin(), bookings.end());  // Uses operator<
```

### Benefits
- ✓ More intuitive syntax
- ✓ Natural expression
- ✓ Code readability
- ✓ Mathematical operations

---

## 8️⃣ VIRTUAL FUNCTIONS & DESTRUCTORS

**Definition**: Functions that can be overridden by derived classes. Virtual destructors prevent memory leaks.

### Virtual Methods

```cpp
class Employee : public Person
{
public:
    // Virtual method - can be overridden
    virtual double calculateBonus() const {
        return salary * 0.05;  // 5% base bonus
    }

    virtual void display() const override;
    virtual ~Employee();  // Virtual destructor
};

class Receptionist : public Employee
{
public:
    // Override with specific implementation
    double calculateBonus() const override {
        double baseBonus = salary * 0.05;
        int totalOperations = checkinsProcessed + checkoutsProcessed;
        double operationBonus = totalOperations * 10.0;
        return baseBonus + operationBonus;
    }

    void display() const override;
};
```

### Virtual Destructors Importance

```cpp
// Without virtual destructor - MEMORY LEAK!
class Base {
public:
    ~Base() { cout << "Base destructor\n"; }
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() { data = new int[100]; }
    ~Derived() { delete[] data; }  // Not called!
};

Base* ptr = new Derived();
delete ptr;  // Only calls Base destructor!

// With virtual destructor - CORRECT!
class Base {
public:
    virtual ~Base() { cout << "Base destructor\n"; }
};

Base* ptr = new Derived();
delete ptr;  // Calls both destructors in correct order
```

### Why Virtual Destructors?

```cpp
void cleanupServices(vector<Service*> services) {
    for (auto service : services) {
        delete service;  // Calls correct destructor due to virtuality
    }
}
```

---

## 9️⃣ CONST CORRECTNESS

**Definition**: Using const to prevent unintended modifications.

### Implementation in Project

```cpp
class Guest : public Person
{
public:
    // Const methods - promise not to modify object
    string getName() const { return name; }
    int getLoyaltyPoints() const { return loyaltyPoints; }
    vector<string> getBookingHistory() const { return bookingHistory; }

    // Non-const methods - can modify
    void addLoyaltyPoints(int points) { loyaltyPoints += points; }
    void addBooking(string bookingID) { bookingHistory.push_back(bookingID); }

    // Const parameters - cannot modify passed object
    bool operator==(const Guest& other) const {
        return personID == other.personID;
    }
};
```

### Benefits
- ✓ Compiler enforcement
- ✓ Clear intent
- ✓ Prevents bugs
- ✓ Better optimization

---

## 🔟 MEMORY MANAGEMENT

**Definition**: Proper allocation and deallocation of memory.

### Proper Memory Management

```cpp
class Hotel
{
private:
    vector<Room*> rooms;
    vector<Employee*> employees;
    vector<Service*> services;

public:
    // Allocation
    void addRoom(Room* room) {
        rooms.push_back(room);
    }

    void hireEmployee(Employee* employee) {
        employees.push_back(employee);
    }

    // Deallocation in destructor
    ~Hotel() {
        for (auto room : rooms) {
            delete room;  // Free dynamically allocated memory
        }
        for (auto emp : employees) {
            delete emp;
        }
        for (auto service : services) {
            delete service;
        }
    }
};
```

### Usage

```cpp
Hotel hotel("Northern Heights Hotel", "123 Main St", "051-1234567", 20, 5);

// Allocate
hotel.addRoom(new StandardRoom("STD1", 1));
hotel.hireEmployee(new Manager("P001", "Ahmed", ...));
hotel.addService(new RestaurantService("S001", "G001", ...));

// When hotel object is destroyed:
// ~Hotel() is called
// All pointers are deleted
// No memory leaks!
```

---

## Summary Table

| Concept | Purpose | Location |
|---------|---------|----------|
| **Encapsulation** | Data hiding & control | All classes - private/public |
| **Inheritance** | Code reuse & hierarchy | Person→Guest/Employee |
| **Polymorphism** | Runtime flexibility | Service, Room classes |
| **Abstraction** | Hide complexity | Service base class |
| **Composition** | Object containment | Hotel class |
| **Friend Functions** | Controlled access | calculateGuestDiscount |
| **Operator Overloading** | Natural syntax | Bill, Booking classes |
| **Virtual Functions** | Dynamic binding | Service, Room, Person |
| **Const Correctness** | Intent clarity | All getter methods |
| **Memory Management** | Resource safety | Hotel destructor |

---

## 📝 Conclusion

This project demonstrates all major C++ OOP concepts working together in harmony:

1. **Base Classes** define common interface (Person, Service, Room)
2. **Derived Classes** specialize behavior (Guest, Employee, RestaurantService)
3. **Composition** combines objects (Hotel contains Rooms, Guests, etc.)
4. **Polymorphism** enables flexible designs
5. **Encapsulation** protects data
6. **Operator Overloading** makes code intuitive
7. **Memory Management** prevents leaks

Perfect for learning and teaching OOP principles! ✨

