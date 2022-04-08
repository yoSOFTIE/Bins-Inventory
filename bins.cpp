#include "bins.h"

/*****************************************************************************
 * FUNCTION menu
 *________________________________________________
 * This function prompts the user with a menu
 * filled with choices on how they would like to
 * utilize the program's functionality.
 *_______________________________________________
 * PRE-CONDITIONS
 * The following needs previous defined values:
 * binSelection : the string associated to the selection in which the user
                  makes
 * Bin          : the structure to hold the inventory names and quantities
 * is           : the input stream
 * os           : the output stream
 * originalList : the original state of the imported text file
 *
 * POST-CONDITIONS
 * This function runs the function that is attributed to the selection
 * chosen by the user.
****************************************************************************/
void menu(string &binSelection, Bin b[], ifstream &is, ofstream &os,
          string originalList[]){
    // DATA TABLE
    char menuChoice = 0;            // IN: user input for menu choices
    bool flag = true;               // FLAG: used for input validation check

    // PROCESS: loop for user menu and selections, continuation
    //          determined by user input
    while(menuChoice != 'q'){
        // PROCESS: open file being used/manipulated
        is.open("inventory.txt");

        // PROCESS: display current inventory
        displayInventory(is, b);

        // PROCESS: INPUT VALIDATION
        do{
            cout << "Menu:\n";
            cout << "Add a new item (a)\n";
            cout << "Select a bin (s)\n";
            cout << "Quit (q)\n\n";
            cout << "Selection: ";
            cin >> menuChoice;
            if(menuChoice == 'a' || menuChoice == 's'||menuChoice == 'q'){
                flag = false;
            }
            else cout << '\n';
        }while(flag);
        flag=true;

        // PROCESS: menu selection actions
        if(menuChoice == 'a') AddItem(b, os);
        if(menuChoice == 's'){
            cout << "Bin Selection: ";
            cin.clear();
            cin.ignore();
            getline(cin, binSelection);
            cout << '\n';
            // PROCESS: INPUT VALIDATION
            do{
                cout << "Menu:\n";
                cout << "Add parts (a)\n";
                cout << "Remove parts (r)\n";
                cout << "\nSelection: ";
                cin >> menuChoice;
                if(menuChoice == 'a' || menuChoice == 'r'){
                    flag = false;
                }
                else cout << '\n';
            }while(flag);
            flag = true;

            if(menuChoice == 'a') AddParts(binSelection, b, os);
            if(menuChoice == 'r') RemoveParts(binSelection, b, os);
        }
        if(menuChoice == 'q') {
            cout << "Good Bye!!!\n";
            os.open("inventory.txt");
            for(int i = 0; i < 20; i++){
                os << originalList[i] << '\n';
            }
            os.close();
            exit(0);
        }
    }
}

/*****************************************************************************
 * FUNCTION displayInventory
 *________________________________________________
 * This function receives the current state of the
 * inventory from the file stream and displays that
 * stream to the user.
 *_______________________________________________
 * PRE-CONDITIONS
 * The following needs previous defined values:
 * Bin          : the structure to hold the inventory names and quantities
 * is           : the input stream
 * POST-CONDITIONS
 * This function displays the current inventory names as well as the quantity
 * associated to the respective part names.
 ****************************************************************************/
void displayInventory(ifstream &is, Bin b[])
{
    // DATA TABLE
    int numLines = 0;          // IN: determine current number of lines in file
    string inventoryAmmt,      // INOUT: hold string for inventory string to
    //convert to string
    line;              // IN: used to help determine number of lines
    //count

    is.clear();
    is.seekg(0, is.beg);

    //PROCESS: determine number of lines in file
    while(getline(is, line)) {
        numLines++;
    }

    //PROCESS: convert numLines to number of items for iteration
    numLines /= 2;
    is.clear();
    is.seekg(0, is.beg);

    // PROCESS: store name/inventory in their appropriate bin struct members
    for(int i = 0; i < numLines; i++){
        getline(is, b[i].partName, '\n');
        getline(is, inventoryAmmt, '\n');
        istringstream(inventoryAmmt) >> b[i].partInventory;
    }

    // PROCESS: print current list in bins array up to the total number of items
    for(int i = 0; i < numLines; i++)
        cout << left << setw(20) << b[i].partName << right << setw(3) << b[i].partInventory << endl;
    cout << endl;
}

/*****************************************************************************
 * FUNCTION AddParts
 *________________________________________________
 * This function takes in the current bin being
 * selected and adds a quantity of parts to that
 * bin, as well writing the changes to the
 * inventory list via the out-stream.
 *_______________________________________________
 * PRE-CONDITIONS
 * The following needs previous defined values:
 * binSelection : the string associated to the selection in which the user
                  makes
 * Bin          : the structure to hold the inventory names and quantities
 * os           : the output stream
 *
 * POST-CONDITIONS
 * This function takes in the quantity of parts in which the user wants to add
 * to a respective part and updates the text file with those changes.
 ****************************************************************************/
void AddParts(const string& binSelection, Bin b[], ofstream &os)
{
    // DATA TABLE
    int partsAdded;         // IN: number of parts user wants to add
    int lastItemIndex;      // IN: stores the index of the last item -> total
    //number items currently

    // PROCESS: find index of last item
    for(int i = 0; i < 30; i++){
        if(b[i].partName == ""){
            lastItemIndex = i;
            break;
        }
    }

    cout << "Number of parts to add: ";
    cin >> partsAdded;

    // PROCESS: input validation for quantity
    while(partsAdded < 0){
        cout << "Number of parts to add: ";
        cin >> partsAdded;
    }

    // PROCESS: find item from user input and update the total if allowed
    for(int i =0; i < lastItemIndex; i++){
        if(b[i].partName == binSelection){
            if((b[i].partInventory + partsAdded) > 30) cout << "Not valid";
            else b[i].partInventory += partsAdded;
            break;
        }
    }
    os.open("inventory.txt");
    // PROCESS: Write to file the updated inventory
    for(int i = 0; i < lastItemIndex; i++){
        os << b[i].partName << '\n' << b[i].partInventory << '\n';
    }
    os.clear();
    os.close();
}

/*****************************************************************************
 * FUNCTION RemoveParts
 *________________________________________________
 * This function takes in the current bin being
 * selected and removes the quantity of parts of
 * that particular bin, as well writing the
 * changes to the inventory list via the
 * out-stream.
 *_______________________________________________
 * PRE-CONDITIONS
 * The following needs previous defined values:
 * binSelection : the string associated to the selection in which the user
 *                makes
 * Bin          : the structure to hold the inventory names and quantities
 * os           : the output stream
 *
 * POST-CONDITIONS
 * This function takes in the quantity of parts in which the user wants to
 * remove from the respective part and updates the text file with those changes.
 ****************************************************************************/
void RemoveParts(const string& binSelection, Bin b[], ofstream &os){
    // DATA TABLE
    int partsRemoved;        // IN: number of parts user wants to remove
    int lastItemIndex;       // IN: stores the index of the last item
    //     -> total number items currently

    // PROCESS: find the last item index
    for(int i = 0; i < 30; i++){
        if(b[i].partName == ""){
            lastItemIndex = i;
            break;
        }
    }

    cout << "Number of parts to remove: ";
    cin >> partsRemoved;

    // PROCESS: input validation
    while(partsRemoved < 0){
        cout << "Number of parts to add: ";
        cin >> partsRemoved;
    }

    // PROCESS: Update the number in inventory struct array for selected part
    for(int i =0; i < lastItemIndex; i++){
        if(b[i].partName == binSelection){
            if((b[i].partInventory - partsRemoved) < 0) cout << "Not valid" << endl;
            else b[i].partInventory -= partsRemoved;
            break;
        }
    }
    os.open("inventory.txt");

    // PROCESS: UPDATE THE INVENTORY IN THE FILE FOR OUPUT, WRITE TO FILE
    for(int i = 0; i < lastItemIndex; i++){
        os << b[i].partName << '\n' << b[i].partInventory << '\n';
    }
    os.close();
}

/*****************************************************************************
 * FUNCTION AddItem
 *________________________________________________
 * This function validates that there is enough
 * space within the inventory to accept new items
 * and adds a new item and its respective quantity
 * based on the user inputs.
 *_______________________________________________
 * PRE-CONDITIONS
 * The following needs previous defined values:
 * Bin          : the structure to hold the inventory names and quantities
 * os           : the output stream
 *
 * POST-CONDITIONS
 * This function updates the current inventory list with the part and quantity
 * in which the user chose to add, if and only if there is space available
 * for such manipulations.
 ****************************************************************************/
void AddItem(Bin b[], ofstream &os){
    // DATA TABLE
    int newItemIndex = 0; // IN: stores the index of bins array where new item
    //will be stored

    // PROCESS: determine if there are more bins to fill
    if(b[29].partName != "") cout << "Max bins reached";
    else{
        // PROCESS: locate the index where first instance of an empty
        //itemDescription string variable is
        for(int i = 0; i < 30; i++){
            if(b[i].partName == ""){
                newItemIndex = i;
                break;
            }
        }

        // INPUT: user input for new item and quantity
        cout << "\nEnter Part Description: ";
        cin >> b[newItemIndex].partName;
        cout << "Number of Parts in the Bin: ";
        cin >> b[newItemIndex].partInventory;
        cout << '\n';
        //PROCESS: Write updated information into file.
        os.open("inventory.txt");
        for(int i = 0; i < 30; i++){
            os << b[i].partName << '\n' << b[i].partInventory << '\n';
            if(b[i].partName == b[newItemIndex].partName) break;
        }
        os.close();
    }
}