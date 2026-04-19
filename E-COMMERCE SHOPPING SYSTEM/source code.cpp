#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ===================== PRODUCT CLASS =====================
class Product {
private:
    string name;
    double price;
    int stock;

public:
    Product() {}

    Product(string n, double p, int s) {
        name = n;
        price = p;
        stock = s;
    }

    string getName() { return name; }
    double getPrice() { return price; }
    int getStock() { return stock; }

    void reduceStock(int qty) {
        if (stock >= qty)
            stock -= qty;
    }

    void display() {
        cout << "\nProduct: " << name;
        cout << "\nPrice: " << price;
        cout << "\nStock: " << stock << endl;
    }
};

// ===================== CART CLASS (COMPOSITION) =====================
class Cart {
private:
    vector<Product> items;
    double total;

public:
    Cart() {
        total = 0;
    }

    void addToCart(Product p) {
        items.push_back(p);
        total += p.getPrice();

        cout << p.getName() << " added to cart.\n";
    }

    void showCart() {
        cout << "\n--- CART ITEMS ---";
        for (auto &p : items) {
            p.display();
        }
        cout << "\nTotal Bill: " << total << endl;
    }

    double getTotal() {
        return total;
    }
};

// ===================== ORDER CLASS =====================
class Order {
public:
    static int totalOrders;

    void checkout(Cart &cart, string userName) {
        cout << "\nOrder Placed Successfully!";
        cout << "\nTotal Amount: " << cart.getTotal() << endl;

        ofstream file("orders.txt", ios::app);
        file << "User: " << userName << " | Total: " << cart.getTotal() << endl;
        file.close();

        totalOrders++;
    }

    void showStats() {
        cout << "\nTotal Orders: " << totalOrders << endl;
    }
};

int Order::totalOrders = 0;

// ===================== USER CLASS =====================
class User {
private:
    string name;
    Cart cart;

public:
    User(string n) {
        name = n;
    }

    string getName() {
        return name;
    }

    void browse(Product products[], int size) {
        for (int i = 0; i < size; i++) {
            products[i].display();
        }
    }

    void addProduct(Product p) {
        cart.addToCart(p);
    }

    void viewCart() {
        cart.showCart();
    }

    Cart& getCart() {
        return cart;
    }
};

// ===================== MAIN SYSTEM =====================
int main() {
    Product products[3] = {
        Product("Laptop", 1200, 5),
        Product("Phone", 800, 10),
        Product("Headphones", 150, 20)
    };

    User user("Ali");
    Order order;

    int choice;

    do {
        cout << "\n===== E-COMMERCE SYSTEM =====";
        cout << "\n1. View Products";
        cout << "\n2. Add to Cart";
        cout << "\n3. View Cart";
        cout << "\n4. Checkout";
        cout << "\n5. Order Stats";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            user.browse(products, 3);
        }

        else if (choice == 2) {
            int index;
            cout << "Enter product index (0-2): ";
            cin >> index;

            if (index >= 0 && index < 3)
                user.addProduct(products[index]);
        }

        else if (choice == 3) {
            user.viewCart();
        }

        else if (choice == 4) {
            order.checkout(user.getCart(), user.getName());
        }

        else if (choice == 5) {
            order.showStats();
        }

    } while (choice != 0);

    return 0;
}