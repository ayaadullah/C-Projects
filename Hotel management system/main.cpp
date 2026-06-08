#include <iostream>
#include <string>
#include "Hotel.h"

using namespace std;

void displayMainMenu();
void guestManagementMenu(Hotel& hotel);
void roomManagementMenu(Hotel& hotel);
void bookingManagementMenu(Hotel& hotel);
void employeeManagementMenu(Hotel& hotel);
void billManagementMenu(Hotel& hotel);
void serviceManagementMenu(Hotel& hotel);
void runDemo(Hotel& hotel);

int main()
{
    Hotel hotel("Northern Heights Hotel & Resort",
                "123 Main Street, Islamabad",
                "+92-51-1234567", 20, 5);
    
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║   SMART HOTEL MANAGEMENT SYSTEM        ║" << endl;
    cout << "║   Northern Heights Hotel & Resort      ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMainMenu();
        cout << "Enter your choice (1-8): ";
        cin >> choice;
        cin.ignore(); // Clear input buffer
        
        switch (choice) {
            case 1:
                guestManagementMenu(hotel);
                break;
            case 2:
                roomManagementMenu(hotel);
                break;
            case 3:
                bookingManagementMenu(hotel);
                break;
            case 4:
                employeeManagementMenu(hotel);
                break;
            case 5:
                billManagementMenu(hotel);
                break;
            case 6:
                serviceManagementMenu(hotel);
                break;
            case 7:
                runDemo(hotel);
                break;
            case 8:
                cout << "\nThank you for using Hotel Management System!" << endl;
                hotel.saveGuestData();
                hotel.saveBookingData();
                hotel.saveBillData();
                running = false;
                break;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}

void displayMainMenu()
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║         MAIN MENU                      ║" << endl;
    cout << "╠════════════════════════════════════════╣" << endl;
    cout << "║ 1. Guest Management                    ║" << endl;
    cout << "║ 2. Room Management                     ║" << endl;
    cout << "║ 3. Booking Management                  ║" << endl;
    cout << "║ 4. Employee Management                 ║" << endl;
    cout << "║ 5. Bill Management                     ║" << endl;
    cout << "║ 6. Service Management                  ║" << endl;
    cout << "║ 7. Run Demo                            ║" << endl;
    cout << "║ 8. Exit                                ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
}

void guestManagementMenu(Hotel& hotel)
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║    GUEST MANAGEMENT MENU               ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    int choice;
    cout << "1. Register New Guest\n2. Display All Guests\n3. Find Guest\n4. Back\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        string id, name, email, phone, address, nationality, docID;
        cout << "\nEnter Guest ID: ";
        getline(cin, id);
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Nationality: ";
        getline(cin, nationality);
        cout << "Enter Document ID: ";
        getline(cin, docID);
        
        Guest newGuest(id, name, email, phone, address, nationality, docID);
        hotel.addGuest(newGuest);
        cout << "\n✓ Guest registered successfully!" << endl;
    }
    else if (choice == 2) {
        hotel.displayAllGuests();
    }
    else if (choice == 3) {
        string guestID;
        cout << "Enter Guest ID: ";
        getline(cin, guestID);
        const Guest* guest = hotel.findGuestByID(guestID);
        if (guest) {
            guest->display();
        }
        else {
            cout << "\n✗ Guest not found!" << endl;
        }
    }
}

void roomManagementMenu(Hotel& hotel)
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║      ROOM MANAGEMENT MENU              ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    int choice;
    cout << "1. Display All Rooms\n2. Display Available Rooms\n3. Display Rooms by Type\n4. Back\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        hotel.displayAllRooms();
    }
    else if (choice == 2) {
        cout << "\n========== Available Rooms ==========" << endl;
        vector<Room*> available = hotel.getAvailableRooms();
        cout << "Total Available: " << available.size() << endl;
        for (auto room : available) {
            cout << room->getRoomID() << " - " << room->getRoomType()
                 << " - Floor " << room->getFloor()
                 << " - Rs. " << room->getBasePrice() << endl;
        }
        cout << "====================================" << endl;
    }
    else if (choice == 3) {
        string type;
        cout << "Enter Room Type (Standard/Deluxe/Executive/Suite): ";
        getline(cin, type);
        vector<Room*> result = hotel.getRoomsByType(type);
        cout << "\nRooms of type " << type << ":" << endl;
        for (auto room : result) {
            cout << room->getRoomID() << " - Floor " << room->getFloor()
                 << " - Rs. " << room->getBasePrice() << endl;
        }
    }
}

void bookingManagementMenu(Hotel& hotel)
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║    BOOKING MANAGEMENT MENU             ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    int choice;
    cout << "1. Create Booking\n2. Display All Bookings\n3. Check-In\n4. Check-Out\n5. Cancel Booking\n6. Back\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        string bookingID, guestID, roomID, checkIn, checkOut;
        double price;
        cout << "Enter Booking ID: ";
        getline(cin, bookingID);
        cout << "Enter Guest ID: ";
        getline(cin, guestID);
        cout << "Enter Room ID: ";
        getline(cin, roomID);
        cout << "Enter Check-In Date (YYYY-MM-DD): ";
        getline(cin, checkIn);
        cout << "Enter Check-Out Date (YYYY-MM-DD): ";
        getline(cin, checkOut);
        cout << "Enter Price per Night: ";
        cin >> price;
        
        Booking booking(bookingID, guestID, roomID, checkIn, checkOut, price);
        hotel.createBooking(booking);
    }
    else if (choice == 2) {
        hotel.displayAllBookings();
    }
    else if (choice == 3) {
        string bookingID;
        cout << "Enter Booking ID for Check-In: ";
        getline(cin, bookingID);
        hotel.checkInGuest(bookingID);
    }
    else if (choice == 4) {
        string bookingID;
        cout << "Enter Booking ID for Check-Out: ";
        getline(cin, bookingID);
        hotel.checkOutGuest(bookingID);
    }
    else if (choice == 5) {
        string bookingID;
        cout << "Enter Booking ID to Cancel: ";
        getline(cin, bookingID);
        hotel.cancelBooking(bookingID);
    }
}

void employeeManagementMenu(Hotel& hotel)
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║   EMPLOYEE MANAGEMENT MENU             ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    int choice;
    cout << "1. Hire Employee\n2. Display All Employees\n3. Calculate Payroll\n4. Back\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        int empType;
        cout << "Employee Type: 1-Receptionist, 2-Manager, 3-HouseKeeping: ";
        cin >> empType;
        cin.ignore();
        
        string id, name, email, phone, address, empID, joinDate;
        cout << "Enter Person ID: ";
        getline(cin, id);
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Employee ID: ";
        getline(cin, empID);
        cout << "Enter Join Date: ";
        getline(cin, joinDate);
        
        double salary;
        cout << "Enter Salary: ";
        cin >> salary;
        cin.ignore();
        
        if (empType == 1) {
            Receptionist* rec = new Receptionist(id, name, email, phone, address, empID, salary, joinDate);
            hotel.hireEmployee(rec);
        }
        else if (empType == 2) {
            string managerType;
            cout << "Enter Manager Type: ";
            getline(cin, managerType);
            Manager* mgr = new Manager(id, name, email, phone, address, empID, salary, joinDate, managerType);
            hotel.hireEmployee(mgr);
        }
        else if (empType == 3) {
            string shift;
            cout << "Enter Shift (Morning/Afternoon/Night): ";
            getline(cin, shift);
            HouseKeeping* hk = new HouseKeeping(id, name, email, phone, address, empID, salary, joinDate, shift);
            hotel.hireEmployee(hk);
        }
    }
    else if (choice == 2) {
        hotel.displayAllEmployees();
    }
    else if (choice == 3) {
        cout << "\nTotal Payroll: Rs. " << hotel.calculatePayrollTotal() << endl;
    }
}

void billManagementMenu(Hotel& hotel)
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║      BILL MANAGEMENT MENU              ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    int choice;
    cout << "1. Generate Bill\n2. Display All Bills\n3. Revenue Report\n4. Back\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        string billID, guestID, bookingID;
        cout << "Enter Bill ID: ";
        getline(cin, billID);
        cout << "Enter Guest ID: ";
        getline(cin, guestID);
        cout << "Enter Booking ID: ";
        getline(cin, bookingID);
        
        Bill bill(billID, guestID, bookingID);
        
        double roomCharges, restaurantCharges, laundryCharges, spaCharges;
        cout << "Enter Room Charges: ";
        cin >> roomCharges;
        cout << "Enter Restaurant Charges: ";
        cin >> restaurantCharges;
        cout << "Enter Laundry Charges: ";
        cin >> laundryCharges;
        cout << "Enter Spa Charges: ";
        cin >> spaCharges;
        cout << "Enter Discount %: ";
        double discount;
        cin >> discount;
        
        bill.setRoomCharges(roomCharges);
        bill.setRestaurantCharges(restaurantCharges);
        bill.setLaundryCharges(laundryCharges);
        bill.setSpaCharges(spaCharges);
        bill.setDiscountPercentage(discount);
        
        hotel.generateBill(bill);
        bill.display();
    }
    else if (choice == 2) {
        hotel.displayAllBills();
    }
    else if (choice == 3) {
        hotel.generateRevenueReport();
    }
}

void serviceManagementMenu(Hotel& hotel)
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║    SERVICE MANAGEMENT MENU             ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    int choice;
    cout << "1. Add Restaurant Service\n2. Add Laundry Service\n3. Add Spa Service\n4. Display All Services\n5. Back\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    if (choice == 1) {
        string sID, gID, dish, type, date;
        int qty;
        double price;
        cout << "Enter Service ID: ";
        getline(cin, sID);
        cout << "Enter Guest ID: ";
        getline(cin, gID);
        cout << "Enter Dish Name: ";
        getline(cin, dish);
        cout << "Enter Quantity: ";
        cin >> qty;
        cout << "Enter Price per Item: ";
        cin >> price;
        cin.ignore();
        cout << "Enter Meal Type: ";
        getline(cin, type);
        cout << "Enter Date: ";
        getline(cin, date);
        
        RestaurantService* service = new RestaurantService(sID, gID, dish, qty, price, type, date);
        hotel.addService(service);
    }
    else if (choice == 2) {
        string sID, gID, laundryType, date;
        int items;
        double pricePerItem;
        cout << "Enter Service ID: ";
        getline(cin, sID);
        cout << "Enter Guest ID: ";
        getline(cin, gID);
        cout << "Enter Number of Items: ";
        cin >> items;
        cin.ignore();
        cout << "Enter Laundry Type (Regular/Dry Cleaning/Express): ";
        getline(cin, laundryType);
        cout << "Enter Price per Item: ";
        cin >> pricePerItem;
        cin.ignore();
        cout << "Enter Date: ";
        getline(cin, date);
        
        LaundryService* service = new LaundryService(sID, gID, items, laundryType, pricePerItem, date);
        hotel.addService(service);
    }
    else if (choice == 3) {
        string sID, gID, treatmentType, date;
        int duration;
        double pricePerMin;
        cout << "Enter Service ID: ";
        getline(cin, sID);
        cout << "Enter Guest ID: ";
        getline(cin, gID);
        cout << "Enter Treatment Type (Massage/Facial/Full Body Spa): ";
        getline(cin, treatmentType);
        cout << "Enter Duration (minutes): ";
        cin >> duration;
        cout << "Enter Price per Minute: ";
        cin >> pricePerMin;
        cin.ignore();
        cout << "Enter Date: ";
        getline(cin, date);
        
        SpaService* service = new SpaService(sID, gID, treatmentType, duration, pricePerMin, date);
        hotel.addService(service);
    }
    else if (choice == 4) {
        hotel.displayAllServices();
    }
}

void runDemo(Hotel& hotel)
{
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║         RUNNING DEMO                   ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    
    // Add demo guests
    cout << "\n[1] Adding Demo Guests..." << endl;
    Guest guest1("G001", "Ahmed Khan", "ahmed@email.com", "03001234567", "Islamabad", "Pakistan", "PK123456");
    guest1.addLoyaltyPoints(500);
    hotel.addGuest(guest1);
    
    Guest guest2("G002", "Fatima Ali", "fatima@email.com", "03009876543", "Lahore", "Pakistan", "PK654321");
    hotel.addGuest(guest2);
    
    cout << "✓ Added 2 guests" << endl;
    
    // Add demo employees
    cout << "\n[2] Adding Demo Employees..." << endl;
    Receptionist* rec = new Receptionist("P001", "Hassan Ahmed", "hassan@hotel.com", "051-1111111", "Islamabad", "E001", 30000, "2023-01-15");
    rec->incrementCheckIn();
    rec->incrementCheckOut();
    hotel.hireEmployee(rec);
    
    Manager* manager = new Manager("P002", "Saira Khan", "saira@hotel.com", "051-2222222", "Islamabad", "E002", 50000, "2022-06-10", "Front Desk Manager");
    manager->setStaffManaged(5);
    hotel.hireEmployee(manager);
    
    HouseKeeping* hk = new HouseKeeping("P003", "Muhammad Ali", "ali@hotel.com", "051-3333333", "Islamabad", "E003", 25000, "2023-03-20", "Morning");
    hk->incrementRoomsCleaned();
    hk->incrementRoomsCleaned();
    hk->incrementRoomsCleaned();
    hotel.hireEmployee(hk);
    
    cout << "✓ Added 3 employees" << endl;
    
    // Create demo bookings
    cout << "\n[3] Creating Demo Bookings..." << endl;
    Booking booking1("BK001", "G001", "STD1", "2024-06-08", "2024-06-10", 3000);
    hotel.createBooking(booking1);
    
    Booking booking2("BK002", "G002", "DLX1", "2024-06-08", "2024-06-12", 5000);
    hotel.createBooking(booking2);
    
    cout << "✓ Created 2 bookings" << endl;
    
    // Check-In guests
    cout << "\n[4] Checking In Guests..." << endl;
    hotel.checkInGuest("BK001");
    hotel.checkInGuest("BK002");
    cout << "✓ Guests checked in" << endl;
    
    // Add services
    cout << "\n[5] Adding Services..." << endl;
    RestaurantService* restService = new RestaurantService("S001", "G001", "Grilled Chicken", 2, 500, "Dinner", "2024-06-08");
    hotel.addService(restService);
    
    LaundryService* laundryService = new LaundryService("S002", "G001", 5, "Regular", 50, "2024-06-08");
    hotel.addService(laundryService);
    
    SpaService* spaService = new SpaService("S003", "G002", "Full Body Spa", 60, 100, "2024-06-08");
    hotel.addService(spaService);
    
    cout << "✓ Added 3 services" << endl;
    
    // Generate bills
    cout << "\n[6] Generating Bills..." << endl;
    Bill bill1("BILL001", "G001", "BK001");
    bill1.setRoomCharges(6000);  // 2 nights
    bill1.setServiceCharges(600);
    bill1.setRestaurantCharges(1000);
    bill1.setLaundryCharges(250);
    bill1.setDiscountPercentage(10);
    bill1.setPaymentMethod("Credit Card");
    bill1.setStatus("Paid");
    hotel.generateBill(bill1);
    
    Bill bill2("BILL002", "G002", "BK002");
    bill2.setRoomCharges(20000);  // 4 nights
    bill2.setServiceCharges(1200);
    bill2.setSpaCharges(6000);
    bill2.setDiscountPercentage(5);
    bill2.setPaymentMethod("Debit Card");
    bill2.setStatus("Paid");
    hotel.generateBill(bill2);
    
    cout << "✓ Generated 2 bills" << endl;
    
    // Display Reports
    cout << "\n[7] Generating Reports..." << endl;
    hotel.displayHotelInfo();
    hotel.displayDashboard();
    hotel.generateOccupancyReport();
    hotel.generateRevenueReport();
    hotel.generateGuestReport();
    
    cout << "\n✓ Demo completed successfully!" << endl;
    
    // Display specific information
    cout << "\n[8] Demo Guest Details:" << endl;
    guest1.display();
    
    cout << "\n[9] Demo Bill Details:" << endl;
    bill1.display();
    
    cout << "\n[10] All Services:" << endl;
    hotel.displayAllServices();
}
