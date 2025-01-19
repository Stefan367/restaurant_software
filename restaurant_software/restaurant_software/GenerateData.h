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



// Functions that read the data from the files when the program starts running

void createFilesIfNotGeneratedYet() {

    for (size_t i = 0; i < FILENAMES.size(); ++i) {

        string filename = FILENAMES[i];
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
    vector<string> lineParts = splitString(line, '-');

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
    if (!isDoublePositiveOrZeroForDailyReports(totalAmount)) return;

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
    if (filename == MENU_FILE_NAME) fileToReadFrom = 1;
    else if (filename == STORAGE_FILE_NAME) fileToReadFrom = 2;
    else if (filename == ORDERS_FILE_NAME) fileToReadFrom = 3;
    else if (filename == DAILY_REPORTS_FILE_NAME) fileToReadFrom = 4;

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


// Functions that save the updated data in the files


// Create the line with the right format for the menu.txt file
string structureDataForMenuFile(FoodItem food)
{
    string currLine = "";
    currLine += food.name + ";";

    for (size_t j = 0; j < food.ingridients.size(); ++j)
    {
        Ingridients ing = food.ingridients[j];
        currLine += ing.name + "-" + to_string(ing.quantity);

        if (j < food.ingridients.size() - 1)
        {
            currLine += ",";
        }
    }

    currLine += ";" + to_string(food.price);

    return currLine;
}

void saveTheDataInTheMenuFile(ofstream& file)
{
    string currMenuLine = "";
    FoodItem currFood;
    for (size_t i = 0; i < menu.size(); i++)
    {
        currFood = menu[i];
        currMenuLine = structureDataForMenuFile(currFood);
        file << currMenuLine << "\n";
    }
}

// Create the line with the right format for the storage.txt file
string structureDataForStorageFile(Storage product)
{
    string currLine = "";
    string productName = product.product;
    int quantity = product.availableQuantity;

    if (!isNameValid(productName)) return "";
    if (!isIntPositive(quantity)) return "";

    currLine += productName + "-" + to_string(quantity);

    return currLine;
}

void saveTheDataInTheStorageFile(ofstream& file)
{
    string currStorageLine = "";
    Storage currProduct;
    for (size_t i = 0; i < storage.size(); i++)
    {
        currProduct = storage[i];
        currStorageLine = structureDataForStorageFile(currProduct);
        file << currStorageLine << "\n";
    }
}

// Create the line with the right format for the orders.txt file
string structureDataForOrdersFile(Order order)
{
    string currLine = "";
    string productName = order.productName;
    string date = order.date;

    if (!isNameValid(productName)) return "";
    if (!isValidDate(date)) return "";

    currLine += productName + "=" + date;

    return currLine;
}

void saveTheDataInTheOrdersFile(ofstream& file)
{
    string currOrderLine = "";
    Order currOrder;
    for (size_t i = 0; i < orders.size(); i++)
    {
        currOrder = orders[i];
        currOrderLine = structureDataForOrdersFile(currOrder);
        file << currOrderLine << "\n";
    }
}

// Create the line with the right format for the dailyReports.txt file
string structureDataForDailyReportsFile(DailyReport dailyReport)
{
    string currLine = "";
    string date = dailyReport.date;
    double totalSales = dailyReport.totalAmount;

    if (!isValidDate(date)) return "";
    if (!isDoublePositiveOrZeroForDailyReports(totalSales)) return "";

    currLine += date + "=" + to_string(totalSales);

    return currLine;
}

void saveTheDataInTheDailyReportsFile(ofstream& file)
{
    string currDailyReportLine = "";
    DailyReport currDailyReport;
    for (size_t i = 0; i < dailyReports.size(); i++)
    {
        currDailyReport = dailyReports[i];
        currDailyReportLine = structureDataForDailyReportsFile(currDailyReport);
        file << currDailyReportLine << "\n";
    }
}

void generateData()
{
    createFilesIfNotGeneratedYet();
    readDataFromFile(MENU_FILE_NAME);
    readDataFromFile(STORAGE_FILE_NAME);
    readDataFromFile(ORDERS_FILE_NAME);
    readDataFromFile(DAILY_REPORTS_FILE_NAME);

    addFirstWorkDay();
}

void saveDataToAllFiles()
{
    string filename = "";

    for (size_t i = 0; i < FILENAMES.size(); i++)
    {
        filename = FILENAMES[i];
        ofstream file(filename);

        if (!file)
        {
            cout << "Error: Could not open file " << filename << " for writing." << endl;
            return;
        }

        if (filename == MENU_FILE_NAME)
        {
            saveTheDataInTheMenuFile(file);
        }
        else if (filename == STORAGE_FILE_NAME)
        {
            saveTheDataInTheStorageFile(file);
        }
        else if (filename == ORDERS_FILE_NAME)
        {
            saveTheDataInTheOrdersFile(file);
        }
        else if (filename == DAILY_REPORTS_FILE_NAME)
        {
            saveTheDataInTheDailyReportsFile(file);
        }

        file.close();
        cout << "File saved successfully: " << filename << endl;
    }
}


#endif
