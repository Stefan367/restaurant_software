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
#include <string>
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

#endif
