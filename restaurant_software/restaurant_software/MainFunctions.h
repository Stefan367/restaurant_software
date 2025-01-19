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

// Check if vectors are empty
bool areThereNoOrders()
{
    return orders.empty();
}

bool isTheStorageEmpty()
{
    return storage.empty();
}

bool areThereNoDailyReports()
{
    return dailyReports.empty();
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
    bool foundInStorage = false;

    Storage currProduct;
    for (size_t i = 0; i < storage.size(); i++)
    {
        currProduct = storage[i];

        if (isStorageItemEmpty(currProduct)) return false;

        if (ingridient.name == currProduct.product)
        {
            foundInStorage = true;
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
    if (!foundInStorage)
    {
        cout << "Product " << ingridient.name << " not found in storage." << endl;
    }

    return false;
}

// Add the quantity of ingridients if an order is canceled
void addUnusedIngridientsInStorage(FoodItem& meal)
{
    for (const auto& ingridient : meal.ingridients)
    {
        for (auto& product : storage)
        {
            if (product.product == ingridient.name)
            {
                product.availableQuantity += ingridient.quantity;
                cout << "Restocked " << ingridient.quantity << " g of " << product.product
                    << " (new total: " << product.availableQuantity << " g)." << std::endl;
            }
        }
    }
}

// Substract the quantity of ingridients if an order is made
void substractUnusedIngridientsInStorage(FoodItem& meal)
{
    for (const auto& currIngridient : meal.ingridients)
    {
        for (auto& currProductToUse : storage)
        {
            if (currIngridient.name == currProductToUse.product)
            {
                currProductToUse.availableQuantity -= currIngridient.quantity;
            }
        }
    }
}

// Remove the needed quantity of each product to prepare a meal
bool prepareMeal(FoodItem& meal)
{
    if (isFoodItemEmpty(meal))
    {
        cout << "Invalid meal!" << endl;
        return false;
    }

    vector<Ingridients> currProductIngridients = meal.ingridients;
    bool canPrepare = true;

    // Check if all ingredients are available in the storage
    for (const auto& currIngridient : currProductIngridients)
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

    // Deduct quantities from storage
    substractUnusedIngridientsInStorage(meal);

    cout << "Meal " << meal.name << " prepared successfully." << endl;
    return true;
}

void updateDailyReport(const double mealPrice)
{
    if (areThereNoDailyReports())
    {
        cout << "Warning: No daily report available to update the total amount." << endl;
        return;
    }
    dailyReports.back().totalAmount += mealPrice;
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

// Cancel order
void cancelLastOrder()
{
    string today = getTodaysDate();
    if (areThereNoOrders() || orders.back().date != today)
    {
        cout << "No orders to cancel or there are no orders for today!" << endl;
        return;
    }

    // Get the last order
    string lastOrder = orders.back().productName;

    orders.pop_back();

    // Find the meal in the menu
    FoodItem meal = takeAMealFromTheMenu(lastOrder);
    if (isFoodItemEmpty(meal))
    {
        cout << "Error: Meal not found in the menu!" << endl;
        return;
    }

    // Add quantities back to the storage
    addUnusedIngridientsInStorage(meal);

    // Subtract the meal price from today's daily report
    if (areThereNoDailyReports())
    {
        cout << "Warning: No daily report to update!" << endl;
        return;
    }
    dailyReports.back().totalAmount -= meal.price;

    cout << "Order for " << lastOrder << " has been successfully canceled." << endl;
}

// View all previous orders
void viewAllOrders()
{
    if (areThereNoOrders())
    {
        cout << "There are no previous orders." << endl;
        return;
    }
    Order currOrder;
    for (size_t i = 0; i < orders.size(); i++)
    {
        currOrder = orders[i];
        cout << currOrder.productName << " <--> " << currOrder.date << "." << endl;
    }
}

// Show all orders sorted and with the count of orders for each meal

// Function to create a sorted temporary vector
void swapOrders(Order& order1, Order& order2)
{
    Order temp = order1;
    order1 = order2;
    order2 = temp;
}

vector<Order> getSortedOrders(const vector<Order>& orders)
{
    vector<Order> sortedOrders = orders;

    // Sort orders with Bubble Sort
    for (size_t i = 0; i < sortedOrders.size(); ++i)
    {
        for (size_t j = 0; j < sortedOrders.size() - i - 1; ++j)
        {
            if (sortedOrders[j].productName > sortedOrders[j + 1].productName)
            {
                swapOrders(sortedOrders[j], sortedOrders[j + 1]);
            }
        }
    }
    return sortedOrders;
}

// Function to display meals only once with their order counts
void viewMealsSortedAndWithCounts()
{
    if (areThereNoOrders())
    {
        cout << "There are no orders.";
        return;
    }

    vector<Order> sortedOrders = getSortedOrders(orders);

    // Iterate through the sorted orders and count each meal
    string currentMeal = "";
    int count = 0;

    for (size_t i = 0; i < sortedOrders.size(); ++i)
    {
        if (sortedOrders[i].productName != currentMeal)
        {
            // If there is a diffrent meal, print the previous meal and reset count
            if (!currentMeal.empty())
            {
                cout << currentMeal << " - Total orders: " << count << endl;
            }
            currentMeal = sortedOrders[i].productName;
            count = 1;
        }
        else
        {
            count++;
        }
    }

    // Print the last meal
    if (!currentMeal.empty())
    {
        cout << currentMeal << " - Total orders: " << count << endl;
    }
}

// Show the Daily Report for today
void showTodaysDailyReport()
{
    if (areThereNoDailyReports())
    {
        cout << "There are no daily reports." << endl;
        return;
    }

    const DailyReport todaysDailyReport = dailyReports.back();

    cout << "The daily sales for today ("
        << todaysDailyReport.date << ") are "
        << todaysDailyReport.totalAmount << " BGN" << endl;
}

#endif