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
* Defines structures about all the items that will be used in the project
*
*/

#include <iostream>
#include <string>
#include <vector>
#ifndef STRUCTURES_H
#define STRUCTURES_H
using namespace std;

struct Ingridients
{
	string name;
	int quantity;
};

struct FoodItem
{
	string name;
	vector<Ingridients> ingridients;
	double price;
};

struct Order
{
	string productName;
	string date;
};

struct Storage
{
	string product;
	int availableQuantity;
};

struct DailyReport
{
	string date;
	double totalAmount;
};


#endif