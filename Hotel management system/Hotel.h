#ifndef HOTEL_H
#define HOTEL_H

#include "Person.h"
#include "Guest.h"
#include "Employee.h"
#include "Room.h"
#include "Booking.h"
#include "Bill.h"
#include "Service.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Hotel
{
private:
    string hotelName;
    string hotelAddress;
    string hotelPhone;
    int totalRooms;
    int totalFloors;
    vector<Room*> rooms;              // Composition - Hotel has Rooms
    vector<Guest> guests;              // Composition - Hotel has Guests
    vector<Employee*> employees;       // Composition - Hotel has Employees
    vector<Booking> bookings;          // Composition - Hotel has Bookings
    vector<Bill> bills;                // Composition - Hotel has Bills
    vector<Service*> services;         // Composition - Hotel has Services

public:
    Hotel();
    Hotel(string name, string address, string phone, int totalRms, int floors);
    
    // Hotel Information
    string getHotelName() const;
    string getHotelAddress() const;
    string getHotelPhone() const;
    int getTotalRooms() const;
    int getTotalFloors() const;
    
    // Room Management
    void initializeRooms();
    void addRoom(Room* room);
    Room* findRoomByID(string roomID) const;
    int getAvailableRoomsCount() const;
    vector<Room*> getAvailableRooms() const;
    vector<Room*> getRoomsByType(string type) const;
    void displayAllRooms() const;
    
    // Guest Management
    void registerGuest(Guest guest);
    void addGuest(Guest guest);
    Guest* findGuestByID(string guestID);
    const Guest* findGuestByID(string guestID) const;
    int getTotalGuestsCount() const;
    void displayAllGuests() const;
    
    // Employee Management
    void hireEmployee(Employee* employee);
    Employee* findEmployeeByID(string empID);
    int getTotalEmployeesCount() const;
    void displayAllEmployees() const;
    double calculatePayrollTotal() const;
    
    // Booking Management
    void createBooking(Booking booking);
    Booking* findBookingByID(string bookingID);
    const Booking* findBookingByID(string bookingID) const;
    vector<Booking> getGuestBookings(string guestID) const;
    vector<Booking> getPendingBookings() const;
    bool cancelBooking(string bookingID);
    int getTotalBookingsCount() const;
    void displayAllBookings() const;
    
    // Check-In / Check-Out
    bool checkInGuest(string bookingID);
    bool checkOutGuest(string bookingID);
    vector<Room*> getOccupiedRooms() const;
    
    // Bill Management
    void generateBill(Bill bill);
    Bill* findBillByID(string billID);
    const Bill* findBillByID(string billID) const;
    double getTotalRevenue() const;
    void displayAllBills() const;
    
    // Service Management
    void addService(Service* service);
    vector<Service*> getGuestServices(string guestID) const;
    void displayAllServices() const;
    
    // Loyalty Program
    void updateGuestLoyaltyPoints(string guestID, int points);
    void redeemLoyaltyPoints(string guestID, int points);
    
    // Reports
    void generateOccupancyReport() const;
    void generateRevenueReport() const;
    void generateGuestReport() const;
    
    // File Operations
    void saveGuestData() const;
    void loadGuestData();
    void saveBookingData() const;
    void loadBookingData();
    void saveBillData() const;
    void loadBillData();
    void saveEmployeeData() const;
    void loadEmployeeData();
    void saveRoomData() const;
    void loadRoomData();
    
    // Display Hotel Information
    void displayHotelInfo() const;
    void displayDashboard() const;
    
    // Destructor
    ~Hotel();
};

#endif
