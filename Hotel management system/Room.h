#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <iostream>

using namespace std;

class Room
{
protected:
    string roomID;
    string roomType;
    int floor;
    double basePrice;
    bool isOccupied;
    string currentGuest;
    int capacity;
    string amenities;

public:
    Room();
    Room(string id, string type, int fl, double price, int cap, string am);
    
    // Getters
    string getRoomID() const;
    string getRoomType() const;
    int getFloor() const;
    double getBasePrice() const;
    bool getIsOccupied() const;
    string getCurrentGuest() const;
    int getCapacity() const;
    string getAmenities() const;
    
    // Setters
    void setOccupied(bool occupied);
    void setCurrentGuest(string guest);
    
    // Virtual methods for polymorphism
    virtual double calculatePrice() const;
    virtual void display() const;
    virtual double getServiceCharge() const;
    virtual ~Room();
};

// Standard Room - simplest room type
class StandardRoom : public Room
{
private:
    bool hasTV;
    bool hasWiFi;

public:
    StandardRoom();
    StandardRoom(string id, int fl);
    
    double calculatePrice() const override;
    double getServiceCharge() const override;
    void display() const override;
};

// Deluxe Room - better amenities
class DeluxeRoom : public Room
{
private:
    int numberOfBeds;
    bool hasBalcony;
    bool hasJacuzzi;

public:
    DeluxeRoom();
    DeluxeRoom(string id, int fl);
    
    int getNumberOfBeds() const;
    bool getHasBalcony() const;
    bool getHasJacuzzi() const;
    
    double calculatePrice() const override;
    double getServiceCharge() const override;
    void display() const override;
};

// Executive Room - premium amenities
class ExecutiveRoom : public Room
{
private:
    bool hasKitchen;
    bool hasWorkArea;
    bool hasSafeLocker;

public:
    ExecutiveRoom();
    ExecutiveRoom(string id, int fl);
    
    double calculatePrice() const override;
    double getServiceCharge() const override;
    void display() const override;
};

// Suite Room - luxury option
class SuiteRoom : public Room
{
private:
    int numberOfRooms;
    bool hasPrivateSpa;
    bool hasDiningArea;
    bool hasButlerService;

public:
    SuiteRoom();
    SuiteRoom(string id, int fl);
    
    int getNumberOfRooms() const;
    bool getHasPrivateSpa() const;
    bool getHasDiningArea() const;
    
    double calculatePrice() const override;
    double getServiceCharge() const override;
    void display() const override;
};

#endif
