#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <fstream>
#include "utils.h"

// ==================== BASE ACCOUNT CLASS ====================
class Account {
protected:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;
    std::string dateOpened;

public:
    Account();
    Account(std::string accNo, std::string name, double bal);

    virtual void deposit(double amount);

    virtual bool withdraw(double amount) = 0;
    virtual void displayDetails() = 0;
    virtual double calculateInterest() = 0;
    virtual std::string getAccountType() = 0;

    double getBalance() const;
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    std::string getDateOpened() const;

    virtual void saveToFile(std::ofstream& file) = 0;

    virtual ~Account() {}
};

// ==================== SAVINGS ACCOUNT ====================
class SavingsAccount : public Account {
private:
    double interestRate;
    int withdrawalCount;
    static const int MAX_FREE_WITHDRAWALS = 4;
    static const double WITHDRAWAL_CHARGE;

public:
    SavingsAccount();
    SavingsAccount(std::string accNo, std::string name, double bal, double rate);

    bool withdraw(double amount) override;
    void displayDetails() override;
    double calculateInterest() override;
    std::string getAccountType() override;
    void resetWithdrawalCount();
    void saveToFile(std::ofstream& file) override;
};

// ==================== CURRENT ACCOUNT ====================
class CurrentAccount : public Account {
private:
    double overdraftLimit;
    double minimumBalance;

public:
    CurrentAccount();
    CurrentAccount(std::string accNo, std::string name, double bal, double overdraft);

    bool withdraw(double amount) override;
    void displayDetails() override;
    double calculateInterest() override;
    std::string getAccountType() override;
    void setOverdraftLimit(double limit);
    void saveToFile(std::ofstream& file) override;
};

// ==================== FIXED DEPOSIT ACCOUNT ====================
class FixedDepositAccount : public Account {
private:
    double interestRate;
    int tenureMonths;
    std::string maturityDate;
    bool isMatured;

public:
    FixedDepositAccount();
    FixedDepositAccount(std::string accNo, std::string name, double amt, double rate, int tenure);

    bool withdraw(double amount) override;
    void displayDetails() override;
    double calculateInterest() override;
    std::string getAccountType() override;
    double calculateMaturityAmount();
    void markAsMatured();
    void saveToFile(std::ofstream& file) override;
};

#endif // ACCOUNT_H
