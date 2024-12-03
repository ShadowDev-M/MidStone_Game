#pragma once
#include <SDL.h>

class Item
{
	float one, two, three;
	float range;
	//bool inRange;
	bool isWeapon;
	bool enhancement; //if a weapon is enhanced, like an enchantment in minecraft
public:
	Item();

	Item(const char* itemName, const char* filePath, float range, bool isWeapon, float one, float two);
	const char* itemName;
	const char* filePath;
	bool getIsWeapon() const { return isWeapon; }
	float getItemRange() const { return range; }
};

