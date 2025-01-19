// restaurant_software.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// proekt_restorant_beta.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

//#include "HelperFunctions.h"
//#include "Constants.h"
#include "UserMenu.h"
#include "MainFunctions.h"

void completeOption(unsigned int choice)
{
	string order;
	string storageProduct;
	switch (choice)
	{
	case 1:
		printMenu();
		break;

	case 2:
		// Clear the console if there is something you do not need
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "What would you like to order: ";
		getline(cin, order);
		orderFoodFromTheMenu(order);
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
		while (storageProduct.empty())
		{
			storageProduct = getValidStringFromConsole(REMOVE_PRODUCT_FROM_STORAGE_MESSAGE);
		}
		removeProductFromStorage(storageProduct);
		break;

	case 9:
		break;

	case 10:
		//startNewWorkingDay();
		break;

	case 11:
		break;

	case 12:
		break;

	case 13:
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