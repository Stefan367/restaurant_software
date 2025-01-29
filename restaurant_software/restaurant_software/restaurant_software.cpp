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
* The main function of the project. Here is where all functions are called and make the program work.
*
*/

#include <iostream>
#include <string>
using namespace std;

#include "UserMenu.h"
#include "MainFunctions.h"

void completeOption(unsigned int choice)
{
	switch (choice)
	{
	case 1:
		printMenu();
		break;

	case 2:
		orderFoodFromTheMenu();
		break;

	case 3:
		cancelLastOrder();
		break;

	case 4:
		viewAllOrders();
		break;

	case 5:
		viewMealsSortedAndWithCounts();
		break;

	case 6:
		showTodaysDailyReport();
		break;

	case 7:
		if (!userRole)
		{
			startNewWorkingDay();
			saveDataToAllFiles();
			exit(0);
		}
		else
		{
			viewWhatHadLeftInTheStorage();
		}
		break;

	case 8:
		viewWhatHadLeftInTheStorage();
		removeProductFromStorage();
		break;

	case 9:
		viewWhatHadLeftInTheStorage();
		addProductInStorage();
		break;

	case 10:
		makeDailyReport();
		break;

	case 11:
		showDailyReportsFromGivenDateToToday();
		break;

	case 12:
		addMenuItem();
		break;

	case 13:
		if (!indicateIfMenuIsEmpty()) break;

		printMenu();
		removeItemFromMenu();
		break;

	case 14:
		startNewWorkingDay();
		saveDataToAllFiles();
		exit(0);
		break;

	default:
		break;
	}
}

void runApplication()
{
	generateData();
	chooseRole();

	while (true)
	{
		visualizeOptions();
		makeYourChoice();
		completeOption(currentChoice);
	}
}

int main()
{
	runApplication();
}