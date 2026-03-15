#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <fstream>

class Transaction {
private:
    std::string transactionID;
    std::string accountNumber;
    std::string transactionType;
    double amount;
    std::string date;
    std::string time;
    double balanceAfter;
    static int transactionCounter;

public:
    Transaction(std::string accNo, std::string type, double amt, double balance);

    void displayTransaction();
    std::string getAccountNumber();
    void saveToFile(std::ofstream& file);
};

#endif // TRANSACTION_H
