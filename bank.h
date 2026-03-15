#ifndef BANK_H
#define BANK_H

#include <string>
#include "customer.h"
#include "transaction.h"

class Bank {
private:
    std::string bankName;
    Customer* customers[100];
    int customerCount;
    Transaction* transactionHistory[1000];
    int transactionCount;
    static int accountNumberCounter;

    std::string generateAccountNumber(std::string type);
    bool accountExists(std::string accNo);
    bool customerIDExists(std::string custID);

public:
    Bank(std::string name);

    void addCustomer(Customer* cust);
    Customer* findCustomer(std::string custID);
    void displayAllCustomers();

    void createAccount(std::string custID, int accountType);
    Account* searchAccount(std::string accNo);

    void performDeposit(std::string accNo, double amount);
    void performWithdrawal(std::string accNo, double amount);
    void transferFunds(std::string fromAcc, std::string toAcc, double amount);
    void displayTransactionHistory(std::string accNo);

    void saveAllData();
    void loadAllData();
    void displayBankSummary();

    ~Bank();
};

#endif // BANK_H
