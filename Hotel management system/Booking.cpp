#include "Booking.h"

Booking::Booking()
    : bookingID(""), guestID(""), roomID(""), checkInDate(""), checkOutDate(""),
      numberOfNights(0), pricePerNight(0.0), status("Pending"), hasArrived(false)
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    bookingDate = string(buffer);
}

Booking::Booking(string bID, string gID, string rID, string checkIn,
                 string checkOut, double price)
    : bookingID(bID), guestID(gID), roomID(rID), checkInDate(checkIn),
      checkOutDate(checkOut), pricePerNight(price), status("Confirmed"), hasArrived(false)
{
    // Calculate number of nights (simple calculation)
    numberOfNights = 1; // For simplicity, assuming 1 night
    
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    bookingDate = string(buffer);
}

string Booking::getBookingID() const { return bookingID; }
string Booking::getGuestID() const { return guestID; }
string Booking::getRoomID() const { return roomID; }
string Booking::getCheckInDate() const { return checkInDate; }
string Booking::getCheckOutDate() const { return checkOutDate; }
int Booking::getNumberOfNights() const { return numberOfNights; }
double Booking::getPricePerNight() const { return pricePerNight; }
string Booking::getStatus() const { return status; }
string Booking::getBookingDate() const { return bookingDate; }
bool Booking::getHasArrived() const { return hasArrived; }

void Booking::setStatus(string s) { status = s; }
void Booking::setHasArrived(bool arrived) { hasArrived = arrived; }

double Booking::calculateTotalCost() const
{
    return pricePerNight * numberOfNights;
}

bool Booking::isValid() const
{
    return status != "Cancelled" && !bookingID.empty();
}

void Booking::display() const
{
    cout << "\n===== Booking Information =====" << endl;
    cout << "Booking ID: " << bookingID << endl;
    cout << "Guest ID: " << guestID << endl;
    cout << "Room ID: " << roomID << endl;
    cout << "Check-In Date: " << checkInDate << endl;
    cout << "Check-Out Date: " << checkOutDate << endl;
    cout << "Number of Nights: " << numberOfNights << endl;
    cout << "Price per Night: Rs. " << pricePerNight << endl;
    cout << "Total Cost: Rs. " << calculateTotalCost() << endl;
    cout << "Status: " << status << endl;
    cout << "Booking Date: " << bookingDate << endl;
    cout << "Arrived: " << (hasArrived ? "Yes" : "No") << endl;
    cout << "===============================" << endl;
}

// Operator Overloading Implementation
bool Booking::operator==(const Booking& other) const
{
    return bookingID == other.bookingID;
}

bool Booking::operator<(const Booking& other) const
{
    return bookingDate < other.bookingDate; // Compare by booking date
}
