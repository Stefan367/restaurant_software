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
#include "HelperFunctions.h"

vector<FoodItem> menu;
vector<Storage> storage;


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

    if (lineParts.size() != 3)
    {
        cout << "Invalid line format: " << line << endl;
        return;
    }

    string foodName = lineParts[0];
    string ingridients = lineParts[1];
    double price = stringToDouble(lineParts[2]);

    if (price < 0.0) return;

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

        Ingridients ing;
        ing.name = currIngridientParts[0];
        ing.quantity = stringToInt(currIngridientParts[1]);

        if (ing.quantity < 0)
        {
            return;
        }

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

    if (lineParts.size() != 2)
    {
        cout << "Invalid line format: " << line << endl;
        return;
    }

    string productName = lineParts[0];
    int availableQuantity = stringToInt(lineParts[1]);

    if (availableQuantity < 0)
    {
        return;
    }

    Storage currProduct;
    currProduct.product = productName;
    currProduct.availableQuantity = availableQuantity;
    storage.push_back(currProduct);
}

// Function to read data from menu.txt
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
            break;

        case 4:
            break;
        default:
            break;
        }
    }

    file.close();
}


void generateData()
{
    createFilesIfNotGeneratedYet();
    readDataFromFile("menu.txt");
    readDataFromFile("storage.txt");
}

#endif
