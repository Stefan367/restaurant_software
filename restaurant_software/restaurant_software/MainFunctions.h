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
    return ing.name.empty() || !ing.quantity;
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

bool isMenuEmpty()
{
    return menu.empty();
}

bool indicateIfStorageIsEmpty()
{
    if (isTheStorageEmpty())
    {
        cout << "There is nothing left in the storage." << endl;
        return false;
    }
    return true;
}

bool indicateIfMenuIsEmpty()
{
    if (isMenuEmpty())
    {
        cout << "There is nothing in the menu." << endl;
        return false;
    }
    return true;
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
    if (!indicateIfMenuIsEmpty()) return;

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
                    << " (available: " << currProduct.availableQuantity << " g)" << endl;
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

    printNewLine();
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

void orderFoodFromTheMenu()
{
    const string order = getValidStringFromConsole(MAKE_AN_ORDER_MESSAGE);
    
    if (!isNameValid(order)) return;

    if (!doesMenuHasGivenMeal(order))
    {
        printNewLine();
        cout << "There is not " << order << " in the menu." << endl;
        return;
    }

    FoodItem orderedMeal = takeAMealFromTheMenu(order);
    if (!prepareMeal(orderedMeal))
    {
        return;
    }
    addNewOrderToAllOrders(orderedMeal.name);
    updateDailyReport(orderedMeal.price);

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
        printNewLine();
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
    cout << endl << "All previous orders are:" << endl;

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

    printNewLine();
    cout << "Alphabetically sorted orders:" << endl;
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

    printNewLine();
    cout << "The daily sales for today ("
        << todaysDailyReport.date << ") are "
        << todaysDailyReport.totalAmount << " BGN" << endl;
}

// View data in storage
void viewWhatHadLeftInTheStorage()
{
    if (isTheStorageEmpty())
    {
        cout << "There is nothing left in the storage." << endl;
    }

    printNewLine();
    cout << "The storage contains: " << endl;

    for (size_t i = 0; i < storage.size(); i++)
    {
        cout << storage[i].product << " - " << storage[i].availableQuantity << " g" << endl;
    }
}

// Remove a given product from storage
void removeProductFromStorage()
{
    const string storageProductName = getValidStringFromConsole(REMOVE_PRODUCT_FROM_STORAGE_MESSAGE);

    if (!indicateIfStorageIsEmpty()) return;

    for (size_t i = 0; i < storage.size(); ++i)
    {
        if (storage[i].product == storageProductName)
        {
            storage.erase(storage.begin() + i);
            cout << "Product " << storageProductName << " removed from storage." << endl;
            return;
        }
    }

    cout << "Product " << storageProductName << " not found in storage." << endl;
}

// Add product to storage or increase quantity if it already exists
bool increaseProductQuantity(const string& storageProduct, const int& quantity)
{
    for (auto& item : storage)
    {
        if (item.product == storageProduct)
        {
            item.availableQuantity += quantity;
            cout << "Increased quantity of " << storageProduct << " by " << quantity
                << " g. Total: " << item.availableQuantity << " g." << endl;
            return true;
        }
    }
    return false;
}

void addProductInStorage()
{
    const string storageProduct = getValidStringFromConsole(ADD_PRODUCT_TO_STORAGE_MESSAGE);
    const int quantity = getValidIntigerFromConsole(PRODUCT_QUANTITY_MESSAGE);
    

    if (!isNameValid(storageProduct)) return;

    if (!isIntPositive(quantity))
    {
        cout << "Quantity must be greater than 0." << endl;
        return;
    }

    printNewLine();
    // Check if the product already exists in the storage
    if (increaseProductQuantity(storageProduct, quantity))
    {
        return;
    }

    // If the product does not exist, add it as a new entry
    storage.push_back({ storageProduct, quantity });
    cout << "New product added in storage: " << storageProduct << " with quantity: "
        << quantity << " g." << endl;
}

// Make a daily report
void makeDailyReport()
{
    printNewLine();

    if (areThereNoDailyReports())
    {
        cout << "There are no daily reports." << endl;
        return;
    }

    // Show the daily report for today
    const DailyReport todaysDailyReport = dailyReports.back();

    cout << "The daily report for today is: " << todaysDailyReport.date << " -> "
        << todaysDailyReport.totalAmount << " BGN" << endl;

    // Create the daily report for the new day
    startNewWorkingDay();
}

// View all daily reports from a given date to today

// Get the index of the first daily report with the given date
int getIndexOfTheFirstDailyReportWithDate(const string& date)
{
    for (size_t i = 0; i < dailyReports.size(); i++)
    {
        if (dailyReports[i].date == date)
        {
            return  i;
        }
    }
    return 0;
}

void showDailyReportsFromGivenDateToToday()
{
    const string date = getValidDateFromConsole(VALIDATE_DATE_MESSAGE);
    printNewLine();

    if (!isValidDate(date))
    {
        cout << "Invalid date: " << date << endl;
        return;
    }

    int indexToStartFrom = getIndexOfTheFirstDailyReportWithDate(date);

    if (!indexToStartFrom)
    {
        cout << "There are no daily reports with the given date." << endl;
        return;
    }

    cout << "Daily Reports from " << date << " to " << getTodaysDate() << " :" << endl;

    for (size_t i = indexToStartFrom; i < dailyReports.size(); i++)
    {
        cout << dailyReports[i].date << " - " << dailyReports[i].totalAmount << " BGN" << endl;
    }
}

// Add new item in the menu
bool getValidDataForMenuItem(string& itemName, vector<Ingridients>& ingredients, double& price)
{
    itemName = getValidStringFromConsole(ADD_NAME_OF_MENU_ITEM);

    // Check if the item already exists
    if (doesMenuHasGivenMeal(itemName))
    {
        cout << "Item " << itemName << " already exists in the menu." << endl;
        return false;
    }

    // Input number of ingredients
    int numIngridients = getValidIntigerFromConsole(ADD_NUMBER_OF_INGRIDIENTS_OF_MENU_ITEM);
    for (int i = 1; i <= numIngridients; ++i)
    {
        Ingridients ing;
        cout << i << ". ";
        ing.name = getValidStringFromConsole(ADD_INGRIDIENT_NAME_OF_MENU_ITEM);

        cout << i << ". ";
        ing.quantity = getValidIntigerFromConsole(ADD_INGRIDIENT_QUANTITY_OF_MENU_ITEM);

        ingredients.push_back(ing);
    }

    // Input price
    price = getValidDoubleFromConsole(ADD_PRICE_OF_MENU_ITEM);

    return true;
}

void addMenuItem()
{
    string itemName;
    vector<Ingridients> ingredients;
    double price = 0.0;

    if (!getValidDataForMenuItem(itemName, ingredients, price)) return;

    if (!isNameValid(itemName)) return;

    printNewLine();
    if (ingredients.empty())
    {
        cout << "The menu item must have at least one ingredient." << endl;
        return;
    }

    if (!isDoublePositive(price)) return;

    menu.push_back({ itemName, ingredients, price });
    cout << itemName << " was successfully added to the menu." << endl;
}

// Remove item from the menu
void removeItemFromMenu()
{
    const string mealName = getValidStringFromConsole(REMOVE_ITEM_FROM_MENU_MESSAGE);

    if (!isNameValid(mealName)) return;

    if (!indicateIfMenuIsEmpty()) return;

    printNewLine();

    for (size_t i = 0; i < menu.size(); ++i)
    {
        if (menu[i].name == mealName)
        {
            menu.erase(menu.begin() + i);
            cout << "Item " << mealName << " removed from menu." << endl;
            return;
        }
    }

    cout << "Item " << mealName << " not found in menu." << endl;
}

#endif