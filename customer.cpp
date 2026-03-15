#include "customer.h"
#include <iostream>
using namespace std;

Customer::Customer() {
    customerID = "";
    name = "";
    address = "";
    phoneNumber = "";
    email = "";
    accountCount = 0;
    for (int i = 0; i < 10; i++) {
        accounts[i] = nullptr;
    }
}

Customer::Customer(string id, string n, string addr, string phone, string mail) {
    customerID = id;
    name = n;
    address = addr;
    phoneNumber = phone;
    email = mail;
    accountCount = 0;
    for (int i = 0; i < 10; i++) {
        accounts[i] = nullptr;
    }
}

void Customer::addAccount(Account* acc) {
    if (accountCount < 10) {
        accounts[accountCount] = acc;
        accountCount++;
    } else {
        cout << "\n[ERROR] Maximum account limit reached!" << endl;
    }
}

void Customer::addAccountWithMessage(Account* acc) {
    if (accountCount < 10) {
        accounts[accountCount] = acc;
        accountCount++;
        cout << "\n[SUCCESS] Account added successfully to customer profile!" << endl;
    } else {
        cout << "\n[ERROR] Maximum account limit reached!" << endl;
    }
}

void Customer::displayAllAccounts() {
    cout << "\n========================================" << endl;
    cout << "         CUSTOMER ACCOUNTS              " << endl;
    cout << "========================================" << endl;
    cout << "Customer: " << name << " (ID: " << customerID << ")" << endl;
    cout << "Total Accounts: " << accountCount << endl;
    cout << "========================================\n" << endl;

    if (accountCount == 0) {
        cout << "No accounts found for this customer." << endl;
    } else {
        for (int i = 0; i < accountCount; i++) {
            if (accounts[i] != nullptr) {
                accounts[i]->displayDetails();
                cout << endl;
            }
        }
    }
}

Account* Customer::findAccount(string accNo) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i] != nullptr && accounts[i]->getAccountNumber() == accNo) {
            return accounts[i];
        }
    }
    return nullptr;
}

void Customer::removeAccount(string accNo) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i] != nullptr && accounts[i]->getAccountNumber() == accNo) {
            delete accounts[i];
            for (int j = i; j < accountCount - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            accounts[accountCount - 1] = nullptr;
            accountCount--;
            cout << "\n[SUCCESS] Account removed successfully!" << endl;
            return;
        }
    }
    cout << "\n[ERROR] Account not found!" << endl;
}

string Customer::getCustomerID() const { return customerID; }
string Customer::getName() const { return name; }
string Customer::getAddress() const { return address; }
string Customer::getPhoneNumber() const { return phoneNumber; }
string Customer::getEmail() const { return email; }
int Customer::getAccountCount() const { return accountCount; }

void Customer::displayCustomerInfo() {
    cout << "\n========================================" << endl;
    cout << "         CUSTOMER INFORMATION           " << endl;
    cout << "========================================" << endl;
    cout << "Customer ID    : " << customerID << endl;
    cout << "Name           : " << name << endl;
    cout << "Address        : " << address << endl;
    cout << "Phone          : " << phoneNumber << endl;
    cout << "Email          : " << email << endl;
    cout << "Total Accounts : " << accountCount << endl;
    cout << "========================================" << endl;
}

void Customer::saveToFile(ofstream& file) {
    file << customerID << "|" << name << "|" << address << "|"
         << phoneNumber << "|" << email << "|" << accountCount << endl;
}

void Customer::saveAccountsToFile(ofstream& file) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i] != nullptr) {
            accounts[i]->saveToFile(file);
        }
    }
}

Customer::~Customer() {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i] != nullptr) {
            delete accounts[i];
        }
    }
}
