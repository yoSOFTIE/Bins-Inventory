#include <iostream>
#include "bins.h"
using namespace std;

/*****************************************************************************
*
* Inventory Bins
*________________________________________________
* This program simulates the adding and removing
* parts from an inventory.
*________________________________________________
* INPUT:
*  menuChoice       : The choice that the user chooses to maneuver through the
*                     program.
*  fileName         : The file name that the user wishes to upload to the
*                     program.
*  partsAdded       : The amount of parts the user wants to add to the
*                     respective part name.
*  partsRemoved     : The amount of parts the user want to remove from the
*                     respective part name.
*  partName         : The name of the part in which the user wants to add
*                     to the inventory.
*  partInventory    : The number of parts the user wishes to attribute to the
*                     added partName.
*
*
* OUTPUT:
*  text file        : The updated text file that the user has done manipulations
*                     to via, adding or removing inventory parts for existing
*                     inventory, or adding new part types to the inventory.
******************************************************************************/

int main() {
    // DATA TABLE
    Bin bins[30];               // INOUT: uses to store and
    ifstream inData;            // IN: takes in filestream from specified file
    ofstream outData;           // OUT: used to write out to file.
    string binSelection;        // IN: user input for desired bin
    string fileName;            // IN: input for specified file name
    string originalList[20];    // IN: used to store original data of file to
    //write back to modified file.

    //PROCESS: user input to select file
    cout << "Enter name of inventory file: ";
    cin >> fileName;
    inData.open(fileName);

    //PROCESS: populate array with original data from file
    for(int i = 0; i < 20; i++){
        getline(inData, originalList[i], '\n');
    }
    inData.clear();
    inData.seekg(0, inData.beg);

    // PROCESS: check if file has been opened
    if(inData.is_open()){
        menu(binSelection, bins, inData, outData, originalList);
    }
    else{
        cout << "File is not open";
    }
    inData.close();
    outData.close();
    return 0;
}
