#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

// ================= PRODUCT CLASS =================

class Product 
{
private:
    int id;
    string name;
    double price;
    int quantity;

public:
    Product() { 
        id = 0; 
        price = 0; 
        quantity = 0; 
    }

    Product(int i, string n, double p, int q) {
        id = i; 
        name = n; 
        price = p; 
        quantity = q;
    }

    int getID() { return id; }
    string getName() { return name; }
    double getPrice() { return price; }
    int getQuantity() { return quantity; }

    void setQuantity(int q) { quantity = q; }
    void setPrice(double p) { price = p; }

    friend ostream& operator<<(ostream &out, Product &p) {
        out << "ID: " << p.id << endl;
        out << "Name: " << p.name << endl;
        out << "Price: " << p.price << endl;
        out << "Quantity: " << p.quantity << endl;
        return out;
    }

    string toFile() {
        stringstream ss;
        ss << id << "|" << name << "|" << price << "|" << quantity;
        return ss.str();
    }
};

// ================= USER CLASSES =================

class User 
{
protected:
    string username;
    string password;

public:
    User(string u, string p) {
        username = u;
        password = p;
    }

    virtual void menu() = 0;
};

class Admin : public User 
{
public:
    Admin(string u, string p) : User(u, p) {}

    void menu() override {
        cout << "\nLogged in as Admin\n";
    }
};

class Customer : public User 
{
public:
    Customer(string u, string p) : User(u, p) {}

    void menu() override {
        cout << "\nLogged in as User\n";
    }
};

// Global Vector to hold products
vector<Product> products;

// ================= FILE FUNCTIONS =================

void saveProducts() 
{
    ofstream file("products.txt");
    for (int i = 0; i < (int)products.size(); i++) {
        file << products[i].toFile() << endl;
    }
    file.close();
}

void loadProducts() 
{
    products.clear();
    ifstream file("products.txt");
    if (!file) return;

    string line;
    while (getline(file, line)) {
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);

        int id = atoi(line.substr(0, p1).c_str());
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        double price = atof(line.substr(p2 + 1, p3 - p2 - 1).c_str());
        int qty = atoi(line.substr(p3 + 1).c_str());

        products.push_back(Product(id, name, price, qty));
    }
    file.close();
}

// ================= INVENTORY FUNCTIONS =================

void addProduct() 
{
    int id, qty;
    double price;
    string name;

    cout << "\nEnter Product ID: ";
    cin >> id;
    cin.ignore();

    cout << "Enter Product Name: ";
    getline(cin, name);

    cout << "Enter Price: ";
    cin >> price;

    cout << "Enter Quantity: ";
    cin >> qty;

    products.push_back(Product(id, name, price, qty));
    saveProducts();

    cout << "\nProduct Added Successfully.\n";
}

void viewProducts() 
{
    if (products.size() == 0) {
        cout << "\nInventory Empty.\n";
        return;
    }

    cout << "\n========== INVENTORY ==========\n";
    for (int i = 0; i < (int)products.size(); i++) {
        cout << "\n-----------------------------\n";
        cout << products[i];

        if (products[i].getQuantity() < 5) {
            cout << "LOW STOCK ALERT!\n";
        }
    }
}

void searchProduct() 
{
    int id;
    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < (int)products.size(); i++) {
        if (products[i].getID() == id) {
            cout << "\nProduct Found\n";
            cout << products[i];
            return;
        }
    }
    cout << "\nProduct Not Found.\n";
}

void updateProduct() 
{
    int id;
    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < (int)products.size(); i++) {
        if (products[i].getID() == id) {
            int qty;
            double price;

            cout << "New Price: ";
            cin >> price;
            cout << "New Quantity: ";
            cin >> qty;

            products[i].setPrice(price);
            products[i].setQuantity(qty);
            saveProducts();

            cout << "\nProduct Updated.\n";
            return;
        }
    }
    cout << "\nProduct Not Found.\n";
}

void deleteProduct() 
{
    int id;
    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < (int)products.size(); i++) {
        if (products[i].getID() == id) {
            products.erase(products.begin() + i);
            saveProducts();
            cout << "\nProduct Deleted.\n";
            return;
        }
    }
    cout << "\nProduct Not Found.\n";
}

void recordSale() 
{
    int id, qty;
    cout << "\nEnter Product ID: ";
    cin >> id;

    for (int i = 0; i < (int)products.size(); i++) {
        if (products[i].getID() == id) {
            cout << "Enter Quantity Sold: ";
            cin >> qty;

            if (qty > products[i].getQuantity()) {
                cout << "\nInsufficient Stock.\n";
                return;
            }

            double total = qty * products[i].getPrice();
            products[i].setQuantity(products[i].getQuantity() - qty);
            saveProducts();

            ofstream sale("sales.txt", ios::app);
            sale << "Product ID: " << products[i].getID()
                 << " | Name: " << products[i].getName()
                 << " | Qty: " << qty
                 << " | Total: " << total << endl;
            sale.close();

            cout << "\nSale Successful.\n";
            cout << "Total Bill: " << total << endl;
            return;
        }
    }
    cout << "\nProduct Not Found.\n";
}

void salesHistory() 
{
    ifstream file("sales.txt");
    if (!file) {
        cout << "\nNo Sales Found.\n";
        return;
    }

    string line;
    cout << "\n========== SALES HISTORY ==========\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// ================= LOGIN FUNCTIONS =================

bool loginAdmin() 
{
    string u, p;
    cout << "\nAdmin Username: ";
    cin >> u;
    cout << "Admin Password: ";
    cin >> p;
    return (u == "ayaad.ullah" && p == "ayaad123");
}

bool loginUser() 
{
    string u, p;
    cout << "\nUser Username: ";
    cin >> u;
    cout << "User Password: ";
    cin >> p;
    return (u == "azhan.khan" && p == "azhan123");
}

// ================= PANELS =================

void adminPanel() 
{
    int choice;
    do {
        cout << "\n====================================";
        cout << "\n INVENTORY MANAGEMENT SYSTEM OF TECHNOVA ELECTRONICS";
        cout << "\n====================================";
        cout << "\n1. Add Product";
        cout << "\n2. View Products";
        cout << "\n3. Search Product";
        cout << "\n4. Update Product";
        cout << "\n5. Delete Product";
        cout << "\n6. Record Sale";
        cout << "\n7. Sales History";
        cout << "\n8. Save Data";
        cout << "\n9. Logout";
        cout << "\n====================================";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: recordSale(); break;
            case 7: salesHistory(); break;
            case 8: saveProducts(); cout << "\nSaved.\n"; break;
            case 9: cout << "\nLogging Out...\n"; break;
            default: cout << "\nInvalid Choice.\n";
        }
    } while (choice != 9);
}

void userPanel() 
{
    int choice;
    do {
        cout << "\n====================================";
        cout << "\n USER PANEL";
        cout << "\n====================================";
        cout << "\n1. View Products";
        cout << "\n2. Search Product";
        cout << "\n3. Sales History";
        cout << "\n4. Logout";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: searchProduct(); break;
            case 3: salesHistory(); break;
            case 4: break;
            default: cout << "\nInvalid Choice";
        }
    } while (choice != 4);
}

// ================= MAIN FUNCTION =================

int main() 
{
    loadProducts();
    int choice;

    do {
        cout << "\n====================================";
        cout << "\n INVENTORY MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Admin Login";
        cout << "\n2. User Login";
        cout << "\n3. Exit";
        cout << "\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (loginAdmin()) {
                    Admin a("ayaad.ullah", "ayaad123");
                    a.menu();
                    adminPanel();
                } else {
                    cout << "\nInvalid Credentials.\n";
                }
                break;

            case 2:
                if (loginUser()) {
                    Customer c("azhan.khan", "azhan123");
                    c.menu();
                    userPanel();
                } else {
                    cout << "\nInvalid Credentials.\n";
                }
                break;

            case 3:
                saveProducts();
                cout << "\nThank You.\n";
                break;

            default:
                cout << "\nInvalid Choice.\n";
        }
    } while (choice != 3);

    return 0;
}
