#include <iostream>
#include "bank.h"
#include "menu.h"
using namespace std;

int main() {
    Bank myBank("National Bank of India");

    cout << "\n========================================" << endl;
    cout << "                                        " << endl;
    cout << "  WELCOME TO BANKING MANAGEMENT SYSTEM  " << endl;
    cout << "                                        " << endl;
    cout << "========================================" << endl;

    cout << "\nLoading existing data..." << endl;
    myBank.loadAllData();

    int choice;
    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                customerMenu(myBank);
                break;
            case 2:
                accountMenu(myBank);
                break;
            case 3:
                transactionMenu(myBank);
                break;
            case 4:
                reportsMenu(myBank);
                break;
            case 5:
                myBank.saveAllData();
                cout << "\n========================================" << endl;
                cout << "   Thank you for using our system!     " << endl;
                cout << "              Goodbye!                 " << endl;
                cout << "========================================\n" << endl;
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
