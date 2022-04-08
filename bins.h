#ifndef LAB3_STRUCTURES_BINS_H
#define LAB3_STRUCTURES_BINS_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

struct Bin{
    string partName;
    int partInventory;
};

/*****************************************************************************
 * displayInventory
 * This function reads and outputs the input file name and reads the parts and
 * the quantities for said parts to the screen.
*****************************************************************************/
void displayInventory(ifstream &is, Bin b[]);

/*****************************************************************************
 * menu
 * This function prompts the user for certain choices, either add a new item,
 * select a bin where an item already exists or quit the program entirely. Once
 * an inventory bin is selected the function will prompt the user to add or
 * remove parts from said bin.
*****************************************************************************/
void menu(string &binSelection, Bin b[], ifstream &is, ofstream &os,
          string originalList[]);

/*****************************************************************************
 * AddParts
 * This function adds parts to the chosen inventory in which the user selected.
*****************************************************************************/
void AddParts(const string& binSelection, Bin b[], ofstream &os);

/*****************************************************************************
 * RemoveParts
 * This function removes parts from the inventory in which the user selected.
*****************************************************************************/
void RemoveParts(const string& binSelection, Bin b[], ofstream &os);

/*****************************************************************************
 * AddItem
 * This function adds an item to the inventory list as well as adds the quantity
 * of that item respectively.
*****************************************************************************/
void AddItem(Bin b[], ofstream &os);


#endif //LAB3_STRUCTURES_BINS_H
