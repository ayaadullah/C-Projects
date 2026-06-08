#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <iostream>
#include <ctime>

using namespace std;

class Booking
{
private:
    string bookingID;
    string guestID;
    string roomID;
    string checkInDate;
    string checkOutDate;
    int numberOfNights;
    double pricePerNight;
    string status; // Confirmed, CheckedIn, CheckedOut, Cancelled
    string bookingDate;
    bool hasArrived;

public:
    Booking();
    Booking(string bID, string gID, string rID, string checkIn,
            string checkOut, double price);
    
    // Getters
    string getBookingID() const;
    string getGuestID() const;
    string getRoomID() const;
    string getCheckInDate() const;
    string getCheckOutDate() const;
    int getNumberOfNights() const;
    double getPricePerNight() const;
    string getStatus() const;
    string getBookingDate() const;
    bool getHasArrived() const;
    
    // Setters
    void setStatus(string s);
    void setHasArrived(bool arrived);
    
    // Booking operations
    double calculateTotalCost() const;
    bool isValid() const;
    void display() const;
    
    // Operator overloading
    bool operator==(const Booking& other) const;
    bool operator<(const Booking& other) const; // By booking date
};

#endif
