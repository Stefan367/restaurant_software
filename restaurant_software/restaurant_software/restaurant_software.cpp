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

//#include "HelperFunctions.h"
//#include "Constants.h"
#include "UserMenu.h"
#include "MainFunctions.h"

void completeOption(unsigned int choice)
{
	string storageProduct;
	string date;
	string mealName;
	int quantity = 0;

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

		while (storageProduct.empty())
		{
			storageProduct = getValidStringFromConsole(ADD_PRODUCT_TO_STORAGE_MESSAGE);
		}
		while (quantity <= 0)
		{
			quantity = getValidIntigerFromConsole(PRODUCT_QUANTITY_MESSAGE);
		}
		addProductInStorage(storageProduct, quantity);

		giveStringDefaultValue(storageProduct);
		giveIntDefaultValue(quantity);
		break;

	case 10:
		makeDailyReport();
		break;

	case 11:

		while (date.empty())
		{
			date = getValidDateFromConsole(VALIDATE_DATE_MESSAGE);
		}
		showDailyReportsFromGivenDateToToday(date);

		giveStringDefaultValue(date);
		break;

	case 12:
		addMenuItem();
		break;

	case 13:
		if (!indicateIfMenuIsEmpty()) break;

		printMenu();
		while (mealName.empty())
		{
			mealName = getValidStringFromConsole(REMOVE_ITEM_FROM_MENU_MESSAGE);
		}
		removeItemFromMenu(mealName);

		giveStringDefaultValue(mealName);
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