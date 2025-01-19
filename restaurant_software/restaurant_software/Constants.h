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

const int MENU_FILE_NUMBER = 1;
const int STORAGE_FILE_NUMBER = 2;
const int ORDERS_FILE_NUMBER = 3;
const int DAILY_REPORTS_FILE_NUMBER = 4;

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

const int MIN_NAMES_LENGTH = 3;

const int DAYS_STRING_LENGTH = 2;
const int MONTH_STRING_LENGTH = 2;
const int YEAR_STRING_LENGTH = 4;

const string MAKE_AN_ORDER_MESSAGE = "What would you like to order: ";
const string REMOVE_PRODUCT_FROM_STORAGE_MESSAGE = "Enter the product name you want to remove: ";
const string ADD_PRODUCT_TO_STORAGE_MESSAGE = "Enter the product name you want to add: ";
const string PRODUCT_QUANTITY_MESSAGE = "Enter the product quantity: ";
const string VALIDATE_DATE_MESSAGE = "Enter the date you want daily reports from: ";


#endif