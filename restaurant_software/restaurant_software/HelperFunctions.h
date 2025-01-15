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

bool doesElementContainsInAnArray(unsigned int element, const int arr[], const unsigned int size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (arr[i] == element) return true;
	}
	return false;
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
		cout << "Invalid data for quantity.";
	}

	// Check for negative sign
	if (str[0] == '-')
	{
		cout << "Negative quantity trying to be added";
		return -1;
	}

	// Process each character
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

#endif
