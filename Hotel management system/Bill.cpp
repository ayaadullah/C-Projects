#include "Bill.h"
#include <ctime>

Bill::Bill()
    : billID(""), guestID(""), bookingID(""), roomCharges(0.0),
      serviceCharges(0.0), restaurantCharges(0.0), laundryCharges(0.0),
      spaCharges(0.0), otherCharges(0.0), discountPercentage(0.0),
      taxPercentage(17.0), totalAmount(0.0), status("Pending"), paymentMethod("")
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    generatedDate = string(buffer);
}

Bill::Bill(string bID, string gID, string bookID)
    : billID(bID), guestID(gID), bookingID(bookID), roomCharges(0.0),
      serviceCharges(0.0), restaurantCharges(0.0), laundryCharges(0.0),
      spaCharges(0.0), otherCharges(0.0), discountPercentage(0.0),
      taxPercentage(17.0), totalAmount(0.0), status("Pending"), paymentMethod("")
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    generatedDate = string(buffer);
}

// Getters
string Bill::getBillID() const { return billID; }
string Bill::getGuestID() const { return guestID; }
string Bill::getBookingID() const { return bookingID; }
double Bill::getRoomCharges() const { return roomCharges; }
double Bill::getServiceCharges() const { return serviceCharges; }
double Bill::getRestaurantCharges() const { return restaurantCharges; }
double Bill::getLaundryCharges() const { return laundryCharges; }
double Bill::getSpaCharges() const { return spaCharges; }
double Bill::getOtherCharges() const { return otherCharges; }
double Bill::getDiscountPercentage() const { return discountPercentage; }
double Bill::getTaxPercentage() const { return taxPercentage; }
double Bill::getTotalAmount() const { return totalAmount; }
string Bill::getGeneratedDate() const { return generatedDate; }
string Bill::getStatus() const { return status; }
string Bill::getPaymentMethod() const { return paymentMethod; }

// Setters
void Bill::setRoomCharges(double charges) { roomCharges = charges; }
void Bill::setServiceCharges(double charges) { serviceCharges = charges; }
void Bill::setRestaurantCharges(double charges) { restaurantCharges = charges; }
void Bill::setLaundryCharges(double charges) { laundryCharges = charges; }
void Bill::setSpaCharges(double charges) { spaCharges = charges; }
void Bill::setOtherCharges(double charges) { otherCharges = charges; }
void Bill::setDiscountPercentage(double discount) { discountPercentage = discount; }
void Bill::setTaxPercentage(double tax) { taxPercentage = tax; }
void Bill::setStatus(string s) { status = s; }
void Bill::setPaymentMethod(string method) { paymentMethod = method; }

double Bill::calculateSubtotal() const
{
    return roomCharges + serviceCharges + restaurantCharges +
           laundryCharges + spaCharges + otherCharges;
}

double Bill::calculateDiscount() const
{
    return calculateSubtotal() * (discountPercentage / 100.0);
}

double Bill::calculateTax() const
{
    double afterDiscount = calculateSubtotal() - calculateDiscount();
    return afterDiscount * (taxPercentage / 100.0);
}

void Bill::calculateTotal()
{
    double subtotal = calculateSubtotal();
    double discount = calculateDiscount();
    double tax = calculateTax();
    totalAmount = subtotal - discount + tax;
}

void Bill::generateBill()
{
    calculateTotal();
    status = "Generated";
}

void Bill::display() const
{
    cout << "\n========== BILL INVOICE ==========" << endl;
    cout << "Bill ID: " << billID << endl;
    cout << "Guest ID: " << guestID << endl;
    cout << "Booking ID: " << bookingID << endl;
    cout << "Generated Date: " << generatedDate << endl;
    cout << "\n----- Charges Breakdown -----" << endl;
    cout << "Room Charges: Rs. " << roomCharges << endl;
    cout << "Service Charges: Rs. " << serviceCharges << endl;
    cout << "Restaurant Charges: Rs. " << restaurantCharges << endl;
    cout << "Laundry Charges: Rs. " << laundryCharges << endl;
    cout << "Spa Charges: Rs. " << spaCharges << endl;
    cout << "Other Charges: Rs. " << otherCharges << endl;
    cout << "----------------------------" << endl;
    cout << "Subtotal: Rs. " << calculateSubtotal() << endl;
    cout << "Discount (" << discountPercentage << "%): Rs. -" << calculateDiscount() << endl;
    cout << "Tax (" << taxPercentage << "%): Rs. " << calculateTax() << endl;
    cout << "----------------------------" << endl;
    cout << "TOTAL AMOUNT DUE: Rs. " << totalAmount << endl;
    cout << "----------------------------" << endl;
    cout << "Status: " << status << endl;
    if (!paymentMethod.empty())
        cout << "Payment Method: " << paymentMethod << endl;
    cout << "=================================" << endl;
}

// Operator Overloading
bool Bill::operator==(const Bill& other) const
{
    return billID == other.billID;
}

bool Bill::operator>(const Bill& other) const
{
    return totalAmount > other.totalAmount;
}

bool Bill::operator<(const Bill& other) const
{
    return totalAmount < other.totalAmount;
}

Bill Bill::operator+(double amount) const
{
    Bill temp = *this;
    temp.otherCharges += amount;
    temp.calculateTotal();
    return temp;
}

Bill Bill::operator-(double amount) const
{
    Bill temp = *this;
    temp.discountPercentage += (amount / calculateSubtotal()) * 100;
    if (temp.discountPercentage > 100)
        temp.discountPercentage = 100;
    temp.calculateTotal();
    return temp;
}

Bill& Bill::operator+=(double amount)
{
    otherCharges += amount;
    calculateTotal();
    return *this;
}

Bill& Bill::operator-=(double amount)
{
    discountPercentage += (amount / calculateSubtotal()) * 100;
    if (discountPercentage > 100)
        discountPercentage = 100;
    calculateTotal();
    return *this;
}

// Friend function implementation
void printBillDetails(const Bill& bill)
{
    cout << "\n===== CONFIDENTIAL BILL DETAILS =====" << endl;
    cout << "Bill ID: " << bill.billID << endl;
    cout << "Guest ID: " << bill.guestID << endl;
    cout << "Room Charges: Rs. " << bill.roomCharges << endl;
    cout << "Service Charges: Rs. " << bill.serviceCharges << endl;
    cout << "Subtotal: Rs. " << bill.calculateSubtotal() << endl;
    cout << "Discount: Rs. " << bill.calculateDiscount() << endl;
    cout << "Tax: Rs. " << bill.calculateTax() << endl;
    cout << "Total: Rs. " << bill.totalAmount << endl;
    cout << "======================================" << endl;
}

double calculateGuestDiscount(const Bill& bill, double loyaltyPoints)
{
    double discount = bill.calculateSubtotal() * (loyaltyPoints * 0.0001);
    return (discount > bill.calculateSubtotal() * 0.1) ? bill.calculateSubtotal() * 0.1 : discount;
}
