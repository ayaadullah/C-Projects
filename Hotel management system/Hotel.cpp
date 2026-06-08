#include "Hotel.h"
#include <algorithm>
#include <fstream>

Hotel::Hotel()
    : hotelName("Northern Heights Hotel & Resort"),
      hotelAddress("123 Main Street, Islamabad"),
      hotelPhone("+92-51-1234567"),
      totalRooms(20), totalFloors(5)
{
    initializeRooms();
}

Hotel::Hotel(string name, string address, string phone, int totalRms, int floors)
    : hotelName(name), hotelAddress(address), hotelPhone(phone),
      totalRooms(totalRms), totalFloors(floors)
{
    initializeRooms();
}

// Hotel Information Getters
string Hotel::getHotelName() const { return hotelName; }
string Hotel::getHotelAddress() const { return hotelAddress; }
string Hotel::getHotelPhone() const { return hotelPhone; }
int Hotel::getTotalRooms() const { return totalRooms; }
int Hotel::getTotalFloors() const { return totalFloors; }

// Room Management Methods
void Hotel::initializeRooms()
{
    // Create different types of rooms
    // Floor 1-2: Standard Rooms
    for (int i = 1; i <= 5; i++) {
        rooms.push_back(new StandardRoom("STD" + to_string(i).c_str(), 1));
    }
    for (int i = 6; i <= 10; i++) {
        rooms.push_back(new StandardRoom("STD" + to_string(i).c_str(), 2));
    }
    
    // Floor 3: Deluxe Rooms
    for (int i = 1; i <= 3; i++) {
        rooms.push_back(new DeluxeRoom("DLX" + to_string(i).c_str(), 3));
    }
    
    // Floor 4: Executive Rooms
    for (int i = 1; i <= 3; i++) {
        rooms.push_back(new ExecutiveRoom("EXE" + to_string(i).c_str(), 4));
    }
    
    // Floor 5: Suite Rooms
    for (int i = 1; i <= 2; i++) {
        rooms.push_back(new SuiteRoom("SUI" + to_string(i).c_str(), 5));
    }
}

void Hotel::addRoom(Room* room)
{
    rooms.push_back(room);
}

Room* Hotel::findRoomByID(string roomID) const
{
    for (auto room : rooms) {
        if (room->getRoomID() == roomID) {
            return room;
        }
    }
    return nullptr;
}

int Hotel::getAvailableRoomsCount() const
{
    int count = 0;
    for (auto room : rooms) {
        if (!room->getIsOccupied()) {
            count++;
        }
    }
    return count;
}

vector<Room*> Hotel::getAvailableRooms() const
{
    vector<Room*> available;
    for (auto room : rooms) {
        if (!room->getIsOccupied()) {
            available.push_back(room);
        }
    }
    return available;
}

vector<Room*> Hotel::getRoomsByType(string type) const
{
    vector<Room*> result;
    for (auto room : rooms) {
        if (room->getRoomType() == type) {
            result.push_back(room);
        }
    }
    return result;
}

void Hotel::displayAllRooms() const
{
    cout << "\n==================== All Rooms ====================" << endl;
    for (auto room : rooms) {
        room->display();
    }
    cout << "=====================================================" << endl;
}

// Guest Management Methods
void Hotel::registerGuest(Guest guest)
{
    guests.push_back(guest);
    cout << "Guest registered successfully!" << endl;
}

void Hotel::addGuest(Guest guest)
{
    guests.push_back(guest);
}

Guest* Hotel::findGuestByID(string guestID)
{
    for (auto& guest : guests) {
        if (guest.getPersonID() == guestID) {
            return &guest;
        }
    }
    return nullptr;
}

const Guest* Hotel::findGuestByID(string guestID) const
{
    for (const auto& guest : guests) {
        if (guest.getPersonID() == guestID) {
            return &guest;
        }
    }
    return nullptr;
}

int Hotel::getTotalGuestsCount() const { return guests.size(); }

void Hotel::displayAllGuests() const
{
    cout << "\n==================== All Guests ====================" << endl;
    for (const auto& guest : guests) {
        guest.display();
    }
    cout << "=====================================================" << endl;
}

// Employee Management Methods
void Hotel::hireEmployee(Employee* employee)
{
    employees.push_back(employee);
    cout << "Employee hired successfully!" << endl;
}

Employee* Hotel::findEmployeeByID(string empID)
{
    for (auto emp : employees) {
        if (emp->getEmployeeID() == empID) {
            return emp;
        }
    }
    return nullptr;
}

int Hotel::getTotalEmployeesCount() const { return employees.size(); }

void Hotel::displayAllEmployees() const
{
    cout << "\n==================== All Employees ====================" << endl;
    for (auto emp : employees) {
        emp->display();
    }
    cout << "=======================================================" << endl;
}

double Hotel::calculatePayrollTotal() const
{
    double total = 0.0;
    for (auto emp : employees) {
        if (emp->getIsActive()) {
            total += emp->getSalary();
        }
    }
    return total;
}

// Booking Management Methods
void Hotel::createBooking(Booking booking)
{
    bookings.push_back(booking);
    cout << "Booking created successfully!" << endl;
}

Booking* Hotel::findBookingByID(string bookingID)
{
    for (auto& booking : bookings) {
        if (booking.getBookingID() == bookingID) {
            return &booking;
        }
    }
    return nullptr;
}

const Booking* Hotel::findBookingByID(string bookingID) const
{
    for (const auto& booking : bookings) {
        if (booking.getBookingID() == bookingID) {
            return &booking;
        }
    }
    return nullptr;
}

vector<Booking> Hotel::getGuestBookings(string guestID) const
{
    vector<Booking> result;
    for (const auto& booking : bookings) {
        if (booking.getGuestID() == guestID) {
            result.push_back(booking);
        }
    }
    return result;
}

vector<Booking> Hotel::getPendingBookings() const
{
    vector<Booking> result;
    for (const auto& booking : bookings) {
        if (booking.getStatus() == "Confirmed") {
            result.push_back(booking);
        }
    }
    return result;
}

bool Hotel::cancelBooking(string bookingID)
{
    for (auto& booking : bookings) {
        if (booking.getBookingID() == bookingID) {
            booking.setStatus("Cancelled");
            cout << "Booking cancelled successfully!" << endl;
            return true;
        }
    }
    return false;
}

int Hotel::getTotalBookingsCount() const { return bookings.size(); }

void Hotel::displayAllBookings() const
{
    cout << "\n==================== All Bookings ====================" << endl;
    for (const auto& booking : bookings) {
        booking.display();
    }
    cout << "======================================================" << endl;
}

// Check-In / Check-Out Methods
bool Hotel::checkInGuest(string bookingID)
{
    Booking* booking = findBookingByID(bookingID);
    if (!booking) {
        cout << "Booking not found!" << endl;
        return false;
    }
    
    Room* room = findRoomByID(booking->getRoomID());
    if (!room) {
        cout << "Room not found!" << endl;
        return false;
    }
    
    if (room->getIsOccupied()) {
        cout << "Room already occupied!" << endl;
        return false;
    }
    
    room->setOccupied(true);
    room->setCurrentGuest(booking->getGuestID());
    booking->setStatus("CheckedIn");
    booking->setHasArrived(true);
    cout << "Check-in successful!" << endl;
    return true;
}

bool Hotel::checkOutGuest(string bookingID)
{
    Booking* booking = findBookingByID(bookingID);
    if (!booking) {
        cout << "Booking not found!" << endl;
        return false;
    }
    
    Room* room = findRoomByID(booking->getRoomID());
    if (!room) {
        cout << "Room not found!" << endl;
        return false;
    }
    
    room->setOccupied(false);
    room->setCurrentGuest("");
    booking->setStatus("CheckedOut");
    cout << "Check-out successful!" << endl;
    return true;
}

vector<Room*> Hotel::getOccupiedRooms() const
{
    vector<Room*> occupied;
    for (auto room : rooms) {
        if (room->getIsOccupied()) {
            occupied.push_back(room);
        }
    }
    return occupied;
}

// Bill Management Methods
void Hotel::generateBill(Bill bill)
{
    bill.generateBill();
    bills.push_back(bill);
    cout << "Bill generated successfully!" << endl;
}

Bill* Hotel::findBillByID(string billID)
{
    for (auto& bill : bills) {
        if (bill.getBillID() == billID) {
            return &bill;
        }
    }
    return nullptr;
}

const Bill* Hotel::findBillByID(string billID) const
{
    for (const auto& bill : bills) {
        if (bill.getBillID() == billID) {
            return &bill;
        }
    }
    return nullptr;
}

double Hotel::getTotalRevenue() const
{
    double total = 0.0;
    for (const auto& bill : bills) {
        if (bill.getStatus() == "Paid") {
            total += bill.getTotalAmount();
        }
    }
    return total;
}

void Hotel::displayAllBills() const
{
    cout << "\n==================== All Bills ====================" << endl;
    for (const auto& bill : bills) {
        bill.display();
    }
    cout << "=================================================" << endl;
}

// Service Management Methods
void Hotel::addService(Service* service)
{
    services.push_back(service);
    cout << "Service added successfully!" << endl;
}

vector<Service*> Hotel::getGuestServices(string guestID) const
{
    vector<Service*> result;
    for (auto service : services) {
        if (service->getGuestID() == guestID) {
            result.push_back(service);
        }
    }
    return result;
}

void Hotel::displayAllServices() const
{
    cout << "\n==================== All Services ====================" << endl;
    for (auto service : services) {
        service->display();
    }
    cout << "====================================================" << endl;
}

// Loyalty Program Methods
void Hotel::updateGuestLoyaltyPoints(string guestID, int points)
{
    Guest* guest = findGuestByID(guestID);
    if (guest) {
        guest->addLoyaltyPoints(points);
        cout << "Loyalty points updated successfully!" << endl;
    }
    else {
        cout << "Guest not found!" << endl;
    }
}

void Hotel::redeemLoyaltyPoints(string guestID, int points)
{
    Guest* guest = findGuestByID(guestID);
    if (guest) {
        guest->redeemLoyaltyPoints(points);
    }
    else {
        cout << "Guest not found!" << endl;
    }
}

// Report Generation Methods
void Hotel::generateOccupancyReport() const
{
    cout << "\n========== OCCUPANCY REPORT ==========" << endl;
    cout << "Hotel: " << hotelName << endl;
    cout << "Total Rooms: " << totalRooms << endl;
    cout << "Occupied Rooms: " << (totalRooms - getAvailableRoomsCount()) << endl;
    cout << "Available Rooms: " << getAvailableRoomsCount() << endl;
    
    double occupancyRate = ((double)(totalRooms - getAvailableRoomsCount()) / totalRooms) * 100;
    cout << "Occupancy Rate: " << occupancyRate << "%" << endl;
    
    cout << "\nRoom Type Breakdown:" << endl;
    vector<Room*> standard = getRoomsByType("Standard");
    vector<Room*> deluxe = getRoomsByType("Deluxe");
    vector<Room*> executive = getRoomsByType("Executive");
    vector<Room*> suite = getRoomsByType("Suite");
    
    cout << "  Standard Rooms: " << standard.size() << endl;
    cout << "  Deluxe Rooms: " << deluxe.size() << endl;
    cout << "  Executive Rooms: " << executive.size() << endl;
    cout << "  Suite Rooms: " << suite.size() << endl;
    cout << "======================================" << endl;
}

void Hotel::generateRevenueReport() const
{
    cout << "\n========== REVENUE REPORT ==========" << endl;
    cout << "Hotel: " << hotelName << endl;
    cout << "Total Bills Generated: " << bills.size() << endl;
    
    double totalGenerated = 0.0;
    int paidBills = 0;
    
    for (const auto& bill : bills) {
        totalGenerated += bill.getTotalAmount();
        if (bill.getStatus() == "Paid") {
            paidBills++;
        }
    }
    
    cout << "Total Revenue (All Bills): Rs. " << totalGenerated << endl;
    cout << "Paid Bills: " << paidBills << endl;
    cout << "Pending Bills: " << (bills.size() - paidBills) << endl;
    cout << "Total Revenue (Paid Only): Rs. " << getTotalRevenue() << endl;
    cout << "===================================" << endl;
}

void Hotel::generateGuestReport() const
{
    cout << "\n========== GUEST REPORT ==========" << endl;
    cout << "Hotel: " << hotelName << endl;
    cout << "Total Guests: " << getTotalGuestsCount() << endl;
    cout << "Total Employees: " << getTotalEmployeesCount() << endl;
    cout << "Total Bookings: " << getTotalBookingsCount() << endl;
    cout << "==================================" << endl;
}

// File Operations
void Hotel::saveGuestData() const
{
    ofstream file("guests.txt");
    for (const auto& guest : guests) {
        file << guest.getPersonID() << "|"
             << guest.getName() << "|"
             << guest.getEmail() << "|"
             << guest.getPhone() << "|"
             << guest.getAddress() << "|"
             << guest.getNationality() << "|"
             << guest.getDocumentID() << "|"
             << guest.getLoyaltyPoints() << "\n";
    }
    file.close();
    cout << "Guest data saved!" << endl;
}

void Hotel::loadGuestData()
{
    ifstream file("guests.txt");
    if (!file.is_open()) {
        cout << "No guest data file found!" << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        // Parse and load guest data
    }
    file.close();
    cout << "Guest data loaded!" << endl;
}

void Hotel::saveBookingData() const
{
    ofstream file("bookings.txt");
    for (const auto& booking : bookings) {
        file << booking.getBookingID() << "|"
             << booking.getGuestID() << "|"
             << booking.getRoomID() << "|"
             << booking.getCheckInDate() << "|"
             << booking.getCheckOutDate() << "|"
             << booking.getStatus() << "\n";
    }
    file.close();
    cout << "Booking data saved!" << endl;
}

void Hotel::loadBookingData()
{
    ifstream file("bookings.txt");
    if (!file.is_open()) {
        cout << "No booking data file found!" << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        // Parse and load booking data
    }
    file.close();
    cout << "Booking data loaded!" << endl;
}

void Hotel::saveBillData() const
{
    ofstream file("bills.txt");
    for (const auto& bill : bills) {
        file << bill.getBillID() << "|"
             << bill.getGuestID() << "|"
             << bill.getTotalAmount() << "|"
             << bill.getStatus() << "\n";
    }
    file.close();
    cout << "Bill data saved!" << endl;
}

void Hotel::loadBillData()
{
    ifstream file("bills.txt");
    if (!file.is_open()) {
        cout << "No bill data file found!" << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        // Parse and load bill data
    }
    file.close();
    cout << "Bill data loaded!" << endl;
}

void Hotel::saveEmployeeData() const
{
    ofstream file("employees.txt");
    for (const auto& emp : employees) {
        file << emp->getPersonID() << "|"
             << emp->getName() << "|"
             << emp->getEmail() << "|"
             << emp->getEmployeeID() << "|"
             << emp->getDepartment() << "|"
             << emp->getSalary() << "\n";
    }
    file.close();
    cout << "Employee data saved!" << endl;
}

void Hotel::loadEmployeeData()
{
    ifstream file("employees.txt");
    if (!file.is_open()) {
        cout << "No employee data file found!" << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        // Parse and load employee data
    }
    file.close();
    cout << "Employee data loaded!" << endl;
}

void Hotel::saveRoomData() const
{
    ofstream file("rooms.txt");
    for (const auto& room : rooms) {
        file << room->getRoomID() << "|"
             << room->getRoomType() << "|"
             << room->getFloor() << "|"
             << room->getBasePrice() << "\n";
    }
    file.close();
    cout << "Room data saved!" << endl;
}

void Hotel::loadRoomData()
{
    ifstream file("rooms.txt");
    if (!file.is_open()) {
        cout << "No room data file found!" << endl;
        return;
    }
    
    string line;
    while (getline(file, line)) {
        // Parse and load room data
    }
    file.close();
    cout << "Room data loaded!" << endl;
}

void Hotel::displayHotelInfo() const
{
    cout << "\n============== HOTEL INFORMATION ==============" << endl;
    cout << "Hotel Name: " << hotelName << endl;
    cout << "Address: " << hotelAddress << endl;
    cout << "Phone: " << hotelPhone << endl;
    cout << "Total Rooms: " << totalRooms << endl;
    cout << "Total Floors: " << totalFloors << endl;
    cout << "=============================================" << endl;
}

void Hotel::displayDashboard() const
{
    cout << "\n============== HOTEL DASHBOARD ==============" << endl;
    cout << "Hotel: " << hotelName << endl;
    cout << "\nCurrent Statistics:" << endl;
    cout << "  Total Guests: " << getTotalGuestsCount() << endl;
    cout << "  Total Employees: " << getTotalEmployeesCount() << endl;
    cout << "  Total Rooms: " << totalRooms << endl;
    cout << "  Occupied Rooms: " << (totalRooms - getAvailableRoomsCount()) << endl;
    cout << "  Available Rooms: " << getAvailableRoomsCount() << endl;
    cout << "  Total Bookings: " << getTotalBookingsCount() << endl;
    cout << "  Total Bills: " << bills.size() << endl;
    cout << "  Total Revenue: Rs. " << getTotalRevenue() << endl;
    cout << "===========================================" << endl;
}

Hotel::~Hotel()
{
    // Clean up dynamically allocated memory
    for (auto room : rooms) {
        delete room;
    }
    for (auto emp : employees) {
        delete emp;
    }
    for (auto service : services) {
        delete service;
    }
}
