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
* Here are the main functionalities for the projrct
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H
using namespace std;

#include "GenerateData.h"
#include "Constants.h"

bool isFoodItemEmpty(const FoodItem& meal)
{
    return meal.name.empty() || meal.ingridients.empty();
}

bool isIngridientItemEmpty(const Ingridients& ing)
{
    return ing.name.empty();
}

bool isStorageItemEmpty(const Storage& item)
{
    return item.product.empty();
}

void startNewWorkingDay()
{
    DailyReport currentWorkingDay = dailyReports.back();
    const string today = currentWorkingDay.date;
    const string newDay = generateNextDay(today);

    if (!isDateWithValidFormat(today) || !isDateWithValidFormat(newDay))
    {
        cout << "Invalid date format!" << endl;
        return;
    }

    double newDailySales = 0.0;
    DailyReport newWorkDay;
    newWorkDay.date = newDay;
    newWorkDay.totalAmount = newDailySales;
    dailyReports.push_back(newWorkDay);
}

// Function to print the menu
void printMenu()
{
    cout << endl << "-------- M E N U --------" << endl;

    for (size_t i = 0; i < menu.size(); ++i)
    {
        FoodItem food = menu[i];
        cout << "Food: " << food.name << "\nIngredients:\n";

        for (size_t j = 0; j < food.ingridients.size(); ++j)
        {
            cout << "  - " << food.ingridients[j].name << ": " << food.ingridients[j].quantity << "g\n";
        }
        cout << "Price: " << food.price << " BGN\n" << endl;
    }
}

#endif