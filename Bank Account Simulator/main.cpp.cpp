#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Account {
  protected:
    std::string accountNumber;
    std::string holderName;
    double balance;
    std::vector<std::string> transactionHistory;

    void addHistory(const std::string &action) {
        if (transactionHistory.size() == 10) {
            transactionHistory.erase(transactionHistory.begin());
        }
        transactionHistory.push_back(action);
    }

    std::string formatMoney(double amount) const {
        std::ostringstream out;
        out << std::fixed << std::setprecision(2) << amount;
        return out.str();
    }

  public:
    Account(std::string accNo, std::string name, double initialBalance)
        : accountNumber(std::move(accNo)), holderName(std::move(name)), balance(initialBalance) {
        addHistory("Account opened with initial balance: $" + formatMoney(initialBalance));
    }

    virtual ~Account() = default;

    virtual void deposit(double amount) {
        if (amount <= 0) {
            std::cout << "Deposit amount must be greater than 0.\n";
            return;
        }
        balance += amount;
        addHistory("Deposited: $" + formatMoney(amount));
    }

    virtual bool withdraw(double amount) {
        if (amount <= 0) {
            std::cout << "Withdrawal amount must be greater than 0.\n";
            return false;
        }
        if (amount > balance) {
            std::cout << "Insufficient funds.\n";
            addHistory("Failed withdrawal (insufficient funds): $" + formatMoney(amount));
            return false;
        }
        balance -= amount;
        addHistory("Withdrew: $" + formatMoney(amount));
        return true;
    }

    virtual double calculateInterest() const = 0;

    virtual void processMonthEnd() {
        double monthlyInterest = calculateInterest();
        if (monthlyInterest > 0) {
            balance += monthlyInterest;
            addHistory("Month-end interest added: $" + formatMoney(monthlyInterest));
        }
    }

    virtual std::string getAccountType() const = 0;

    void displaySummary() const {
        std::cout << "\n--- Account Summary ---\n";
        std::cout << "Type: " << getAccountType() << "\n";
        std::cout << "Account Number: " << accountNumber << "\n";
        std::cout << "Holder Name: " << holderName << "\n";
        std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    }

    void displayTransactionHistory() const {
        std::cout << "\n--- Last " << transactionHistory.size() << " Transaction(s) ---\n";
        for (size_t i = 0; i < transactionHistory.size(); ++i) {
            std::cout << i + 1 << ". " << transactionHistory[i] << "\n";
        }
    }
};

class SavingsAccount : public Account {
  private:
    double annualInterestRate;

  public:
    SavingsAccount(std::string accNo, std::string name, double initialBalance, double annualRate)
        : Account(std::move(accNo), std::move(name), initialBalance), annualInterestRate(annualRate) {}

    double calculateInterest() const override {
        return balance * (annualInterestRate / 12.0);
    }

    std::string getAccountType() const override {
        return "Savings Account";
    }
};

class CheckingAccount : public Account {
  private:
    double transactionFee;

    bool applyFee(const std::string &action) {
        if (balance < transactionFee) {
            addHistory("Fee skipped after " + action + " (insufficient balance for fee)");
            return false;
        }
        balance -= transactionFee;
        addHistory("Transaction fee charged after " + action + ": $" + formatMoney(transactionFee));
        return true;
    }

  public:
    CheckingAccount(std::string accNo, std::string name, double initialBalance, double fee)
        : Account(std::move(accNo), std::move(name), initialBalance), transactionFee(fee) {}

    void deposit(double amount) override {
        if (amount <= 0) {
            std::cout << "Deposit amount must be greater than 0.\n";
            return;
        }
        balance += amount;
        addHistory("Deposited: $" + formatMoney(amount));
        applyFee("deposit");
    }

    bool withdraw(double amount) override {
        if (amount <= 0) {
            std::cout << "Withdrawal amount must be greater than 0.\n";
            return false;
        }

        double totalDebit = amount + transactionFee;
        if (totalDebit > balance) {
            std::cout << "Insufficient funds (including transaction fee).\n";
            addHistory("Failed withdrawal (including fee): $" + formatMoney(amount));
            return false;
        }

        balance -= amount;
        addHistory("Withdrew: $" + formatMoney(amount));
        applyFee("withdrawal");
        return true;
    }

    double calculateInterest() const override {
        return 0.0;
    }

    std::string getAccountType() const override {
        return "Checking Account";
    }
};

void showMenu() {
    std::cout << "\n===== Bank Account Simulator (Advanced) =====\n";
    std::cout << "1. Deposit\n";
    std::cout << "2. Withdraw\n";
    std::cout << "3. Process Month End\n";
    std::cout << "4. View Account Summary\n";
    std::cout << "5. View Transaction History (last 10)\n";
    std::cout << "6. Exit\n";
    std::cout << "Choose an option: ";
}

int main() {
    std::cout << "Choose account type:\n";
    std::cout << "1. Savings Account\n";
    std::cout << "2. Checking Account\n";
    std::cout << "Enter choice: ";

    int accountChoice = 0;
    std::cin >> accountChoice;

    std::unique_ptr<Account> account;
    if (accountChoice == 1) {
        account = std::make_unique<SavingsAccount>("SA-1001", "Alex Johnson", 1000.00, 0.04);
    } else if (accountChoice == 2) {
        account = std::make_unique<CheckingAccount>("CA-2001", "Alex Johnson", 1000.00, 2.50);
    } else {
        std::cout << "Invalid choice. Exiting...\n";
        return 0;
    }

    int choice = 0;
    while (choice != 6) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            double amount;
            std::cout << "Enter amount to deposit: $";
            std::cin >> amount;
            account->deposit(amount);
            break;
        }
        case 2: {
            double amount;
            std::cout << "Enter amount to withdraw: $";
            std::cin >> amount;
            account->withdraw(amount);
            break;
        }
        case 3:
            account->processMonthEnd();
            std::cout << "Month-end processing complete.\n";
            break;
        case 4:
            account->displaySummary();
            break;
        case 5:
            account->displayTransactionHistory();
            break;
        case 6:
            std::cout << "Thank you for using the Bank Account Simulator.\n";
            break;
        default:
            std::cout << "Invalid option. Try again.\n";
        }
    }

    return 0;
}