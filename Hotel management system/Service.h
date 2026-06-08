#ifndef SERVICE_H
#define SERVICE_H

#include <string>
#include <iostream>

using namespace std;

// Abstract Service class
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
    Service(string sID, string gID, double cost, string date);
    
    string getServiceID() const;
    string getGuestID() const;
    double getBaseCost() const;
    string getServiceDate() const;
    string getStatus() const;
    void setStatus(string s);
    
    // Pure virtual method - must be implemented by derived classes
    virtual double calculateBill() = 0;
    virtual void display() const = 0;
    virtual ~Service();
};

// Restaurant Service
class RestaurantService : public Service
{
private:
    string dishName;
    int quantity;
    double dishPrice;
    string mealType; // Breakfast, Lunch, Dinner, Snacks

public:
    RestaurantService();
    RestaurantService(string sID, string gID, string dish, int qty,
                      double price, string type, string date);
    
    string getDishName() const;
    int getQuantity() const;
    double getDishPrice() const;
    string getMealType() const;
    
    double calculateBill() override;
    void display() const override;
};

// Laundry Service
class LaundryService : public Service
{
private:
    int numberOfItems;
    string laundryType; // Regular, Dry Cleaning, Express
    double pricePerItem;

public:
    LaundryService();
    LaundryService(string sID, string gID, int items,
                   string type, double pricePerItem, string date);
    
    int getNumberOfItems() const;
    string getLaundryType() const;
    double getPricePerItem() const;
    
    double calculateBill() override;
    void display() const override;
};

// Spa Service
class SpaService : public Service
{
private:
    string treatmentType; // Massage, Facial, Full Body Spa
    int durationMinutes;
    double pricePerMinute;

public:
    SpaService();
    SpaService(string sID, string gID, string treatment,
               int duration, double pricePerMin, string date);
    
    string getTreatmentType() const;
    int getDurationMinutes() const;
    
    double calculateBill() override;
    void display() const override;
};

// Room Service
class RoomService : public Service
{
private:
    string itemDescription;
    int quantity;
    double itemCost;
    double deliveryCharge;

public:
    RoomService();
    RoomService(string sID, string gID, string item, int qty,
                double cost, string date);
    
    string getItemDescription() const;
    int getQuantity() const;
    
    double calculateBill() override;
    void display() const override;
};

#endif
