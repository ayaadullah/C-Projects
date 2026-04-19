#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// ===================== TRANSACTION CLASS =====================
class Transaction {
private:
    vector<string> history;

public:
    void addTransaction(string t) {
        history.push_back(t);

        ofstream file("transactions.txt", ios::app);
        file << t << endl;
        file.close();
    }

    void showHistory() {
        cout << "\n--- Transaction History ---\n";
        for (auto &t : history) {
            cout << t << endl;
        }
    }
};

// ===================== ACCOUNT CLASS =====================
class Account {
private:
    string accountNumber;
    string holderName;
    double balance;
    Transaction transaction;

public:
    Account() {
        accountNumber = "";
        holderName = "";
        balance = 0;
    }

    Account(string acc, string name, double bal) {
        accountNumber = acc;
        holderName = name;
        balance = bal;
    }

    string getAccountNumber() { return accountNumber; }

    void deposit(double amount) {
        balance += amount;
        transaction.addTransaction("Deposited: " + to_string(amount));
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            transaction.addTransaction("Withdrawn: " + to_string(amount));
        } else {
            cout << "Insufficient Balance!\n";
        }
    }

    void display() {
        cout << "\nAccount No: " << accountNumber;
        cout << "\nName: " << holderName;
        cout << "\nBalance: " << balance << endl;
    }

    void showTransactions() {
        transaction.showHistory();
    }

    void saveToFile() {
        ofstream file("accounts.txt", ios::app);
        file << accountNumber << "," << holderName << "," << balance << endl;
        file.close();
    }
};

// ===================== CUSTOMER CLASS =====================
class Customer {
public:
    void performDeposit(Account &acc, double amount) {
        acc.deposit(amount);
    }

    void performWithdraw(Account &acc, double amount) {
        acc.withdraw(amount);
    }
};

// ===================== ADMIN CLASS =====================
class Admin {
public:
    static int totalAccounts;
    static int totalTransactions;

    void newAccount() {
        totalAccounts++;
    }

    void newTransaction() {
        totalTransactions++;
    }

    void showStats() {
        cout << "\n--- BANK STATS ---";
        cout << "\nTotal Accounts: " << totalAccounts;
        cout << "\nTotal Transactions: " << totalTransactions << endl;
    }
};

int Admin::totalAccounts = 0;
int Admin::totalTransactions = 0;

// ===================== MAIN SYSTEM =====================
int main() {
    vector<Account> accounts;
    Customer customer;
    Admin admin;

    int choice;

    do {
        cout << "\n===== SMART BANKING SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. View Accounts";
        cout << "\n5. View Transactions";
        cout << "\n6. Bank Stats";
        cout << "\n0. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string acc, name;
            double bal;

            cout << "Enter Account Number: ";
            cin >> acc;
            cout << "Enter Name: ";
            cin >> name;
            cout << "Enter Initial Balance: ";
            cin >> bal;

            Account a(acc, name, bal);
            accounts.push_back(a);
            a.saveToFile();
            admin.newAccount();
        }

        else if (choice == 2) {
            string acc;
            double amount;

            cout << "Enter Account Number: ";
            cin >> acc;
            cout << "Enter Amount: ";
            cin >> amount;

            for (auto &a : accounts) {
                if (a.getAccountNumber() == acc) {
                    customer.performDeposit(a, amount);
                    admin.newTransaction();
                }
            }
        }

        else if (choice == 3) {
            string acc;
            double amount;

            cout << "Enter Account Number: ";
            cin >> acc;
            cout << "Enter Amount: ";
            cin >> amount;

            for (auto &a : accounts) {
                if (a.getAccountNumber() == acc) {
                    customer.performWithdraw(a, amount);
                    admin.newTransaction();
                }
            }
        }

        else if (choice == 4) {
            for (auto &a : accounts)
                a.display();
        }

        else if (choice == 5) {
            for (auto &a : accounts)
                a.showTransactions();
        }

        else if (choice == 6) {
            admin.showStats();
        }

    } while (choice != 0);

    return 0;
}