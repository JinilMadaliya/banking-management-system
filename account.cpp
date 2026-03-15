#include "account.h"
#include <iostream>
#include <iomanip>
using namespace std;

// ==================== BASE ACCOUNT CLASS ====================
Account::Account() {
    accountNumber = "";
    accountHolderName = "";
    balance = 0.0;
    dateOpened = getCurrentDate();
}

Account::Account(string accNo, string name, double bal) {
    accountNumber = accNo;
    accountHolderName = name;
    balance = bal;
    dateOpened = getCurrentDate();
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        cout << "\n[SUCCESS] Deposit successful! Rs. " << amount << " added." << endl;
    } else {
        cout << "\n[ERROR] Invalid deposit amount!" << endl;
    }
}

double Account::getBalance() const { return balance; }
string Account::getAccountNumber() const { return accountNumber; }
string Account::getAccountHolderName() const { return accountHolderName; }
string Account::getDateOpened() const { return dateOpened; }

// ==================== SAVINGS ACCOUNT ====================
const double SavingsAccount::WITHDRAWAL_CHARGE = 50.0;

SavingsAccount::SavingsAccount() : Account() {
    interestRate = 4.0;
    withdrawalCount = 0;
}

SavingsAccount::SavingsAccount(string accNo, string name, double bal, double rate)
    : Account(accNo, name, bal) {
    interestRate = rate;
    withdrawalCount = 0;
}

bool SavingsAccount::withdraw(double amount) {
    double charge = 0;
    if (withdrawalCount >= MAX_FREE_WITHDRAWALS) {
        charge = WITHDRAWAL_CHARGE;
        cout << "\n[WARNING] Withdrawal charge of Rs. " << charge << " will be applied." << endl;
    }

    if (amount + charge <= balance && amount > 0) {
        balance -= (amount + charge);
        withdrawalCount++;
        cout << "\n[SUCCESS] Withdrawal successful! Rs. " << amount << " debited." << endl;
        if (charge > 0) {
            cout << "  (Charge: Rs. " << charge << ")" << endl;
        }
        return true;
    } else {
        cout << "\n[ERROR] Insufficient balance or invalid amount!" << endl;
        return false;
    }
}

void SavingsAccount::displayDetails() {
    cout << "\n========================================" << endl;
    cout << "       SAVINGS ACCOUNT DETAILS          " << endl;
    cout << "========================================" << endl;
    cout << "Account Number    : " << accountNumber << endl;
    cout << "Account Holder    : " << accountHolderName << endl;
    cout << "Account Type      : Savings Account" << endl;
    cout << "Current Balance   : Rs. " << fixed << setprecision(2) << balance << endl;
    cout << "Interest Rate     : " << interestRate << "% p.a." << endl;
    cout << "Date Opened       : " << dateOpened << endl;
    cout << "Withdrawals Made  : " << withdrawalCount << " (Free: "
         << MAX_FREE_WITHDRAWALS << ")" << endl;
    cout << "========================================" << endl;
}

double SavingsAccount::calculateInterest() {
    return (balance * interestRate) / 100.0;
}

string SavingsAccount::getAccountType() {
    return "Savings";
}

void SavingsAccount::resetWithdrawalCount() {
    withdrawalCount = 0;
}

void SavingsAccount::saveToFile(ofstream& file) {
    file << "SAVINGS|" << accountNumber << "|" << accountHolderName << "|"
         << balance << "|" << interestRate << "|" << withdrawalCount << "|"
         << dateOpened << endl;
}

// ==================== CURRENT ACCOUNT ====================
CurrentAccount::CurrentAccount() : Account() {
    overdraftLimit = 10000.0;
    minimumBalance = 5000.0;
}

CurrentAccount::CurrentAccount(string accNo, string name, double bal, double overdraft)
    : Account(accNo, name, bal) {
    overdraftLimit = overdraft;
    minimumBalance = 5000.0;
}

bool CurrentAccount::withdraw(double amount) {
    if (amount <= 0) {
        cout << "\n[ERROR] Invalid withdrawal amount!" << endl;
        return false;
    }

    if (balance - amount >= -overdraftLimit) {
        balance -= amount;
        cout << "\n[SUCCESS] Withdrawal successful! Rs. " << amount << " debited." << endl;
        if (balance < 0) {
            cout << "  [WARNING] Using overdraft facility. Balance: Rs. " << balance << endl;
        }
        return true;
    } else {
        cout << "\n[ERROR] Exceeds overdraft limit!" << endl;
        return false;
    }
}

void CurrentAccount::displayDetails() {
    cout << "\n========================================" << endl;
    cout << "       CURRENT ACCOUNT DETAILS          " << endl;
    cout << "========================================" << endl;
    cout << "Account Number    : " << accountNumber << endl;
    cout << "Account Holder    : " << accountHolderName << endl;
    cout << "Account Type      : Current Account" << endl;
    cout << "Current Balance   : Rs. " << fixed << setprecision(2) << balance << endl;
    cout << "Overdraft Limit   : Rs. " << overdraftLimit << endl;
    cout << "Minimum Balance   : Rs. " << minimumBalance << endl;
    cout << "Date Opened       : " << dateOpened << endl;
    cout << "========================================" << endl;
}

double CurrentAccount::calculateInterest() {
    return 0.0;
}

string CurrentAccount::getAccountType() {
    return "Current";
}

void CurrentAccount::setOverdraftLimit(double limit) {
    overdraftLimit = limit;
}

void CurrentAccount::saveToFile(ofstream& file) {
    file << "CURRENT|" << accountNumber << "|" << accountHolderName << "|"
         << balance << "|" << overdraftLimit << "|" << minimumBalance << "|"
         << dateOpened << endl;
}

// ==================== FIXED DEPOSIT ACCOUNT ====================
FixedDepositAccount::FixedDepositAccount() : Account() {
    interestRate = 7.0;
    tenureMonths = 12;
    isMatured = false;
}

FixedDepositAccount::FixedDepositAccount(string accNo, string name, double amt, double rate, int tenure)
    : Account(accNo, name, amt) {
    interestRate = rate;
    tenureMonths = tenure;
    isMatured = false;
    maturityDate = "After " + to_string(tenure) + " months";
}

bool FixedDepositAccount::withdraw(double amount) {
    if (!isMatured) {
        cout << "\n[ERROR] Cannot withdraw before maturity!" << endl;
        cout << "  Maturity: " << maturityDate << endl;
        cout << "  Premature withdrawal will incur penalties." << endl;
        return false;
    }

    if (amount <= balance && amount > 0) {
        balance -= amount;
        cout << "\n[SUCCESS] Withdrawal successful! Rs. " << amount << " debited." << endl;
        return true;
    } else {
        cout << "\n[ERROR] Invalid withdrawal amount!" << endl;
        return false;
    }
}

void FixedDepositAccount::displayDetails() {
    cout << "\n========================================" << endl;
    cout << "    FIXED DEPOSIT ACCOUNT DETAILS       " << endl;
    cout << "========================================" << endl;
    cout << "Account Number    : " << accountNumber << endl;
    cout << "Account Holder    : " << accountHolderName << endl;
    cout << "Account Type      : Fixed Deposit" << endl;
    cout << "Deposit Amount    : Rs. " << fixed << setprecision(2) << balance << endl;
    cout << "Interest Rate     : " << interestRate << "% p.a." << endl;
    cout << "Tenure            : " << tenureMonths << " months" << endl;
    cout << "Maturity Date     : " << maturityDate << endl;
    cout << "Maturity Amount   : Rs. " << calculateMaturityAmount() << endl;
    cout << "Status            : " << (isMatured ? "Matured" : "Active") << endl;
    cout << "Date Opened       : " << dateOpened << endl;
    cout << "========================================" << endl;
}

double FixedDepositAccount::calculateInterest() {
    return (balance * interestRate * tenureMonths) / (100.0 * 12.0);
}

string FixedDepositAccount::getAccountType() {
    return "Fixed Deposit";
}

double FixedDepositAccount::calculateMaturityAmount() {
    return balance + calculateInterest();
}

void FixedDepositAccount::markAsMatured() {
    isMatured = true;
    balance = calculateMaturityAmount();
}

void FixedDepositAccount::saveToFile(ofstream& file) {
    file << "FD|" << accountNumber << "|" << accountHolderName << "|"
         << balance << "|" << interestRate << "|" << tenureMonths << "|"
         << isMatured << "|" << dateOpened << endl;
}
