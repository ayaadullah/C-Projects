#include "Guest.h"

Guest::Guest()
    : Person(), nationality(""), documentID(""), loyaltyPoints(0), totalSpent(0.0)
{
}

Guest::Guest(string id, string n, string e, string p, string a, string nat, string docID)
    : Person(id, n, e, p, a), nationality(nat), documentID(docID), loyaltyPoints(0), totalSpent(0.0)
{
}

string Guest::getNationality() const { return nationality; }
string Guest::getDocumentID() const { return documentID; }
int Guest::getLoyaltyPoints() const { return loyaltyPoints; }
double Guest::getTotalSpent() const { return totalSpent; }
vector<string> Guest::getBookingHistory() const { return bookingHistory; }

void Guest::addLoyaltyPoints(int points)
{
    loyaltyPoints += points;
}

void Guest::redeemLoyaltyPoints(int points)
{
    if (loyaltyPoints >= points)
    {
        loyaltyPoints -= points;
    }
    else
    {
        cout << "Insufficient loyalty points!" << endl;
    }
}

double Guest::getLoyaltyDiscount() const
{
    // 1 point = 0.1% discount, max 10% discount
    double discount = (loyaltyPoints * 0.001);
    return (discount > 10.0) ? 10.0 : discount;
}

void Guest::addBooking(string bookingID)
{
    bookingHistory.push_back(bookingID);
}

void Guest::updateTotalSpent(double amount)
{
    totalSpent += amount;
}

void Guest::display() const
{
    cout << "\n===== Guest Information =====" << endl;
    cout << "Guest ID: " << personID << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Address: " << address << endl;
    cout << "Nationality: " << nationality << endl;
    cout << "Document ID: " << documentID << endl;
    cout << "Loyalty Points: " << loyaltyPoints << endl;
    cout << "Loyalty Discount: " << getLoyaltyDiscount() << "%" << endl;
    cout << "Total Amount Spent: Rs. " << totalSpent << endl;
    cout << "Number of Bookings: " << bookingHistory.size() << endl;
    cout << "=============================" << endl;
}

// Friend function implementation
double calculateGuestDiscount(const Guest& guest, double billAmount)
{
    double discount = billAmount * (guest.loyaltyPoints * 0.001);
    return (discount > billAmount * 0.1) ? billAmount * 0.1 : discount;
}
