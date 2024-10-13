#pragma once
#include "Item.h"
#include "iostream"
using namespace std;
class Inventory
{
	static const int rows = 4;
	static const int cols = 5;
	Item* mainInventory[rows][cols];


public:
	Inventory();
	bool addItem(Item* item);
	bool removeItem(int row, int col);	
<<<<<<< HEAD
	Item* getItem(int row, int col) { return mainInventory[row][col]; }
=======
	bool removeItem(int row, int col);
	Item* getItem(int row, int col) { return mainInventory[row][col]; }
	void printInventory() /* { cout << mainInventory << endl*/;

>>>>>>> origin/inventory-branch
};

