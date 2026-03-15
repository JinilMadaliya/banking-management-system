#include "bank.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

int Bank::accountNumberCounter = 1000;

Bank::Bank(string name) {
    bankName = name;
    customerCount = 0;
    transactionCount = 0;
    for (int i = 0; i < 100; i++) {
        customers[i] = nullptr;
    }
    for (int i = 0; i < 1000; i++) {
        transactionHistory[i] = nullptr;
    }
}

string Bank::generateAccountNumber(string type) {
    accountNumberCounter++;
    return type + to_string(accountNumberCounter);
}

bool Bank::accountExists(string accNo) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i] != nullptr) {
            if (customers[i]->findAccount(accNo) != nullptr) {
                return true;
            }
        }
    }
    return false;
}

bool Bank::customerIDExists(string custID) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i] != nullptr && customers[i]->getCustomerID() == custID) {
            return true;
        }
    }
    return false;
}

void Bank::addCustomer(Customer* cust) {
    if (customerCount < 100) {
        if (customerIDExists(cust->getCustomerID())) {
            cout << "\n[ERROR] Customer ID already exists! Please use a unique ID." << endl;
            delete cust;
            return;
        }
        customers[customerCount] = cust;
        customerCount++;
        cout << "\n[SUCCESS] Customer added successfully!" << endl;
    } else {
        cout << "\n[ERROR] Customer limit reached!" << endl;
    }
}

Customer* Bank::findCustomer(string custID) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i] != nullptr && customers[i]->getCustomerID() == custID) {
            return customers[i];
        }
    }
    return nullptr;
}

void Bank::displayAllCustomers() {
    cout << "\n========================================" << endl;
    cout << "         ALL CUSTOMERS                  " << endl;
    cout << "========================================" << endl;
    cout << "Bank: " << bankName << endl;
    cout << "Total Customers: " << customerCount << endl;
    cout << "========================================\n" << endl;

    if (customerCount == 0) {
        cout << "No customers found." << endl;
    } else {
        for (int i = 0; i < customerCount; i++) {
            if (customers[i] != nullptr) {
                customers[i]->displayCustomerInfo();
                cout << endl;
            }
        }
    }
}

void Bank::createAccount(string custID, int accountType) {
    Customer* cust = findCustomer(custID);
    if (cust == nullptr) {
        cout << "\n[ERROR] Customer not found!" << endl;
        return;
    }

    string accNo;
    string name = cust->getName();
    double initialDeposit;
    Account* newAccount = nullptr;

    cout << "\nEnter initial deposit amount: Rs. ";
    cin >> initialDeposit;

    if (initialDeposit < 0) {
        cout << "\n[ERROR] Invalid amount!" << endl;
        return;
    }

    switch (accountType) {
        case 1: {
            accNo = generateAccountNumber("SA");
            double rate;
            cout << "Enter interest rate (%): ";
            cin >> rate;
            newAccount = new SavingsAccount(accNo, name, initialDeposit, rate);
            break;
        }
        case 2: {
            accNo = generateAccountNumber("CA");
            double overdraft;
            cout << "Enter overdraft limit: Rs. ";
            cin >> overdraft;
            newAccount = new CurrentAccount(accNo, name, initialDeposit, overdraft);
            break;
        }
        case 3: {
            accNo = generateAccountNumber("FD");
            double rate;
            int tenure;
            cout << "Enter interest rate (%): ";
            cin >> rate;
            cout << "Enter tenure (months): ";
            cin >> tenure;
            newAccount = new FixedDepositAccount(accNo, name, initialDeposit, rate, tenure);
            break;
        }
        default:
            cout << "\n[ERROR] Invalid account type!" << endl;
            return;
    }

    cust->addAccountWithMessage(newAccount);
    cout << "Account Number: " << accNo << endl;
}

Account* Bank::searchAccount(string accNo) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i] != nullptr) {
            Account* acc = customers[i]->findAccount(accNo);
            if (acc != nullptr) {
                return acc;
            }
        }
    }
    return nullptr;
}

void Bank::performDeposit(string accNo, double amount) {
    Account* acc = searchAccount(accNo);
    if (acc != nullptr) {
        acc->deposit(amount);
        Transaction* trans = new Transaction(accNo, "DEPOSIT", amount, acc->getBalance());
        if (transactionCount < 1000) {
            transactionHistory[transactionCount] = trans;
            transactionCount++;
        }
        trans->displayTransaction();
    } else {
        cout << "\n[ERROR] Account not found!" << endl;
    }
}

void Bank::performWithdrawal(string accNo, double amount) {
    Account* acc = searchAccount(accNo);
    if (acc != nullptr) {
        if (acc->withdraw(amount)) {
            Transaction* trans = new Transaction(accNo, "WITHDRAWAL", amount, acc->getBalance());
            if (transactionCount < 1000) {
                transactionHistory[transactionCount] = trans;
                transactionCount++;
            }
            trans->displayTransaction();
        }
    } else {
        cout << "\n[ERROR] Account not found!" << endl;
    }
}

void Bank::transferFunds(string fromAcc, string toAcc, double amount) {
    Account* accFrom = searchAccount(fromAcc);
    Account* accTo = searchAccount(toAcc);

    if (accFrom == nullptr || accTo == nullptr) {
        cout << "\n[ERROR] One or both accounts not found!" << endl;
        return;
    }

    if (accFrom->withdraw(amount)) {
        accTo->deposit(amount);

        Transaction* trans1 = new Transaction(fromAcc, "TRANSFER OUT", amount, accFrom->getBalance());
        Transaction* trans2 = new Transaction(toAcc, "TRANSFER IN", amount, accTo->getBalance());

        if (transactionCount < 998) {
            transactionHistory[transactionCount++] = trans1;
            transactionHistory[transactionCount++] = trans2;
        }

        cout << "\n[SUCCESS] Transfer successful!" << endl;
        cout << "\nFrom Account:" << endl;
        trans1->displayTransaction();
        cout << "\nTo Account:" << endl;
        trans2->displayTransaction();
    }
}

void Bank::displayTransactionHistory(string accNo) {
    cout << "\n========================================" << endl;
    cout << "       TRANSACTION HISTORY              " << endl;
    cout << "========================================" << endl;
    cout << "Account Number: " << accNo << endl;
    cout << "========================================\n" << endl;

    bool found = false;
    for (int i = 0; i < transactionCount; i++) {
        if (transactionHistory[i] != nullptr &&
            transactionHistory[i]->getAccountNumber() == accNo) {
            transactionHistory[i]->displayTransaction();
            found = true;
        }
    }

    if (!found) {
        cout << "No transactions found for this account." << endl;
    }
}

void Bank::saveAllData() {
    ofstream custFile("customers.txt");
    if (custFile.is_open()) {
        for (int i = 0; i < customerCount; i++) {
            if (customers[i] != nullptr) {
                customers[i]->saveToFile(custFile);
            }
        }
        custFile.close();
        cout << "[INFO] Saved " << customerCount << " customers." << endl;
    } else {
        cout << "[ERROR] Could not open customers.txt for writing." << endl;
    }

    ofstream accFile("accounts.txt");
    if (accFile.is_open()) {
        int totalAccounts = 0;
        for (int i = 0; i < customerCount; i++) {
            if (customers[i] != nullptr) {
                customers[i]->saveAccountsToFile(accFile);
                totalAccounts += customers[i]->getAccountCount();
            }
        }
        accFile.close();
        cout << "[INFO] Saved " << totalAccounts << " accounts." << endl;
    } else {
        cout << "[ERROR] Could not open accounts.txt for writing." << endl;
    }

    ofstream transFile("transactions.txt");
    if (transFile.is_open()) {
        for (int i = 0; i < transactionCount; i++) {
            if (transactionHistory[i] != nullptr) {
                transactionHistory[i]->saveToFile(transFile);
            }
        }
        transFile.close();
        cout << "[INFO] Saved " << transactionCount << " transactions." << endl;
    } else {
        cout << "[ERROR] Could not open transactions.txt for writing." << endl;
    }

    cout << "\n[SUCCESS] All data saved successfully!" << endl;
}

void Bank::loadAllData() {
    ifstream custFile("customers.txt");
    if (custFile.is_open()) {
        string line;
        while (getline(custFile, line)) {
            stringstream ss(line);
            string id, name, address, phone, email, accCountStr;

            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, address, '|');
            getline(ss, phone, '|');
            getline(ss, email, '|');
            getline(ss, accCountStr, '|');

            Customer* cust = new Customer(id, name, address, phone, email);
            if (customerCount < 100) {
                customers[customerCount] = cust;
                customerCount++;
            }
        }
        custFile.close();
        if (customerCount > 0) {
            cout << "[INFO] Loaded " << customerCount << " customers from file." << endl;
        }
    }

    ifstream accFile("accounts.txt");
    if (accFile.is_open()) {
        string line;
        int accountsLoaded = 0;
        while (getline(accFile, line)) {
            stringstream ss(line);
            string type, accNo, name, balanceStr, extra1Str, extra2Str, dateOpened;

            getline(ss, type, '|');
            getline(ss, accNo, '|');
            getline(ss, name, '|');
            getline(ss, balanceStr, '|');
            getline(ss, extra1Str, '|');
            getline(ss, extra2Str, '|');
            getline(ss, dateOpened, '|');

            double balance = stod(balanceStr);
            Account* acc = nullptr;

            if (type == "SAVINGS") {
                double rate = stod(extra1Str);
                acc = new SavingsAccount(accNo, name, balance, rate);
            } else if (type == "CURRENT") {
                double overdraft = stod(extra1Str);
                acc = new CurrentAccount(accNo, name, balance, overdraft);
            } else if (type == "FD") {
                double rate = stod(extra1Str);
                int tenure = stoi(extra2Str);
                acc = new FixedDepositAccount(accNo, name, balance, rate, tenure);
            }

            if (acc != nullptr) {
                for (int i = 0; i < customerCount; i++) {
                    if (customers[i] != nullptr && customers[i]->getName() == name) {
                        customers[i]->addAccount(acc);
                        accountsLoaded++;
                        break;
                    }
                }
            }

            if (accNo.length() > 2) {
                int num = stoi(accNo.substr(2));
                if (num >= accountNumberCounter) {
                    accountNumberCounter = num;
                }
            }
        }
        accFile.close();
        if (accountsLoaded > 0) {
            cout << "[INFO] Loaded " << accountsLoaded << " accounts from file." << endl;
        }
    }

    ifstream transFile("transactions.txt");
    if (transFile.is_open()) {
        string line;
        int transLoaded = 0;
        while (getline(transFile, line) && transactionCount < 1000) {
            transLoaded++;
        }
        transFile.close();
        if (transLoaded > 0) {
            cout << "[INFO] Found " << transLoaded << " transaction records in file." << endl;
        }
    }

    if (customerCount > 0) {
        cout << "\n[SUCCESS] Data loaded successfully!\n" << endl;
    }
}

void Bank::displayBankSummary() {
    cout << "\n========================================" << endl;
    cout << "          BANK SUMMARY                  " << endl;
    cout << "========================================" << endl;
    cout << "Bank Name         : " << bankName << endl;
    cout << "Total Customers   : " << customerCount << endl;
    cout << "Total Transactions: " << transactionCount << endl;
    cout << "========================================" << endl;
}

Bank::~Bank() {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i] != nullptr) {
            delete customers[i];
        }
    }
    for (int i = 0; i < transactionCount; i++) {
        if (transactionHistory[i] != nullptr) {
            delete transactionHistory[i];
        }
    }
}
