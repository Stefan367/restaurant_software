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
	switch (choice)
	{
	case 1:
		printMenu();
		break;

	case 2:
		break;

	case 3:
		break;

	case 4:
		break;

	case 5:
		break;

	case 6:
		break;

	case 7:
		if (!userRole)
		{
			startNewWorkingDay();
			saveDataToAllFiles();
			exit(0);
		}
		break;

	case 8:
		break;

	case 9:
		break;

	case 10:
		startNewWorkingDay();
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