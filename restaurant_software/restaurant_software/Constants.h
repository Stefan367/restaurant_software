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

#endif