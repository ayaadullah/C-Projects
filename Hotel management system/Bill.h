#ifndef BILL_H
#define BILL_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Bill
{
private:
    string billID;
    string guestID;
    string bookingID;
    double roomCharges;
    double serviceCharges;
    double restaurantCharges;
    double laundryCharges;
    double spaCharges;
    double otherCharges;
    double discountPercentage;
    double taxPercentage;
    double totalAmount;
    string generatedDate;
    string status; // Pending, Paid, Cancelled
    string paymentMethod; // Credit Card, Debit Card, Cash

public:
    Bill();
    Bill(string bID, string gID, string bookID);
    
    // Getters
    string getBillID() const;
    string getGuestID() const;
    string getBookingID() const;
    double getRoomCharges() const;
    double getServiceCharges() const;
    double getRestaurantCharges() const;
    double getLaundryCharges() const;
    double getSpaCharges() const;
    double getOtherCharges() const;
    double getDiscountPercentage() const;
    double getTaxPercentage() const;
    double getTotalAmount() const;
    string getGeneratedDate() const;
    string getStatus() const;
    string getPaymentMethod() const;
    
    // Setters
    void setRoomCharges(double charges);
    void setServiceCharges(double charges);
    void setRestaurantCharges(double charges);
    void setLaundryCharges(double charges);
    void setSpaCharges(double charges);
    void setOtherCharges(double charges);
    void setDiscountPercentage(double discount);
    void setTaxPercentage(double tax);
    void setStatus(string s);
    void setPaymentMethod(string method);
    
    // Bill calculation
    double calculateSubtotal() const;
    double calculateDiscount() const;
    double calculateTax() const;
    void calculateTotal();
    void generateBill();
    
    // Display
    void display() const;
    
    // Operator Overloading
    bool operator==(const Bill& other) const;
    bool operator>(const Bill& other) const; // Compare by total amount
    bool operator<(const Bill& other) const; // Compare by total amount
    Bill operator+(double amount) const; // Add extra charges
    Bill operator-(double amount) const; // Apply discount
    Bill& operator+=(double amount); // Add charges
    Bill& operator-=(double amount); // Apply discount
    
    // Friend function for accessing private members
    friend void printBillDetails(const Bill& bill);
    friend double calculateGuestDiscount(const Bill& bill, double loyaltyPoints);
};

#endif
