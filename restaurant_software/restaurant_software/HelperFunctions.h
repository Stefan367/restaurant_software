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
* Defines helper functions for manipulating data
*
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
using namespace std;

#include "Constants.h"

bool doesElementContainsInAnArray(unsigned int element, const int arr[], const unsigned int size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == element) return true;
	}
	return false;
}


bool isDigit(const char ch)
{
	return (ch >= '0' && ch <= '9') ? true : false;
}

bool isLetter(const char ch)
{
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? true : false;
}

bool isNumber(const string& str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!isDigit(str[i])) return false;
	}
	return true;
}

int charToInt(const char ch)
{
	if (ch >= '0' && ch <= '9') return ch - '0';
	else return -1;
}

int stringToInt(const string& str)
{
	int result = 0;
	size_t i = 0;

	if (str.empty())
	{
		cout << "Invalid data for integer.";
	}

	// Check for negative sign
	if (str[0] == '-')
	{
		cout << "Negative intiger trying to be added";
		return -1;
	}

	// Check each character
	for (size_t i = 0; i < str.size(); ++i)
	{
		char ch = str[i];

		int digit = charToInt(ch);

		if (digit < 0)
		{
			cout << "Invalid characters in the number";
			return -1;
		}

		result = result * 10 + digit;

		if (result < 0)
		{
			// Overflow detection for signed int
			return -1;
		}
	}

	return result;
}

double stringToDouble(const string& str)
{
	double result = 0.0;
	double fractionalPart = 0.0;
	bool isFraction = false;
	double divisor = 10.0;

	if (str.empty())
	{
		cout << "Input string is empty";
		return -1.0;
	}

	if (str[0] == '-')
	{
		cout << "Negative price is trying to be added";
	}

	// Process each character
	for (size_t i = 0; i < str.size(); ++i) {
		char ch = str[i];

		if (ch == '.') {
			if (isFraction)
			{
				cout << "Invalid input: multiple decimal points";
				return -1.0;
			}
			// Start processing fractional part
			isFraction = true;
			continue;
		}

		int digit = charToInt(ch);

		if (digit < 0)
		{
			cout << "Invalid characters in the number";
			return -1.0;
		}

		if (!isFraction)
		{
			// Build the integer part
			result = result * 10.0 + digit;
		}
		else
		{
			// Build the fractional part
			fractionalPart += digit / divisor;
			divisor *= 10.0; // Move to the next decimal place
		}
	}
	result += fractionalPart;

	return result;
}

string intToString(int value, const int width)
{
	string result = to_string(value);

	while (result.length() < width)
	{
		result = "0" + result;
	}
	return result;
}

string intToValidDateFormatString(int value, int width)
{
	string result = to_string(value);

	while (result.length() < width)
	{
		result = "0" + result;
	}
	return result;
}

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isDateWithValidFormat(const string date)
{
	return (date.length() == 10 && date[2] == '-' && date[5] == '-');
}

string generateNextDay(const string& date)
{

	vector<int> daysInMonth = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	// Parse the date
	if (!isDateWithValidFormat(date))
	{
		cout << "Invalid date format: " << date << endl;
		return "";
	}

	int day = stringToInt(date.substr(0, DAYS_STRING_LENGTH));
	int month = stringToInt(date.substr(3, MONTH_STRING_LENGTH));
	int year = stringToInt(date.substr(6, YEAR_STRING_LENGTH));

	// February days count case
	if (isLeapYear(year))
	{
		daysInMonth[1] = 29;
	}

	day++;

	// Check if the day gets bigger than the days in the current month
	if (day > daysInMonth[month - 1])
	{
		day = 1;
		month++;

		// Check if month gets into a new year
		if (month > 12) {
			month = 1;
			year++;
		}
	}

	// Format the new date
	string newDate = intToString(day, DAYS_STRING_LENGTH) + "-"
		+ intToString(month, MONTH_STRING_LENGTH) + "-"
		+ intToString(year, YEAR_STRING_LENGTH);

	return newDate;
}

vector<string> splitString(const string& str, char delimiter)
{
	vector<string> result;
	string token;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == delimiter)
		{
			if (!token.empty())
			{
				result.push_back(token);
			}
			// Reset token
			token.clear();
		}
		else
		{
			// Append character to the current token till you find delimiter
			token += str[i];
		}
	}

	// Add the last token if it is not empty
	if (!token.empty())
	{
		result.push_back(token);
	}

	return result;
}

bool containsNumbers(const string& str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (isDigit(str[i]))
		{
			return true;
		}
	}
	return false;
}

bool containsOnlyLetters(const string& str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!isLetter(str[i]) && str[i] != ' ')
		{
			return false;
		}
	}
	return true;
}

void giveStringDefaultValue(string& str)
{
	str = "";
}

void giveIntDefaultValue(int& number)
{
	number = 0;
}

void giveDoubleDefaultValue(double& floatingNumber)
{
	floatingNumber = 0.0;
}

#endif
