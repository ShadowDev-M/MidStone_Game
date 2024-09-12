#pragma once
class Inventory
{
	char hotkey1;
	char hotkey2;
	char hotkey3;
	char hotkey4;
	char hotkey5;

	int maxLoad = 20;
	const char* mainInventory[5];
	const char* extraInventory[15];

public:
	
	Inventory()
	{
		mainInventory[0] = &hotkey1;
		mainInventory[1] = &hotkey2;
		mainInventory[2] = &hotkey3;
		mainInventory[3] = &hotkey4;
		mainInventory[4] = &hotkey5;
	}
};

