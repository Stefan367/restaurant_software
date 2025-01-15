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