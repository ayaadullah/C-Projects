# 🏨 Smart Hotel Management System (C++)

A comprehensive, production-grade hotel management system built with modern C++ OOP principles. This project is suitable for university-level OOP final exams and semester projects.

## 📋 Project Overview

**Northern Heights Hotel & Resort** - A complete hotel management solution featuring guest management, room bookings, employee payroll, billing, and advanced services.

### 🎯 Key Features

- ✅ **Guest Management** - Registration, loyalty points, booking history
- ✅ **Room Management** - 4 room types with polymorphism
- ✅ **Booking System** - Reservations with check-in/check-out
- ✅ **Employee Management** - Multiple employee types with bonuses
- ✅ **Bill Generation** - Dynamic billing with discounts & taxes
- ✅ **Services** - Restaurant, Laundry, Spa, Room Service
- ✅ **Loyalty Program** - Points system with redemption
- ✅ **File Handling** - Data persistence (guests, bookings, bills, employees)
- ✅ **Reports** - Occupancy, revenue, and guest reports
- ✅ **Interactive Menu** - User-friendly command-line interface

---

## 🏗️ OOP Concepts Implemented

### ✓ Encapsulation
- Private data members with public getter/setter methods
- All classes protect sensitive data

### ✓ Inheritance
**Single Inheritance:**
```cpp
Person (Base)
├── Guest
└── Employee
    ├── Receptionist
    ├── Manager
    └── HouseKeeping

Room (Base)
├── StandardRoom
├── DeluxeRoom
├── ExecutiveRoom
└── SuiteRoom

Service (Abstract Base)
├── RestaurantService
├── LaundryService
├── SpaService
└── RoomService
```

### ✓ Polymorphism (Method Overriding)
- Virtual functions: `display()`, `calculatePrice()`, `calculateBill()`
- Virtual destructors for proper memory cleanup

### ✓ Abstraction
- Abstract Service class with pure virtual methods
- Interface-based design for services

### ✓ Composition (Has-A Relationship)
```cpp
Hotel Has-A:
  - Multiple Rooms
  - Multiple Guests
  - Multiple Employees
  - Multiple Bookings
  - Multiple Bills
  - Multiple Services
```

### ✓ Operator Overloading
- `==` - Equality comparison
- `<`, `>` - Less than, greater than
- `+`, `-` - Add/subtract charges
- `+=`, `-=` - Compound assignment

### ✓ Friend Functions
- `calculateGuestDiscount()` - Access guest loyalty details
- `printBillDetails()` - Access confidential bill information

### ✓ File Handling
- Save/Load guest data
- Save/Load booking data
- Save/Load bill data
- Save/Load employee data
- Save/Load room data

---

## 📁 Project Structure

```
hotel_management_system/
├── Person.h / Person.cpp          # Base person class
├── Guest.h / Guest.cpp            # Guest with loyalty program
├── Employee.h / Employee.cpp      # Employee types (Receptionist, Manager, HouseKeeping)
├── Room.h / Room.cpp              # Room types (Standard, Deluxe, Executive, Suite)
├── Service.h / Service.cpp        # Services (Restaurant, Laundry, Spa, Room)
├── Booking.h / Booking.cpp        # Booking management
├── Bill.h / Bill.cpp              # Bill generation with operator overloading
├── Hotel.h / Hotel.cpp            # Main hotel class (Composition pattern)
├── main.cpp                       # Application driver & interactive menu
├── Makefile                       # Build configuration
├── README.md                      # This file
├── guests.txt                     # Guest data file
├── bookings.txt                   # Booking data file
├── bills.txt                      # Bill data file
├── employees.txt                  # Employee data file
└── rooms.txt                      # Room data file
```

---

## 🚀 How to Compile and Run

### Prerequisites
- GCC compiler (g++) with C++11 support
- Linux/Mac/Windows (with WSL or MinGW)

### Method 1: Using Makefile (Recommended)
```bash
# Navigate to project directory
cd hotel_management_system

# Compile the project
make

# Run the application
make run

# Clean build files
make clean
```

### Method 2: Manual Compilation
```bash
g++ -std=c++11 -o hotel_system main.cpp Person.cpp Guest.cpp Employee.cpp \
    Room.cpp Service.cpp Booking.cpp Bill.cpp Hotel.cpp

# Run
./hotel_system
```

### Method 3: Step-by-step Compilation
```bash
g++ -std=c++11 -c Person.cpp
g++ -std=c++11 -c Guest.cpp
g++ -std=c++11 -c Employee.cpp
g++ -std=c++11 -c Room.cpp
g++ -std=c++11 -c Service.cpp
g++ -std=c++11 -c Booking.cpp
g++ -std=c++11 -c Bill.cpp
g++ -std=c++11 -c Hotel.cpp
g++ -std=c++11 -c main.cpp

g++ -o hotel_system *.o
./hotel_system
```

---

## 📖 Usage Guide

### Main Menu Options

1. **Guest Management**
   - Register new guests
   - View all guests
   - Search for specific guest
   - Automatic loyalty point tracking

2. **Room Management**
   - View all rooms with details
   - Check available rooms
   - Filter by room type
   - View occupancy status

3. **Booking Management**
   - Create new reservations
   - View all bookings
   - Check-in guests
   - Check-out guests
   - Cancel bookings

4. **Employee Management**
   - Hire new employees (3 types)
   - View employee details
   - Calculate payroll with bonuses
   - Track employee performance

5. **Bill Management**
   - Generate bills for guests
   - View billing history
   - Apply discounts
   - Generate revenue reports

6. **Service Management**
   - Add restaurant orders
   - Process laundry requests
   - Book spa services
   - Track room service requests

7. **Run Demo**
   - Automatic demonstration with sample data
   - Shows all features in action

8. **Exit**
   - Save all data before exiting

---

## 💰 Room Types & Pricing

| Room Type | Price/Night | Capacity | Amenities |
|-----------|------------|----------|-----------|
| **Standard** | Rs. 3,000 | 1 | TV, WiFi |
| **Deluxe** | Rs. 5,000 | 2 | AC, Balcony, Jacuzzi |
| **Executive** | Rs. 7,500 | 2 | Kitchen, Work Area, Locker |
| **Suite** | Rs. 15,000 | 4 | Luxury, Private Spa, Dining |

---

## 💼 Employee Types

### 1. Receptionist
- Manages check-ins/check-outs
- Bonus: Base 5% + Rs. 10 per operation

### 2. Manager
- Oversees staff and operations
- Bonus: Base 10% + Rs. 500 per staff member

### 3. Housekeeping
- Room cleaning and maintenance
- Bonus: Base 5% + Rs. 50 per room cleaned

---

## 🎁 Loyalty Program

**Point System:**
- Guests earn loyalty points with every booking
- 1 loyalty point = 0.1% discount (max 10%)
- Points can be redeemed for future discounts
- Special offers for frequent guests

**Example:**
- Guest spends Rs. 50,000 over multiple stays
- Accumulates 500 loyalty points
- Gets 5% automatic discount on next booking

---

## 📊 Services Available

### 1. Restaurant Service
- Multiple meal types (Breakfast, Lunch, Dinner)
- 10% service charge + 17% GST
- Dynamic menu pricing

### 2. Laundry Service
- Regular, Dry Cleaning, Express options
- Extra charges: DC (25%), Express (15%)
- Bulk processing available

### 3. Spa Service
- Massage, Facial, Full Body Spa
- Charged per minute
- 15% service charge included

### 4. Room Service
- In-room dining and supplies
- 10% service charge + Rs. 50 delivery fee
- 17% GST applied

---

## 📈 Reporting Features

### 1. Occupancy Report
- Total rooms vs occupied
- Occupancy percentage
- Breakdown by room type

### 2. Revenue Report
- Total bills generated
- Paid vs pending bills
- Net revenue calculation

### 3. Guest Report
- Total registered guests
- Employee count
- Booking statistics

### 4. Dashboard
- Real-time statistics
- Quick overview of operations
- Performance metrics

---

## 💻 Sample Code Usage

### Creating a Guest
```cpp
Guest guest("G001", "Ahmed Khan", "ahmed@email.com", 
            "03001234567", "Islamabad", "Pakistan", "PK123456");
guest.addLoyaltyPoints(500);
hotel.addGuest(guest);
```

### Creating a Booking
```cpp
Booking booking("BK001", "G001", "STD1", "2024-06-08", "2024-06-10", 3000);
hotel.createBooking(booking);
hotel.checkInGuest("BK001");
```

### Generating a Bill
```cpp
Bill bill("BILL001", "G001", "BK001");
bill.setRoomCharges(6000);
bill.setRestaurantCharges(1000);
bill.setDiscountPercentage(10);
bill.setPaymentMethod("Credit Card");
hotel.generateBill(bill);
bill.display();
```

### Adding Services
```cpp
RestaurantService* service = new RestaurantService(
    "S001", "G001", "Biryani", 2, 500, "Lunch", "2024-06-08"
);
hotel.addService(service);
double billAmount = service->calculateBill(); // Polymorphic call
```

---

## 🔐 Data Persistence

All data is automatically saved to text files:

**guests.txt**
```
G001|Ahmed Khan|ahmed@email.com|03001234567|Islamabad|Pakistan|PK123456|500
```

**bookings.txt**
```
BK001|G001|STD1|2024-06-08|2024-06-10|CheckedIn
```

**bills.txt**
```
BILL001|G001|31250|Paid
```

---

## 🎓 Educational Value

This project demonstrates:

✓ Real-world OOP design patterns
✓ Proper encapsulation and access control
✓ Inheritance hierarchies with multiple levels
✓ Polymorphism through virtual functions
✓ Abstract classes and interfaces
✓ Composition pattern implementation
✓ Memory management (new/delete, destructors)
✓ File I/O operations
✓ Operator overloading
✓ Friend functions and access control
✓ Dynamic arrays and vectors
✓ Error handling and validation

**Perfect For:**
- OOP Final Exam projects
- Semester projects
- Portfolio demonstration
- System design learning

---

## 📝 Code Statistics

- **Total Lines of Code**: ~3000+
- **Number of Classes**: 13
- **Number of Files**: 17
- **Header Files**: 8
- **Implementation Files**: 8
- **Main Driver**: 1
- **Build Configuration**: 1

---

## 🐛 Error Handling

The system includes comprehensive error checking:

- ✓ Null pointer checks
- ✓ Input validation
- ✓ Boundary checking
- ✓ File existence validation
- ✓ Room availability verification
- ✓ Booking status validation
- ✓ Guest identification verification

---

## 🔄 Demo Walkthrough

Run option 7 (Demo) to see:

1. **2 Guest registrations** with loyalty points
2. **3 Employee hires** (Receptionist, Manager, HouseKeeping)
3. **2 Booking creations** with check-ins
4. **3 Service additions** (Restaurant, Laundry, Spa)
5. **2 Bill generations** with payment methods
6. **5 Automated reports** (Hotel info, Dashboard, Occupancy, Revenue, Guests)
7. **Detailed output** of all system features

---

## 📞 System Specifications

**Hotel Details:**
- Name: Northern Heights Hotel & Resort
- Location: 123 Main Street, Islamabad
- Phone: +92-51-1234567
- Total Rooms: 20 (across 5 floors)
- Room Types: 4 categories
- Employees: Multiple departments

---

## 🎨 Features Highlight

| Feature | Implementation |
|---------|-----------------|
| Guest Registration | ✓ Encapsulation |
| Room Booking | ✓ Composition |
| Check-In/Out | ✓ Polymorphism |
| Billing System | ✓ Operator Overloading |
| Services | ✓ Abstract Base Class |
| Employee Types | ✓ Inheritance |
| Loyalty Program | ✓ Friend Functions |
| Data Storage | ✓ File Handling |
| Reports | ✓ Data Analysis |

---

## 📚 Additional Notes

- All classes follow SOLID principles
- Memory is properly managed with destructors
- Virtual destructors prevent memory leaks
- Code is well-commented and organized
- Suitable for learning and production use

---

## ✅ Testing Checklist

- [x] Guest registration and lookup
- [x] Room availability checking
- [x] Booking creation and cancellation
- [x] Check-in/Check-out functionality
- [x] Bill generation with calculations
- [x] Service additions and billing
- [x] Loyalty points tracking
- [x] Employee management
- [x] Payroll calculation
- [x] Report generation
- [x] File I/O operations
- [x] Operator overloading

---

## 🎉 Conclusion

This Smart Hotel Management System is a comprehensive C++ project that effectively demonstrates all major OOP concepts in a real-world scenario. It's perfect for educational purposes and provides a solid foundation for learning advanced programming concepts.

**Happy Coding! 🚀**

---

**Project Version**: 1.0
**Last Updated**: June 2024
**Language**: C++11
**Compiler**: GCC/Clang
