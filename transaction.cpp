#include "transaction.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
using namespace std;

int Transaction::transactionCounter = 0;

Transaction::Transaction(string accNo, string type, double amt, double balance) {
    transactionCounter++;
    transactionID = "TXN" + to_string(transactionCounter);
    accountNumber = accNo;
    transactionType = type;
    amount = amt;
    balanceAfter = balance;
    date = getCurrentDate();
    time = getCurrentTime();
}

void Transaction::displayTransaction() {
    cout << "========================================" << endl;
    cout << "Transaction ID  : " << transactionID << endl;
    cout << "Account Number  : " << accountNumber << endl;
    cout << "Type            : " << transactionType << endl;
    cout << "Amount          : Rs. " << fixed << setprecision(2) << amount << endl;
    cout << "Date            : " << date << endl;
    cout << "Time            : " << time << endl;
    cout << "Balance After   : Rs. " << balanceAfter << endl;
    cout << "========================================" << endl;
}

string Transaction::getAccountNumber() {
    return accountNumber;
}

void Transaction::saveToFile(ofstream& file) {
    file << transactionID << "|" << accountNumber << "|"
         << transactionType << "|" << amount << "|"
         << date << "|" << time << "|" << balanceAfter << endl;
}
