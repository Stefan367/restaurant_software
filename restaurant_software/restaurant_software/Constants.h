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
* Defines constants which are used in the project
*
*/

#include <iostream>
#include <string>
#ifndef CONSTANTS_H
#define CONSTANTS_H
using namespace std;

const unsigned int MAX_SIZE = 100;
const char NEW_LINE = '\n';
bool userRole; // 1 - manager, 0 - waiter
const int VALID_CHOICES_WAITER[] = { 1, 2, 3, 4, 5, 6, 7 };
const unsigned int NUMBER_OF_VALID_CHOICES_FOR_WAITER = 7;
const int VALID_CHOICES_MANAGER[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };
const unsigned int NUMBER_OF_VALID_CHOICES_FOR_MANAGER = 14;
unsigned int currentChoice = 0;

const int MENU_ITEM_FEATURES_COUNT = 3;
const int STORAGE_PRODUCT_FEATURES_COUNT = 2;
const int ORDERS_FEATURES_COUNT = 2;
const int DAILY_REPORTS_FEATURES_COUNT = 2;

const string MENU_FILE_NAME = "menu.txt";
const string STORAGE_FILE_NAME = "storage.txt";
const string ORDERS_FILE_NAME = "orders.txt";
const string DAILY_REPORTS_FILE_NAME = "dailyReports.txt";

const vector<string> FILENAMES = {
    MENU_FILE_NAME,
    ORDERS_FILE_NAME,
    STORAGE_FILE_NAME,
    DAILY_REPORTS_FILE_NAME
};

#endif