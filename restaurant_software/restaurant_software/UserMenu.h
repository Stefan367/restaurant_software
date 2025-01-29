/*
* Solution to course project #1
* Introduction to programming course
* Faculty of Mathematics And Informatics of Sofia University
* Winter semester 2024/2025
*
* @author Stefan Ivanov
* @idnumber 2MI0600509
* @compiler VCC
*
* Generates the user menu
*
*/

#include <iostream>
#include <string>
#ifndef USERMENU_H
#define USERMENU_H
using namespace std;

#include "HelperFunctions.h"
#include "Constants.h"

bool isChoiceValid(unsigned int choice)
{
	if (userRole)
		return doesElementContainsInAnArray(choice, VALID_CHOICES_MANAGER, NUMBER_OF_VALID_CHOICES_FOR_MANAGER);

	else
		return doesElementContainsInAnArray(choice, VALID_CHOICES_WAITER, NUMBER_OF_VALID_CHOICES_FOR_WAITER);
}

bool checkIsRoleValid(string role)
{
	return (role == "waiter" || role == "manager") ? true : false;
}

void setUserRole(string role)
{
	userRole = (role == "manager") ? 1 : 0;
}

void chooseRole()
{
	string role;
	while (true)
	{
		cout << "Enter your role (waiter/manager): ";
		cin >> role;
		cin.ignore(numeric_limits<streamsize>::max(), NEW_LINE);

		if (checkIsRoleValid(role))
		{
			setUserRole(role);
			break;
		}
		cout << "Invalid input! ";
	}
}

void makeYourChoice()
{
	unsigned int choice;

	while (true)
	{
		cout << "Your choice is: ";
		cin >> choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), NEW_LINE);
			cout << "Invalid input! Please enter a number." << endl;
			continue;
		}

		if (isChoiceValid(choice))
		{
			currentChoice = choice;
			break;
		}
		cout << "Invalid choice! You can only choose from 1 to " << (userRole ? "14" : "7") << endl;
	}
}

void visualizeOptions()
{
	if (userRole || !userRole)
	{
		cout << endl << "1. View menu." << endl;
		cout << "2. Create an order." << endl;
		cout << "3. Cancel order." << endl;
		cout << "4. View previous orders." << endl;
		cout << "5. View previous orders sorted alphabetically and the number of orders of every item." << endl;
		cout << "6. View the daily sales." << endl;
	}

	if (!userRole) cout << "7. End application." << endl;

	if (userRole)
	{
		cout << "7. View what has left in the storage." << endl;
		cout << "8. Remove product from the storage." << endl;
		cout << "9. Add product in the storage." << endl;
		cout << "10. Make daily report." << endl;
		cout << "11. View all daily reports from a given date to today." << endl;
		cout << "12. Add new item on the menu." << endl;
		cout << "13. Remove an item on the menu." << endl;
		cout << "14. End application." << endl;
	}
}

#endif