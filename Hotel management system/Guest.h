#ifndef GUEST_H
#define GUEST_H

#include "Person.h"
#include <vector>

using namespace std;

class Guest : public Person
{
private:
    string nationality;
    string documentID;
    int loyaltyPoints;
    double totalSpent;
    vector<string> bookingHistory;

public:
    Guest();
    Guest(string id, string n, string e, string p, string a, 
          string nat, string docID);
    
    // Getters
    string getNationality() const;
    string getDocumentID() const;
    int getLoyaltyPoints() const;
    double getTotalSpent() const;
    vector<string> getBookingHistory() const;
    
    // Loyalty program methods
    void addLoyaltyPoints(int points);
    void redeemLoyaltyPoints(int points);
    double getLoyaltyDiscount() const;
    
    // Booking history
    void addBooking(string bookingID);
    
    // Update spending
    void updateTotalSpent(double amount);
    
    // Override display
    void display() const override;
    
    // Friend function for bill access
    friend double calculateGuestDiscount(const Guest& guest, double billAmount);
};

#endif
