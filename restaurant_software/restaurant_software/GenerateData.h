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
* Generates the data needed for the project
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#ifndef GENERATEDATA_H
#define GENERATEDATA_H
using namespace std;

#include "Structures.h"
//#include "HelperFunctions.h"
#include "ValidateData.h"

vector<FoodItem> menu;
vector<Storage> storage;
vector<Order> orders;
vector<DailyReport> dailyReports;

void createFilesIfNotGeneratedYet() {
    vector<string> filenames = {
        "menu.txt",
        "orders.txt",
        "storage.txt",
        "dailyReports.txt"
    };

    for (size_t i = 0; i < filenames.size(); ++i) {

        string filename = filenames[i];
        ofstream file(filename, ios::app);

        if (!file)
        {
            cout << "Error: Could not create or open file: " << filename << endl;
            return;
        }

        file.close();
    }
}

void parseMenuLine(const string& line)
{
    vector<string> lineParts = splitString(line, ';');

    if (lineParts.size() != MENU_ITEM_FEATURES_COUNT)
    {
        cout << "Invalid line format: " << line << endl;
        return;
    }

    string foodName = lineParts[0];
    string ingridients = lineParts[1];
    double price = stringToDouble(lineParts[2]);

    if (!isNameValid(foodName)) return;
    if (!isDoublePositive(price)) return;

    // Parse ingridients
    vector<Ingridients> ingridientsList;

    vector<string> ingridientParts = splitString(ingridients, ',');
    for (size_t i = 0; i < ingridientParts.size(); i++)
    {
        string currIngridient = ingridientParts[i];

        vector<string> currIngridientParts = splitString(currIngridient, '-');
        if (currIngridientParts.size() != 2)
        {
            cout << "Invalid ingridient format: " << currIngridient << endl;
            return;
        }

        string ingName = currIngridientParts[0];;
        int quantity = stringToInt(currIngridientParts[1]);

        if (!isNameValid(ingName)) return;
        if (!isIntPositive(quantity)) return;

        Ingridients ing;
        ing.name = ingName;
        ing.quantity = quantity;

        ingridientsList.push_back(ing);
    }
    FoodItem foodItem;
    foodItem.name = foodName;
    foodItem.ingridients = ingridientsList;
    foodItem.price = price;
    menu.push_back(foodItem);
}

void parseStorageLine(const string& line)
{
    vector<string> lineParts = splitString(line, ' ');

    if (lineParts.size() != STORAGE_PRODUCT_FEATURES_COUNT)
    {
        cout << "Invalid line format: " << line << endl;
        return;
    }

    string productName = lineParts[0];
    int availableQuantity = stringToInt(lineParts[1]);

    if (!isNameValid(productName)) return;
    if (!isIntPositive(availableQuantity)) return;

    Storage currProduct;
    currProduct.product = productName;
    currProduct.availableQuantity = availableQuantity;
    storage.push_back(currProduct);
}

void parseOrderLine(const string& line)
{
    vector<string> lineParts = splitString(line, '=');

    if (lineParts.size() != ORDERS_FEATURES_COUNT)
    {
        cout << "Invalid line format: " << line << endl;
        return;
    }

    string productName = lineParts[0];
    string date = lineParts[1];

    if (!isNameValid(productName)) return;
    if (!isValidDate(date))
    {
        cout << "Invalid date format: " << date << endl;
    }

    Order order;
    order.productName = productName;
    order.date = date;
    orders.push_back(order);
}

void parseDailyReportLine(const string& line)
{
    vector<string> lineParts = splitString(line, '=');

    if (lineParts.size() != DAILY_REPORTS_FEATURES_COUNT)
    {
        cout << "Invalid line format: " << line << endl;
        return;
    }

    string date = lineParts[0];
    double totalAmount = stringToDouble(lineParts[1]);

    if (!isValidDate(date))
    {
        cout << "Invalid date format: " << date << endl;
        return;
    }
    if (!isDoublePositive(totalAmount)) return;

    DailyReport dailyReport;
    dailyReport.date = date;
    dailyReport.totalAmount = totalAmount;
    dailyReports.push_back(dailyReport);
}


// Function to read data from all text files
void readDataFromFile(string filename)
{
    ifstream file(filename);
    if (!file)
    {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    unsigned int fileToReadFrom = 0;
    if (filename == "menu.txt") fileToReadFrom = 1;
    else if (filename == "storage.txt") fileToReadFrom = 2;
    else if (filename == "orders.txt") fileToReadFrom = 3;
    else if (filename == "dailyReports.txt") fileToReadFrom = 4;

    string line;
    while (getline(file, line))
    {
        switch (fileToReadFrom)
        {
        case 1:
            parseMenuLine(line);
            break;

        case 2:
            parseStorageLine(line);
            break;

        case 3:
            parseOrderLine(line);
            break;

        case 4:
            parseDailyReportLine(line);
            break;
        default:
            break;
        }
    }

    file.close();
}

void addFirstWorkDay()
{
    if (!dailyReports.size())
    {
        const string firstWorkDay = "01-01-2025";
        double dailySales = 0.0;

        DailyReport firstDailyReport;
        firstDailyReport.date = firstWorkDay;
        firstDailyReport.totalAmount = dailySales;
        dailyReports.push_back(firstDailyReport);
    }
}


void generateData()
{
    createFilesIfNotGeneratedYet();
    readDataFromFile("menu.txt");
    readDataFromFile("storage.txt");
    readDataFromFile("orders.txt");
    readDataFromFile("dailyReports.txt");
}

#endif
