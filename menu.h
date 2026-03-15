#ifndef MENU_H
#define MENU_H

#include "bank.h"

void displayMainMenu();
void customerMenu(Bank& bank);
void accountMenu(Bank& bank);
void transactionMenu(Bank& bank);
void reportsMenu(Bank& bank);

#endif // MENU_H
