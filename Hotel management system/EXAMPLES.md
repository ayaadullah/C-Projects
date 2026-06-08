# 💡 Example Usage & Code Snippets

Quick reference guide for using the Smart Hotel Management System.

---

## 🎯 Quick Start Examples

### 1. Creating and Managing Guests

```cpp
// Create a guest
Guest guest1("G001", "Ahmed Khan", "ahmed@email.com", 
             "03001234567", "Islamabad", "Pakistan", "PK123456");

// Add guest to hotel
hotel.addGuest(guest1);

// Add loyalty points
guest1.addLoyaltyPoints(500);

// Display guest information
guest1.display();

// Get guest details
cout << "Name: " << guest1.getName() << endl;
cout << "Email: " << guest1.getEmail() << endl;
cout << "Loyalty Points: " << guest1.getLoyaltyPoints() << endl;
cout << "Loyalty Discount: " << guest1.getLoyaltyDiscount() << "%" << endl;

// Find guest by ID
Guest* foundGuest = hotel.findGuestByID("G001");
if (foundGuest) {
    foundGuest->display();
}
```

---

### 2. Managing Rooms

```cpp
// Hotel automatically initializes rooms in constructor
// Total: 20 rooms (10 Standard, 3 Deluxe, 3 Executive, 2 Suite)

// Display all rooms
hotel.displayAllRooms();

// Get available rooms
int available = hotel.getAvailableRoomsCount();
cout << "Available Rooms: " << available << endl;

// Get rooms of specific type
vector<Room*> deluxeRooms = hotel.getRoomsByType("Deluxe");
cout << "Deluxe Rooms: " << deluxeRooms.size() << endl;

// Access room details
Room* room = hotel.findRoomByID("STD1");
if (room) {
    room->display();
    cout << "Price: Rs. " << room->calculatePrice() << endl;
    cout << "Service Charge: Rs. " << room->getServiceCharge() << endl;
}

// Create custom room
room = new ExecutiveRoom("EXE10", 4);
hotel.addRoom(room);
```

---

### 3. Booking System

```cpp
// Create a booking
string bookingID = "BK001";
string guestID = "G001";
string roomID = "STD1";
string checkIn = "2024-06-08";
string checkOut = "2024-06-10";
double pricePerNight = 3000;

Booking booking(bookingID, guestID, roomID, checkIn, checkOut, pricePerNight);
hotel.createBooking(booking);

// Get booking details
Booking* myBooking = hotel.findBookingByID("BK001");
if (myBooking) {
    cout << "Booking ID: " << myBooking->getBookingID() << endl;
    cout << "Guest: " << myBooking->getGuestID() << endl;
    cout << "Room: " << myBooking->getRoomID() << endl;
    cout << "Total Cost: Rs. " << myBooking->calculateTotalCost() << endl;
}

// Check-in guest
hotel.checkInGuest("BK001");

// Check-out guest
hotel.checkOutGuest("BK001");

// Cancel booking
hotel.cancelBooking("BK001");

// Get all bookings for a guest
vector<Booking> guestBookings = hotel.getGuestBookings("G001");
cout << "Total Bookings: " << guestBookings.size() << endl;
```

---

### 4. Employee Management

#### Creating a Receptionist

```cpp
Receptionist* receptionist = new Receptionist(
    "P001",              // Person ID
    "Hassan Ahmed",      // Name
    "hassan@hotel.com",  // Email
    "051-1111111",       // Phone
    "Islamabad",         // Address
    "E001",              // Employee ID
    30000,               // Salary
    "2023-01-15"         // Join Date
);

// Record operations
receptionist->incrementCheckIn();
receptionist->incrementCheckOut();

hotel.hireEmployee(receptionist);
receptionist->display();

// Calculate bonus
cout << "Bonus: Rs. " << receptionist->calculateBonus() << endl;
```

#### Creating a Manager

```cpp
Manager* manager = new Manager(
    "P002",           // Person ID
    "Saira Khan",     // Name
    "saira@hotel.com", // Email
    "051-2222222",    // Phone
    "Islamabad",      // Address
    "E002",           // Employee ID
    50000,            // Salary
    "2022-06-10",     // Join Date
    "Front Desk Manager"  // Manager Type
);

manager->setStaffManaged(5);
hotel.hireEmployee(manager);

cout << "Managing " << manager->getStaffManaged() << " staff" << endl;
cout << "Bonus: Rs. " << manager->calculateBonus() << endl;
```

#### Creating Housekeeping Staff

```cpp
HouseKeeping* housekeeper = new HouseKeeping(
    "P003",          // Person ID
    "Muhammad Ali",  // Name
    "ali@hotel.com", // Email
    "051-3333333",   // Phone
    "Islamabad",     // Address
    "E003",          // Employee ID
    25000,           // Salary
    "2023-03-20",    // Join Date
    "Morning"        // Shift (Morning/Afternoon/Night)
);

housekeeper->incrementRoomsCleaned();
housekeeper->incrementRoomsCleaned();
housekeeper->incrementRoomsCleaned();

hotel.hireEmployee(housekeeper);
cout << "Rooms Cleaned: " << housekeeper->getRoomsCleaned() << endl;
cout << "Bonus: Rs. " << housekeeper->calculateBonus() << endl;
```

---

### 5. Services Management

#### Restaurant Service

```cpp
RestaurantService* restaurant = new RestaurantService(
    "S001",           // Service ID
    "G001",           // Guest ID
    "Biryani",        // Dish Name
    2,                // Quantity
    500,              // Price per item
    "Lunch",          // Meal Type
    "2024-06-08"      // Date
);

hotel.addService(restaurant);
restaurant->display();

// Calculate bill with service charge and GST
double restaurantBill = restaurant->calculateBill();
cout << "Total Bill: Rs. " << restaurantBill << endl;

// Expected calculation:
// Subtotal: 500 * 2 = 1000
// Service Charge (10%): 100
// GST (17% on total): 187
// Total: 1287
```

#### Laundry Service

```cpp
LaundryService* laundry = new LaundryService(
    "S002",           // Service ID
    "G001",           // Guest ID
    5,                // Number of Items
    "Dry Cleaning",   // Type (Regular/Dry Cleaning/Express)
    50,               // Price per item
    "2024-06-08"      // Date
);

hotel.addService(laundry);
laundry->display();

// Calculate with extra charges
double laundryBill = laundry->calculateBill();
cout << "Laundry Bill: Rs. " << laundryBill << endl;

// Expected calculation:
// Subtotal: 50 * 5 = 250
// Extra charge (25% for Dry Cleaning): 62.5
// Total: 312.5
```

#### Spa Service

```cpp
SpaService* spa = new SpaService(
    "S003",           // Service ID
    "G002",           // Guest ID
    "Full Body Spa",  // Treatment Type
    60,               // Duration (minutes)
    100,              // Price per minute
    "2024-06-08"      // Date
);

hotel.addService(spa);
spa->display();

// Calculate spa bill
double spaBill = spa->calculateBill();
cout << "Spa Bill: Rs. " << spaBill << endl;

// Expected calculation:
// Treatment Cost: 100 * 60 = 6000
// Service Charge (15%): 900
// Total: 6900
```

---

### 6. Bill Generation

```cpp
// Create a bill
Bill bill("BILL001", "G001", "BK001");

// Add charges
bill.setRoomCharges(6000);      // 2 nights * Rs. 3000
bill.setServiceCharges(600);    // 10% service charge
bill.setRestaurantCharges(1000); // Food
bill.setLaundryCharges(250);    // Laundry
bill.setSpaCharges(6000);       // Spa treatment
bill.setOtherCharges(500);      // Miscellaneous

// Apply discount
bill.setDiscountPercentage(10);  // 10% discount

// Generate bill
hotel.generateBill(bill);
bill.display();

// Output shows:
// Subtotal: 14350
// Discount (10%): 1435
// Tax (17%): 2195.55
// Total: 15110.55
```

### Bill Operator Overloading Examples

```cpp
Bill bill1("BILL001", "G001", "BK001");
bill1.setRoomCharges(5000);

// Add extra charges using +
Bill bill2 = bill1 + 1000;  // Add Rs. 1000

// Apply discount using -
Bill bill3 = bill1 - 500;   // Discount Rs. 500

// Compound operations
bill1 += 500;   // Add Rs. 500 to charges
bill1 -= 1000;  // Apply Rs. 1000 discount

// Comparisons
if (bill1 > bill2) {
    cout << "Bill1 is more expensive" << endl;
}

if (bill1 == bill2) {
    cout << "Same bill ID" << endl;
}

// Friend function for special access
printBillDetails(bill1);  // Can access private members!
double discount = calculateGuestDiscount(guest1, bill1.getTotalAmount());
```

---

### 7. Loyalty Program

```cpp
// Add loyalty points
guest1.addLoyaltyPoints(500);

// Check loyalty balance
cout << "Loyalty Points: " << guest1.getLoyaltyPoints() << endl;

// Calculate automatic discount
double discount = guest1.getLoyaltyDiscount();
cout << "Loyalty Discount: " << discount << "%" << endl;

// Redeem points
guest1.redeemLoyaltyPoints(300);

// Track booking history
guest1.addBooking("BK001");
guest1.addBooking("BK002");
vector<string> history = guest1.getBookingHistory();
cout << "Total Bookings: " << history.size() << endl;

// Update total spending
guest1.updateTotalSpent(15000);
cout << "Total Spent: Rs. " << guest1.getTotalSpent() << endl;
```

---

### 8. Reporting Features

```cpp
// Display all rooms
hotel.displayAllRooms();

// Display all guests
hotel.displayAllGuests();

// Display all employees
hotel.displayAllEmployees();

// Display all bookings
hotel.displayAllBookings();

// Display all bills
hotel.displayAllBills();

// Display all services
hotel.displayAllServices();

// Generate reports
hotel.displayHotelInfo();
hotel.displayDashboard();
hotel.generateOccupancyReport();
hotel.generateRevenueReport();
hotel.generateGuestReport();

// Statistics
cout << "Total Rooms: " << hotel.getTotalRooms() << endl;
cout << "Available Rooms: " << hotel.getAvailableRoomsCount() << endl;
cout << "Total Guests: " << hotel.getTotalGuestsCount() << endl;
cout << "Total Employees: " << hotel.getTotalEmployeesCount() << endl;
cout << "Total Bookings: " << hotel.getTotalBookingsCount() << endl;
cout << "Total Revenue: Rs. " << hotel.getTotalRevenue() << endl;
cout << "Payroll Total: Rs. " << hotel.calculatePayrollTotal() << endl;
```

---

### 9. Data Persistence

```cpp
// Save all data before exiting
hotel.saveGuestData();      // Saves to guests.txt
hotel.saveBookingData();    // Saves to bookings.txt
hotel.saveBillData();       // Saves to bills.txt
hotel.saveEmployeeData();   // Saves to employees.txt
hotel.saveRoomData();       // Saves to rooms.txt

// Load data on startup
hotel.loadGuestData();
hotel.loadBookingData();
hotel.loadBillData();
hotel.loadEmployeeData();
hotel.loadRoomData();
```

---

### 10. Complete Workflow Example

```cpp
// Step 1: Create Hotel
Hotel myHotel("Northern Heights Hotel", "123 Main St", "051-1234567", 20, 5);

// Step 2: Register Guest
Guest guest("G001", "Ahmed Khan", "ahmed@email.com", "03001234567", 
            "Islamabad", "Pakistan", "PK123456");
myHotel.addGuest(guest);

// Step 3: Create Booking
Booking booking("BK001", "G001", "STD1", "2024-06-08", "2024-06-10", 3000);
myHotel.createBooking(booking);

// Step 4: Check-in
myHotel.checkInGuest("BK001");

// Step 5: Add Services
RestaurantService* restaurant = new RestaurantService(
    "S001", "G001", "Biryani", 2, 500, "Lunch", "2024-06-08");
myHotel.addService(restaurant);

// Step 6: Generate Bill
Bill bill("BILL001", "G001", "BK001");
bill.setRoomCharges(6000);
bill.setRestaurantCharges(1000);
bill.setDiscountPercentage(10);
bill.setPaymentMethod("Credit Card");
myHotel.generateBill(bill);

// Step 7: Check-out
myHotel.checkOutGuest("BK001");

// Step 8: Display Results
bill.display();
myHotel.generateRevenueReport();

// Step 9: Save Data
myHotel.saveGuestData();
myHotel.saveBookingData();
myHotel.saveBillData();
```

---

## 📝 Common Patterns

### Polymorphic Service Processing

```cpp
void processAllServices(Hotel& hotel, string guestID) {
    vector<Service*> services = hotel.getGuestServices(guestID);
    
    double totalCost = 0;
    for (auto service : services) {
        service->display();  // Polymorphic!
        totalCost += service->calculateBill();  // Polymorphic!
    }
    
    cout << "Total Service Cost: Rs. " << totalCost << endl;
}
```

### Room Type Filtering

```cpp
void displayRoomsByType(Hotel& hotel, string type) {
    vector<Room*> rooms = hotel.getRoomsByType(type);
    
    cout << type << " Rooms Available: " << endl;
    for (auto room : rooms) {
        room->display();  // Polymorphic display
        cout << "Total Price: Rs. " << room->calculatePrice() 
             << " + Service: Rs. " << room->getServiceCharge() << endl;
    }
}
```

### Employee Bonus Calculation

```cpp
void displayEmployeeBonuses(Hotel& hotel) {
    vector<Employee*> allEmployees;
    // Assuming we have a method to get all employees
    
    double totalBonus = 0;
    for (auto emp : allEmployees) {
        cout << emp->getName() << ": Rs. " 
             << emp->calculateBonus() << endl;  // Polymorphic!
        totalBonus += emp->calculateBonus();
    }
    
    cout << "Total Bonus Payout: Rs. " << totalBonus << endl;
}
```

---

## 🔍 Debugging Tips

```cpp
// Display full guest details
guest.display();

// Display room details
room->display();

// Display booking details
booking.display();

// Display service details
service->display();

// Display bill with all charges
bill.display();

// Check hotel status
myHotel.displayDashboard();

// Verify all data
myHotel.displayAllRooms();
myHotel.displayAllGuests();
myHotel.displayAllBookings();
myHotel.displayAllBills();
```

---

These examples cover all major functionality of the Smart Hotel Management System! 🚀

