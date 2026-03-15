#include "menu.h"
#include <iostream>
#include <iomanip>
using namespace std;

void displayMainMenu() {
    cout << "\n";
    cout << "========================================" << endl;
    cout << "     BANKING MANAGEMENT SYSTEM          " << endl;
    cout << "========================================" << endl;
    cout << "1. Customer Management" << endl;
    cout << "2. Account Management" << endl;
    cout << "3. Transactions" << endl;
    cout << "4. Reports & Information" << endl;
    cout << "5. Save Data & Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

void customerMenu(Bank& bank) {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "      CUSTOMER MANAGEMENT               " << endl;
        cout << "========================================" << endl;
        cout << "1. Add New Customer" << endl;
        cout << "2. View Customer Details" << endl;
        cout << "3. View All Customers" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string id, name, address, phone, email;
                cout << "\nEnter Customer ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Name: ";
                getline(cin, name);
                cout << "Enter Address: ";
                getline(cin, address);
                cout << "Enter Phone: ";
                cin >> phone;
                cout << "Enter Email: ";
                cin >> email;

                Customer* newCust = new Customer(id, name, address, phone, email);
                bank.addCustomer(newCust);
                break;
            }
            case 2: {
                string custID;
                cout << "\nEnter Customer ID: ";
                cin >> custID;
                Customer* cust = bank.findCustomer(custID);
                if (cust != nullptr) {
                    cust->displayCustomerInfo();
                    cust->displayAllAccounts();
                } else {
                    cout << "\n[ERROR] Customer not found!" << endl;
                }
                break;
            }
            case 3:
                bank.displayAllCustomers();
                break;
            case 4:
                return;
            default:
                cout << "\n[ERROR] Invalid choice!" << endl;
        }
    } while (choice != 4);
}

void accountMenu(Bank& bank) {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "       ACCOUNT MANAGEMENT               " << endl;
        cout << "========================================" << endl;
        cout << "1. Create New Account" << endl;
        cout << "2. View Account Details" << endl;
        cout << "3. Close Account" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string custID;
                int accType;
                cout << "\nEnter Customer ID: ";
                cin >> custID;
                cout << "\nSelect Account Type:" << endl;
                cout << "1. Savings Account" << endl;
                cout << "2. Current Account" << endl;
                cout << "3. Fixed Deposit Account" << endl;
                cout << "Enter choice: ";
                cin >> accType;

                bank.createAccount(custID, accType);
                break;
            }
            case 2: {
                string accNo;
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                Account* acc = bank.searchAccount(accNo);
                if (acc != nullptr) {
                    acc->displayDetails();
                } else {
                    cout << "\n[ERROR] Account not found!" << endl;
                }
                break;
            }
            case 3: {
                string custID, accNo;
                cout << "\nEnter Customer ID: ";
                cin >> custID;
                cout << "Enter Account Number: ";
                cin >> accNo;
                Customer* cust = bank.findCustomer(custID);
                if (cust != nullptr) {
                    cust->removeAccount(accNo);
                } else {
                    cout << "\n[ERROR] Customer not found!" << endl;
                }
                break;
            }
            case 4:
                return;
            default:
                cout << "\n[ERROR] Invalid choice!" << endl;
        }
    } while (choice != 4);
}

void transactionMenu(Bank& bank) {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "          TRANSACTIONS                  " << endl;
        cout << "========================================" << endl;
        cout << "1. Deposit Money" << endl;
        cout << "2. Withdraw Money" << endl;
        cout << "3. Transfer Funds" << endl;
        cout << "4. View Transaction History" << endl;
        cout << "5. Calculate Interest" << endl;
        cout << "6. Back to Main Menu" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string accNo;
                double amount;
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                cout << "Enter Amount to Deposit: Rs. ";
                cin >> amount;
                bank.performDeposit(accNo, amount);
                break;
            }
            case 2: {
                string accNo;
                double amount;
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                cout << "Enter Amount to Withdraw: Rs. ";
                cin >> amount;
                bank.performWithdrawal(accNo, amount);
                break;
            }
            case 3: {
                string fromAcc, toAcc;
                double amount;
                cout << "\nEnter Source Account Number: ";
                cin >> fromAcc;
                cout << "Enter Destination Account Number: ";
                cin >> toAcc;
                cout << "Enter Amount to Transfer: Rs. ";
                cin >> amount;
                bank.transferFunds(fromAcc, toAcc, amount);
                break;
            }
            case 4: {
                string accNo;
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                bank.displayTransactionHistory(accNo);
                break;
            }
            case 5: {
                string accNo;
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                Account* acc = bank.searchAccount(accNo);
                if (acc != nullptr) {
                    double interest = acc->calculateInterest();
                    cout << "\n========================================" << endl;
                    cout << "       INTEREST CALCULATION             " << endl;
                    cout << "========================================" << endl;
                    cout << "Account Number  : " << acc->getAccountNumber() << endl;
                    cout << "Account Type    : " << acc->getAccountType() << endl;
                    cout << "Current Balance : Rs. " << fixed << setprecision(2)
                         << acc->getBalance() << endl;
                    cout << "Interest Earned : Rs. " << interest << endl;
                    cout << "========================================" << endl;
                } else {
                    cout << "\n[ERROR] Account not found!" << endl;
                }
                break;
            }
            case 6:
                return;
            default:
                cout << "\n[ERROR] Invalid choice!" << endl;
        }
    } while (choice != 6);
}

void reportsMenu(Bank& bank) {
    int choice;
    do {
        cout << "\n========================================" << endl;
        cout << "      REPORTS & INFORMATION             " << endl;
        cout << "========================================" << endl;
        cout << "1. Bank Summary" << endl;
        cout << "2. View All Customers" << endl;
        cout << "3. Search Account" << endl;
        cout << "4. Back to Main Menu" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bank.displayBankSummary();
                break;
            case 2:
                bank.displayAllCustomers();
                break;
            case 3: {
                string accNo;
                cout << "\nEnter Account Number: ";
                cin >> accNo;
                Account* acc = bank.searchAccount(accNo);
                if (acc != nullptr) {
                    acc->displayDetails();
                } else {
                    cout << "\n[ERROR] Account not found!" << endl;
                }
                break;
            }
            case 4:
                return;
            default:
                cout << "\n[ERROR] Invalid choice!" << endl;
        }
    } while (choice != 4);
}
