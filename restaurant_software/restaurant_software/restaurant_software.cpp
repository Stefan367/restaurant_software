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
	case CHOICE_1_SHOW_MENU:
		printMenu();
		break;

	case CHOICE_2_MAKE_ORDER:
		orderFoodFromTheMenu();
		break;

	case CHOICE_3_CANCEL_ORDER:
		cancelLastOrder();
		break;

	case CHOICE_4_PREVIOUS_ORDERS:
		viewAllOrders();
		break;

	case CHOICE_5_SORTED_ORDER:
		viewMealsSortedAndWithCounts();
		break;

	case CHOICE_6_DAILY_SALES:
		showTodaysDailyReport();
		break;

	case CHOICE_7_CLOSE_OR_STORAGE:
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

	case CHOICE_8_REMOVE_PRODUCT:
		viewWhatHadLeftInTheStorage();
		removeProductFromStorage();
		break;

	case CHOICE_9_ADD_PRODUCT:
		viewWhatHadLeftInTheStorage();
		addProductInStorage();
		break;

	case CHOICE_10_MAKE_REPORT:
		makeDailyReport();
		break;

	case CHOICE_11_REPORTS_FROM_DATE:
		showDailyReportsFromGivenDateToToday();
		break;

	case CHOICE_12_ADD_MENU_ITEM:
		addMenuItem();
		break;

	case CHOICE_13_REMOVE_MENU_ITEM:
		if (!indicateIfMenuIsEmpty()) break;

		printMenu();
		removeItemFromMenu();
		break;

	case CHOICE_14_CLOSE_APP:
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