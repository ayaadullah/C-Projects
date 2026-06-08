#include "Room.h"

// ========== Base Room Class Implementation ==========
Room::Room()
    : roomID(""), roomType(""), floor(0), basePrice(0.0), isOccupied(false),
      currentGuest(""), capacity(0), amenities("")
{
}

Room::Room(string id, string type, int fl, double price, int cap, string am)
    : roomID(id), roomType(type), floor(fl), basePrice(price),
      isOccupied(false), currentGuest(""), capacity(cap), amenities(am)
{
}

string Room::getRoomID() const { return roomID; }
string Room::getRoomType() const { return roomType; }
int Room::getFloor() const { return floor; }
double Room::getBasePrice() const { return basePrice; }
bool Room::getIsOccupied() const { return isOccupied; }
string Room::getCurrentGuest() const { return currentGuest; }
int Room::getCapacity() const { return capacity; }
string Room::getAmenities() const { return amenities; }

void Room::setOccupied(bool occupied) { isOccupied = occupied; }
void Room::setCurrentGuest(string guest) { currentGuest = guest; }

double Room::calculatePrice() const { return basePrice; }

double Room::getServiceCharge() const { return basePrice * 0.10; } // 10%

void Room::display() const
{
    cout << "\n===== Room Information =====" << endl;
    cout << "Room ID: " << roomID << endl;
    cout << "Type: " << roomType << endl;
    cout << "Floor: " << floor << endl;
    cout << "Base Price: Rs. " << basePrice << endl;
    cout << "Capacity: " << capacity << " guests" << endl;
    cout << "Status: " << (isOccupied ? "Occupied" : "Available") << endl;
    cout << "Current Guest: " << (currentGuest.empty() ? "None" : currentGuest) << endl;
    cout << "Amenities: " << amenities << endl;
    cout << "Service Charge: Rs. " << getServiceCharge() << endl;
    cout << "=============================" << endl;
}

Room::~Room()
{
}

// ========== StandardRoom Implementation ==========
StandardRoom::StandardRoom()
    : Room("STD000", "Standard", 1, 3000, 1, "TV, WiFi"), hasTV(true), hasWiFi(true)
{
}

StandardRoom::StandardRoom(string id, int fl)
    : Room(id, "Standard", fl, 3000, 1, "TV, WiFi"), hasTV(true), hasWiFi(true)
{
}

double StandardRoom::calculatePrice() const
{
    return basePrice; // Base price as is
}

double StandardRoom::getServiceCharge() const
{
    return basePrice * 0.10; // 10% service charge
}

void StandardRoom::display() const
{
    cout << "\n===== Standard Room Information =====" << endl;
    cout << "Room ID: " << roomID << endl;
    cout << "Floor: " << floor << endl;
    cout << "Price per Night: Rs. " << basePrice << endl;
    cout << "Capacity: " << capacity << " guest" << endl;
    cout << "TV: " << (hasTV ? "Yes" : "No") << endl;
    cout << "WiFi: " << (hasWiFi ? "Yes" : "No") << endl;
    cout << "Status: " << (isOccupied ? "Occupied" : "Available") << endl;
    cout << "====================================" << endl;
}

// ========== DeluxeRoom Implementation ==========
DeluxeRoom::DeluxeRoom()
    : Room("DLX000", "Deluxe", 2, 5000, 2, "AC, TV, WiFi, Balcony, Jacuzzi"),
      numberOfBeds(2), hasBalcony(true), hasJacuzzi(true)
{
}

DeluxeRoom::DeluxeRoom(string id, int fl)
    : Room(id, "Deluxe", fl, 5000, 2, "AC, TV, WiFi, Balcony, Jacuzzi"),
      numberOfBeds(2), hasBalcony(true), hasJacuzzi(true)
{
}

int DeluxeRoom::getNumberOfBeds() const { return numberOfBeds; }
bool DeluxeRoom::getHasBalcony() const { return hasBalcony; }
bool DeluxeRoom::getHasJacuzzi() const { return hasJacuzzi; }

double DeluxeRoom::calculatePrice() const
{
    return basePrice; // Base price for deluxe
}

double DeluxeRoom::getServiceCharge() const
{
    return basePrice * 0.12; // 12% service charge
}

void DeluxeRoom::display() const
{
    cout << "\n===== Deluxe Room Information =====" << endl;
    cout << "Room ID: " << roomID << endl;
    cout << "Floor: " << floor << endl;
    cout << "Price per Night: Rs. " << basePrice << endl;
    cout << "Capacity: " << capacity << " guests" << endl;
    cout << "Number of Beds: " << numberOfBeds << endl;
    cout << "Balcony: " << (hasBalcony ? "Yes" : "No") << endl;
    cout << "Jacuzzi: " << (hasJacuzzi ? "Yes" : "No") << endl;
    cout << "Status: " << (isOccupied ? "Occupied" : "Available") << endl;
    cout << "===================================" << endl;
}

// ========== ExecutiveRoom Implementation ==========
ExecutiveRoom::ExecutiveRoom()
    : Room("EXE000", "Executive", 3, 7500, 2, "AC, Kitchen, WiFi, Locker, Work Area"),
      hasKitchen(true), hasWorkArea(true), hasSafeLocker(true)
{
}

ExecutiveRoom::ExecutiveRoom(string id, int fl)
    : Room(id, "Executive", fl, 7500, 2, "AC, Kitchen, WiFi, Locker, Work Area"),
      hasKitchen(true), hasWorkArea(true), hasSafeLocker(true)
{
}

double ExecutiveRoom::calculatePrice() const
{
    return basePrice; // Base price
}

double ExecutiveRoom::getServiceCharge() const
{
    return basePrice * 0.15; // 15% service charge
}

void ExecutiveRoom::display() const
{
    cout << "\n===== Executive Room Information =====" << endl;
    cout << "Room ID: " << roomID << endl;
    cout << "Floor: " << floor << endl;
    cout << "Price per Night: Rs. " << basePrice << endl;
    cout << "Capacity: " << capacity << " guests" << endl;
    cout << "Kitchen: " << (hasKitchen ? "Yes" : "No") << endl;
    cout << "Work Area: " << (hasWorkArea ? "Yes" : "No") << endl;
    cout << "Safe Locker: " << (hasSafeLocker ? "Yes" : "No") << endl;
    cout << "Status: " << (isOccupied ? "Occupied" : "Available") << endl;
    cout << "=====================================" << endl;
}

// ========== SuiteRoom Implementation ==========
SuiteRoom::SuiteRoom()
    : Room("SUI000", "Suite", 4, 15000, 4, "Luxury, Private Spa, Dining Area"),
      numberOfRooms(3), hasPrivateSpa(true), hasDiningArea(true), hasButlerService(true)
{
}

SuiteRoom::SuiteRoom(string id, int fl)
    : Room(id, "Suite", fl, 15000, 4, "Luxury, Private Spa, Dining Area"),
      numberOfRooms(3), hasPrivateSpa(true), hasDiningArea(true), hasButlerService(true)
{
}

int SuiteRoom::getNumberOfRooms() const { return numberOfRooms; }
bool SuiteRoom::getHasPrivateSpa() const { return hasPrivateSpa; }
bool SuiteRoom::getHasDiningArea() const { return hasDiningArea; }

double SuiteRoom::calculatePrice() const
{
    return basePrice; // Base price for suite
}

double SuiteRoom::getServiceCharge() const
{
    return basePrice * 0.20; // 20% service charge
}

void SuiteRoom::display() const
{
    cout << "\n===== Suite Room Information =====" << endl;
    cout << "Room ID: " << roomID << endl;
    cout << "Floor: " << floor << endl;
    cout << "Price per Night: Rs. " << basePrice << endl;
    cout << "Capacity: " << capacity << " guests" << endl;
    cout << "Number of Rooms: " << numberOfRooms << endl;
    cout << "Private Spa: " << (hasPrivateSpa ? "Yes" : "No") << endl;
    cout << "Dining Area: " << (hasDiningArea ? "Yes" : "No") << endl;
    cout << "Butler Service: " << (hasButlerService ? "Yes" : "No") << endl;
    cout << "Status: " << (isOccupied ? "Occupied" : "Available") << endl;
    cout << "==================================" << endl;
}
