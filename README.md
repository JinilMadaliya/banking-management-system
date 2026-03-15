# 🏦 Banking Management System

A console-based **Banking Management System** built in C++ that demonstrates core Object-Oriented Programming concepts including inheritance, polymorphism, encapsulation, and file I/O. The project is organized into a clean modular structure using separate header and source files.

---

## 📁 Project Structure

```
banking/
├── main.cpp            # Entry point — initializes bank, runs main loop
├── utils.h / .cpp      # Date & time utility functions
├── transaction.h / .cpp# Transaction recording and display
├── account.h / .cpp    # Abstract Account base + Savings, Current, FD classes
├── customer.h / .cpp   # Customer profile and account management
├── bank.h / .cpp       # Core banking operations and file I/O
├── menu.h / .cpp       # All menu/UI interaction functions
├── Makefile            # Build configuration
└── README.md
```

---

## ✨ Features

- **Customer Management** — Add, view, and list customers
- **Account Types**
  - 💰 Savings Account — with interest rate and free withdrawal limit
  - 🏢 Current Account — with overdraft facility
  - 📅 Fixed Deposit Account — with tenure-based maturity calculation
- **Transactions** — Deposit, Withdraw, Transfer funds between accounts
- **Transaction History** — Per-account log of all operations
- **Interest Calculation** — Based on account type and balance
- **Data Persistence** — Saves and loads all data from flat text files (`customers.txt`, `accounts.txt`, `transactions.txt`)

---

## 🧱 OOP Concepts Used

| Concept | Where Applied |
|---|---|
| **Abstraction** | `Account` is an abstract base class with pure virtual methods |
| **Inheritance** | `SavingsAccount`, `CurrentAccount`, `FixedDepositAccount` extend `Account` |
| **Polymorphism** | Virtual `withdraw()`, `displayDetails()`, `calculateInterest()` |
| **Encapsulation** | Private data members with public getters across all classes |
| **Dynamic Memory** | Accounts and transactions heap-allocated with proper destructors |

---

## 🔧 Requirements

- **C++ Compiler** — g++ with C++11 support or later
- **Make** — for using the Makefile (optional)
- Works on **Linux**, **macOS**, and **Windows** (with MinGW or WSL)

---

## 🚀 Build & Run

### Using Make
```bash
make
./banking
```

### Manual Compilation
```bash
g++ -std=c++11 main.cpp utils.cpp transaction.cpp account.cpp customer.cpp bank.cpp menu.cpp -o banking
./banking
```

### Clean Build Artifacts
```bash
make clean
```

---

## 🗂️ Data Files

The program automatically creates these files on save:

| File | Contents |
|---|---|
| `customers.txt` | Customer ID, name, address, phone, email |
| `accounts.txt` | Account type, number, holder, balance, and type-specific fields |
| `transactions.txt` | Transaction ID, type, amount, date, time, balance after |

Data is loaded automatically on startup if the files exist.

---

## 📋 Menu Overview

```
BANKING MANAGEMENT SYSTEM
1. Customer Management
   ├── Add New Customer
   ├── View Customer Details
   └── View All Customers
2. Account Management
   ├── Create New Account
   ├── View Account Details
   └── Close Account
3. Transactions
   ├── Deposit Money
   ├── Withdraw Money
   ├── Transfer Funds
   ├── View Transaction History
   └── Calculate Interest
4. Reports & Information
   ├── Bank Summary
   ├── View All Customers
   └── Search Account
5. Save Data & Exit
```

---

## 📐 Class Hierarchy

```
Account  (abstract)
├── SavingsAccount
├── CurrentAccount
└── FixedDepositAccount

Customer
└── holds → Account* [up to 10]

Bank
├── holds → Customer* [up to 100]
└── holds → Transaction* [up to 1000]
```

---

## 👤 Author

**Your Name**
- GitHub: [@JinilMadaliya](https://github.com/JinilMadaliya)

---

## 📄 License

This project is open source and available under the [MIT License](LICENSE).
