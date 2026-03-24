#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
using namespace std;

class Item {
private:
    int id;
    string name;
    int quantity;
    double price;
public:
    Item() {}
    Item(int id, string name, int qty, double price);

    void setID(int id);
    int getID();
    void setName(string name);
    string getName();
    void setQuantity(int qty);
    int getQuantity();
    void setPrice(double price);
    double getPrice();

    void displayItem();
};

#endif
#include "inventory.h"
#include <iostream>
using namespace std;

Item::Item(int id, string name, int qty, double price) {
    this->id = id;
    this->name = name;
    this->quantity = qty;
    this->price = price;
}

void Item::setID(int id) { this->id = id; }
int Item::getID() { return id; }

void Item::setName(string name) { this->name = name; }
string Item::getName() { return name; }

void Item::setQuantity(int qty) { quantity = qty; }
int Item::getQuantity() { return quantity; }

void Item::setPrice(double price) { this->price = price; }
double Item::getPrice() { return price; }

void Item::displayItem() {
    cout << "ID: " << id << " | Name: " << name
         << " | Qty: " << quantity << " | Price: " << price << endl;
}
#include <iostream>
#include <fstream>
#include <vector>
#include "inventory.h"
using namespace std;

vector<Item> inventory;

// Function prototypes
void loadInventory();
void saveInventory();
void addItem();
void displayInventory();
void updateItem();
void searchItem();
void deleteItem();

int main() {
    loadInventory();
    int choice;
    do {
        cout << "\n--- Inventory Management ---\n";
        cout << "1. Add Item\n2. Display Inventory\n3. Update Item\n";
        cout << "4. Search Item\n5. Delete Item\n6. Exit\nChoice: ";
        cin >> choice;

        switch(choice) {
            case 1: addItem(); break;
            case 2: displayInventory(); break;
            case 3: updateItem(); break;
            case 4: searchItem(); break;
            case 5: deleteItem(); break;
            case 6: saveInventory(); cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while(choice != 6);
    return 0;
}
void loadInventory() {
    ifstream fin("inventory.txt");
    int id, qty;
    string name;
    double price;
    while(fin >> id >> ws && getline(fin, name) >> qty >> price) {
        inventory.push_back(Item(id, name, qty, price));
    }
    fin.close();
}

void saveInventory() {
    ofstream fout("inventory.txt");
    for(auto &item: inventory) {
        fout << item.getID() << " " << item.getName() << " " 
             << item.getQuantity() << " " << item.getPrice() << endl;
    }
    fout.close();
}