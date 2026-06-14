# Inventory Management System (Technova Electronics)

A standard console-based **Inventory Management System** implemented in C++ using advanced **Object-Oriented Programming (OOP)** paradigms. The system features multi-role login authorization, persistent flat-file tracking for stock control, algorithmic product lookups, automated transactional logic, and visual low-stock indicators.

---

## 🚀 Key Features

* **Role-Based Authentication:** Features isolated navigation panels for authorized Administrators and regular Users/Customers.
* **Persistent File Storage:** Seamlessly synchronizes application state with text files (`products.txt` and `sales.txt`) using customized parsing and pipeline logic.
* **Dynamic Record Management:** Complete CRUD (Create, Read, Update, Delete) capability for processing business inventory items dynamically.
* **Integrated Sales Recording:** Tracks purchases, computes overall billing costs automatically, evaluates quantity checks to prevent overselling, and saves historical logs permanently.
* **Low Stock Warning Alert:** Visually triggers a warning identifier immediately when a stored product's total inventory count dips under a value of 5 units.

---

## 🛠️ Technical Implementation & OOP Architecture

This program effectively leverages fundamental OOP mechanics to ensure structural integrity and modular design:

* **Encapsulation:** The internal components of a data product (ID, name, price, stock metrics) are safely bound using private visibility parameters within the `Product` entity, exposed cleanly through specialized accessors/mutators.
* **Inheritance:** An abstract primary base class (`User`) standardizes generalized verification components, extending specialized sub-menus down to independent derived classes (`Admin` and `Customer`).
* **Polymorphism & Abstract Classes:** Employs dynamic dispatch techniques by marking the signature `virtual void menu() = 0;` as a pure virtual function inside the core structure, enforcing customized menu behavior across endpoints.
* **Operator Overloading:** Overrides the standard stream output handler (`friend ostream& operator<<`) to allow raw object strings to print directly to the user display natively.

---

## 📦 System Credentials

The application uses structural mock profiles for user credential validation:

| User Role | Username | Password |
| :--- | :--- | :--- |
| **System Administrator** | `ayaad.ullah` | `ayaad123` |
| **Standard User / Client** | `azhan.khan` | `azhan123` |

---

## 💻 Getting Started

### Prerequisites
Ensure a modern C++ compiler (such as `g++` via GCC) is configured locally on your system platform.

### Compilation
Open your system terminal within the directory containing the project code file and compile it:

```bash
g++ "Inventory Management System Source Code.cpp" -o inventory_system
