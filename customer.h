#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <fstream>
#include "account.h"

class Customer {
private:
    std::string customerID;
    std::string name;
    std::string address;
    std::string phoneNumber;
    std::string email;
    Account* accounts[10];
    int accountCount;

public:
    Customer();
    Customer(std::string id, std::string n, std::string addr, std::string phone, std::string mail);

    void addAccount(Account* acc);
    void addAccountWithMessage(Account* acc);
    void displayAllAccounts();
    Account* findAccount(std::string accNo);
    void removeAccount(std::string accNo);

    std::string getCustomerID() const;
    std::string getName() const;
    std::string getAddress() const;
    std::string getPhoneNumber() const;
    std::string getEmail() const;
    int getAccountCount() const;

    void displayCustomerInfo();
    void saveToFile(std::ofstream& file);
    void saveAccountsToFile(std::ofstream& file);

    ~Customer();
};

#endif // CUSTOMER_H
