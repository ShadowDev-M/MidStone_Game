#include "Inventory.h"

//IVENTORY MAKER
Inventory::Inventory() {//creates inventory array with... nothing... boo!
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mainInventory[i][j] = nullptr;
        }
    }
}

//SEARCH AND ADD TO INVENTORY
bool Inventory::addItem(Item* item) {//uses a for loop to look for the first empty slot, and returns a value when it finds and also places the item
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (mainInventory[i][j] = nullptr) {//if that slot is empty
                mainInventory[i][j] = item; //use that slot for the item
                return true; //set to true to satisfy the function and end it
            }
        
        }
    }
    return false; //if the loop can't find anything, nothing happens
}

//ITEM REMOVER
bool Inventory::removeItem(int row, int col) {
    if (mainInventory[row][col] != nullptr) { //if the space is not empty
        mainInventory[row][col] = nullptr; // then make it empty
        return true;// satisfy function
    }
    return false; // is the space is already empty
}


   
