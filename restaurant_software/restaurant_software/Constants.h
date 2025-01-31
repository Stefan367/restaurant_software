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

const int CHOICE_1_SHOW_MENU = 1;
const int CHOICE_2_MAKE_ORDER = 2;
const int CHOICE_3_CANCEL_ORDER = 3;
const int CHOICE_4_PREVIOUS_ORDERS = 4;
const int CHOICE_5_SORTED_ORDER = 5;
const int CHOICE_6_DAILY_SALES = 6;
const int CHOICE_7_CLOSE_OR_STORAGE = 7;
const int CHOICE_8_REMOVE_PRODUCT = 8;
const int CHOICE_9_ADD_PRODUCT = 9;
const int CHOICE_10_MAKE_REPORT = 10;
const int CHOICE_11_REPORTS_FROM_DATE = 11;
const int CHOICE_12_ADD_MENU_ITEM = 12;
const int CHOICE_13_REMOVE_MENU_ITEM = 13;
const int CHOICE_14_CLOSE_APP = 14;

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
const string REMOVE_PRODUCT_FROM_STORAGE_MESSAGE = "Enter the name of the product you want to remove: ";
const string ADD_PRODUCT_TO_STORAGE_MESSAGE = "Enter the name of the product you want to add: ";
const string PRODUCT_QUANTITY_MESSAGE = "Enter the product quantity: ";
const string VALIDATE_DATE_MESSAGE = "Enter the date you want daily reports from: ";
const string REMOVE_ITEM_FROM_MENU_MESSAGE = "Enter the item from the menu you want to delete: ";
const string ADD_NAME_OF_MENU_ITEM = "Enter the name of the new menu item: ";
const string ADD_NUMBER_OF_INGRIDIENTS_OF_MENU_ITEM = "Enter the number of ingredients: ";
const string ADD_INGRIDIENT_NAME_OF_MENU_ITEM = "Enter the ingridient name: ";
const string ADD_INGRIDIENT_QUANTITY_OF_MENU_ITEM = "Enter the ingridient quantity: ";
const string ADD_PRICE_OF_MENU_ITEM = "Enter the price of the new menu item: ";


#endif