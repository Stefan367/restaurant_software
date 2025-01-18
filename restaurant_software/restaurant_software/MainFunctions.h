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
* Here are the main functionalities for the project
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

// Get the today's date
string getTodaysDate()
{
    string today = dailyReports.back().date;
    return today;
}

void addNewOrderToAllOrders(const string& orderedMeal)
{
    if (!isNameValid(orderedMeal)) return;

    string today = getTodaysDate();

    Order newOrder;
    newOrder.productName = orderedMeal;
    newOrder.date = today;

    orders.push_back(newOrder);
}

// Check if the menu has a given meal
bool doesMenuHasGivenMeal(const string& meal)
{
    if (!isNameValid(meal)) return false;

    FoodItem currFood;
    for (size_t i = 0; i < menu.size(); i++)
    {
        currFood = menu[i];
        if (meal == currFood.name)
        {
            return true;
        }
    }
    return false;
}

// Take a meal from the menu if it exist
FoodItem takeAMealFromTheMenu(const string& meal)
{
    if (!isNameValid(meal)) return { "", {}, 0.0 };

    FoodItem currMeal;
    for (size_t i = 0; i < menu.size(); i++)
    {
        currMeal = menu[i];
        if (meal == currMeal.name)
        {
            break;
        }
    }
    return currMeal;
}

// Check if storage contains a certain product to prepare a meal
bool doesStorageContainsProductForMeal(Ingridients ingridient)
{
    Storage currProduct;
    for (size_t i = 0; i < storage.size(); i++)
    {
        currProduct = storage[i];

        if (isStorageItemEmpty(currProduct)) return false;

        if (ingridient.name == currProduct.product)
        {
            if (ingridient.quantity <= currProduct.availableQuantity)
            {
                return true;
            }
            else
            {
                cout << "Not enough quantity of " << currProduct.product
                    << " (available: " << currProduct.availableQuantity << " g)";
                return false;
            }
        }
    }
}

// Remove the needed quantity of each product to prepare a meal
bool prepareMeal(FoodItem& meal)
{
    if (isFoodItemEmpty(meal))
    {
        cout << "Invalid meal!";
        return false;
    }

    vector<Ingridients> currProductIngridients = meal.ingridients;
    Ingridients currIngridient;
    Storage currProductToUse;

    bool canPrepare = true;

    for (size_t i = 0; i < currProductIngridients.size(); i++)
    {
        if (!doesStorageContainsProductForMeal(currIngridient))
        {
            canPrepare = false;
        }
    }

    if (!canPrepare)
    {
        cout << "Cannot prepare meal " << meal.name << "." << endl;
        return false;
    }

    for (const auto& currIngridient : currProductIngridients)
    {
        // Use reference to modify the original object
        for (auto& currProductToUse : storage)
        {
            if (currIngridient.name == currProductToUse.product)
            {
                currProductToUse.availableQuantity -= currIngridient.quantity;
            }
        }
    }
    cout << "Meal " << meal.name << " prepared successfully." << endl;
    return true;
}

void updateDailyReport(const double mealPrice)
{
    if (!dailyReports.empty())
    {
        dailyReports.back().totalAmount += mealPrice;
    }
    else
    {
        cout << "Warning: No daily report available to update the total amount." << endl;
    }
}


// MAIN FUNCTIONS IN THE APP

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

// Order something from the menu
void orderFoodFromTheMenu(const string& orderedMeal)
{
    if (!isNameValid(orderedMeal)) return;

    if (!doesMenuHasGivenMeal(orderedMeal))
    {
        cout << "There is not " << orderedMeal << " in the menu." << endl;
        return;
    }

    FoodItem order = takeAMealFromTheMenu(orderedMeal);
    if (!prepareMeal(order))
    {
        return;
    }
    addNewOrderToAllOrders(order.name);
    updateDailyReport(order.price);

}

#endif