#include "Service.h"

// ========== Base Service Class Implementation ==========
Service::Service()
    : serviceID(""), guestID(""), baseCost(0.0), serviceDate(""), status("Pending")
{
}

Service::Service(string sID, string gID, double cost, string date)
    : serviceID(sID), guestID(gID), baseCost(cost), serviceDate(date), status("Pending")
{
}

string Service::getServiceID() const { return serviceID; }
string Service::getGuestID() const { return guestID; }
double Service::getBaseCost() const { return baseCost; }
string Service::getServiceDate() const { return serviceDate; }
string Service::getStatus() const { return status; }
void Service::setStatus(string s) { status = s; }

Service::~Service()
{
}

// ========== RestaurantService Implementation ==========
RestaurantService::RestaurantService()
    : Service(), dishName(""), quantity(0), dishPrice(0.0), mealType("")
{
}

RestaurantService::RestaurantService(string sID, string gID, string dish, int qty,
                                     double price, string type, string date)
    : Service(sID, gID, price * qty, date), dishName(dish), quantity(qty),
      dishPrice(price), mealType(type)
{
}

string RestaurantService::getDishName() const { return dishName; }
int RestaurantService::getQuantity() const { return quantity; }
double RestaurantService::getDishPrice() const { return dishPrice; }
string RestaurantService::getMealType() const { return mealType; }

double RestaurantService::calculateBill()
{
    double subtotal = dishPrice * quantity;
    double serviceCharge = subtotal * 0.10; // 10% service charge
    double gst = (subtotal + serviceCharge) * 0.17; // 17% GST
    return subtotal + serviceCharge + gst;
}

void RestaurantService::display() const
{
    cout << "\n===== Restaurant Service =====" << endl;
    cout << "Service ID: " << serviceID << endl;
    cout << "Guest ID: " << guestID << endl;
    cout << "Dish: " << dishName << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Price per Item: Rs. " << dishPrice << endl;
    cout << "Meal Type: " << mealType << endl;
    cout << "Date: " << serviceDate << endl;
    cout << "Status: " << status << endl;
    cout << "==============================" << endl;
}

// ========== LaundryService Implementation ==========
LaundryService::LaundryService()
    : Service(), numberOfItems(0), laundryType(""), pricePerItem(0.0)
{
}

LaundryService::LaundryService(string sID, string gID, int items,
                               string type, double pricePerItem, string date)
    : Service(sID, gID, items * pricePerItem, date), numberOfItems(items),
      laundryType(type), pricePerItem(pricePerItem)
{
}

int LaundryService::getNumberOfItems() const { return numberOfItems; }
string LaundryService::getLaundryType() const { return laundryType; }
double LaundryService::getPricePerItem() const { return pricePerItem; }

double LaundryService::calculateBill()
{
    double subtotal = numberOfItems * pricePerItem;
    // Extra charges based on laundry type
    double extraCharge = 0.0;
    if (laundryType == "Dry Cleaning")
        extraCharge = subtotal * 0.25; // 25% extra
    else if (laundryType == "Express")
        extraCharge = subtotal * 0.15; // 15% extra
    
    return subtotal + extraCharge;
}

void LaundryService::display() const
{
    cout << "\n===== Laundry Service =====" << endl;
    cout << "Service ID: " << serviceID << endl;
    cout << "Guest ID: " << guestID << endl;
    cout << "Number of Items: " << numberOfItems << endl;
    cout << "Laundry Type: " << laundryType << endl;
    cout << "Price per Item: Rs. " << pricePerItem << endl;
    cout << "Date: " << serviceDate << endl;
    cout << "Status: " << status << endl;
    cout << "==========================" << endl;
}

// ========== SpaService Implementation ==========
SpaService::SpaService()
    : Service(), treatmentType(""), durationMinutes(0), pricePerMinute(0.0)
{
}

SpaService::SpaService(string sID, string gID, string treatment,
                       int duration, double pricePerMin, string date)
    : Service(sID, gID, duration * pricePerMin, date), treatmentType(treatment),
      durationMinutes(duration), pricePerMinute(pricePerMin)
{
}

string SpaService::getTreatmentType() const { return treatmentType; }
int SpaService::getDurationMinutes() const { return durationMinutes; }

double SpaService::calculateBill()
{
    double treatmentCost = durationMinutes * pricePerMinute;
    double serviceCharge = treatmentCost * 0.15; // 15% service charge
    return treatmentCost + serviceCharge;
}

void SpaService::display() const
{
    cout << "\n===== Spa Service =====" << endl;
    cout << "Service ID: " << serviceID << endl;
    cout << "Guest ID: " << guestID << endl;
    cout << "Treatment Type: " << treatmentType << endl;
    cout << "Duration: " << durationMinutes << " minutes" << endl;
    cout << "Price per Minute: Rs. " << pricePerMinute << endl;
    cout << "Date: " << serviceDate << endl;
    cout << "Status: " << status << endl;
    cout << "=======================" << endl;
}

// ========== RoomService Implementation ==========
RoomService::RoomService()
    : Service(), itemDescription(""), quantity(0), itemCost(0.0), deliveryCharge(50.0)
{
}

RoomService::RoomService(string sID, string gID, string item, int qty,
                         double cost, string date)
    : Service(sID, gID, cost * qty + 50, date), itemDescription(item),
      quantity(qty), itemCost(cost), deliveryCharge(50.0)
{
}

string RoomService::getItemDescription() const { return itemDescription; }
int RoomService::getQuantity() const { return quantity; }

double RoomService::calculateBill()
{
    double subtotal = itemCost * quantity;
    double serviceCharge = subtotal * 0.10; // 10% service charge
    double gst = (subtotal + serviceCharge) * 0.17; // 17% GST
    return subtotal + serviceCharge + deliveryCharge + gst;
}

void RoomService::display() const
{
    cout << "\n===== Room Service =====" << endl;
    cout << "Service ID: " << serviceID << endl;
    cout << "Guest ID: " << guestID << endl;
    cout << "Item: " << itemDescription << endl;
    cout << "Quantity: " << quantity << endl;
    cout << "Item Cost: Rs. " << itemCost << endl;
    cout << "Delivery Charge: Rs. " << deliveryCharge << endl;
    cout << "Date: " << serviceDate << endl;
    cout << "Status: " << status << endl;
    cout << "=======================" << endl;
}
