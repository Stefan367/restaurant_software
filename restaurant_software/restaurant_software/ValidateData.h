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
* Functions for data validation
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#ifndef ValidateData_H
#define ValidateData_H
using namespace std;

#include "Constants.h"
#include "HelperFunctions.h"

bool isIntPositive(const int n)
{
	if (n < 0)
	{
		cout << "Numbers cannot be negative";
		return false;
	}
	return true;
}

bool isDoublePositive(const double n)
{
	if (n < 0.0)
	{
		cout << "Numbers cannot be negative";
		return false;
	}
	return true;
}

bool isNameValid(const string& name)
{
	if (name.size() < MIN_NAMES_LENGTH || (!containsOnlyLetters(name)))
	{
		cout << "All strings such as product name and menu item name should be "
			<< "at least 3 characters long and contains only letters : " << name << endl;
		return false;
	}
	return true;
}

bool isValidDate(const string& date)
{
	// valid date: 01-01-2025

	if (!isDateWithValidFormat(date))
	{
		cout << "Invalid date format: " << date << endl;
		return false;
	}

	string dayStr = date.substr(0, 2);
	string monthStr = date.substr(3, 2);
	string yearStr = date.substr(6, 4);

	// Validate that day, month, year are numeric
	if (!isNumber(dayStr) || !isNumber(monthStr) || !isNumber(yearStr))
	{
		return false;
	}

	int day = stringToInt(dayStr);
	int month = stringToInt(monthStr);
	int year = stringToInt(yearStr);

	if (month < 1 || month > 12) {
		return false;
	}

	// Days in each month
	vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month == 2 && isLeapYear(year))
	{
		daysInMonth[1] = 29;
	}

	if (day < 1 || day > daysInMonth[month - 1])
	{
		return false;
	}

	return true;
}

// Validate string input from the console until it's valid
string getValidStringFromConsole(const string& prompt)
{
	string input;

	cin.ignore(numeric_limits<streamsize>::max(), NEW_LINE);
	while (true)
	{

		cout << prompt;
		getline(cin, input);

		if (isNameValid(input))
		{
			break;
		}
	}

	return input;
}

#endif