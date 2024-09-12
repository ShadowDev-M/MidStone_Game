#pragma once
#include <VMath.h>
#include <Vector.h>

using namespace MATH;

class Item
{
	bool weapon;
	bool utility;
	bool tile; //if the item is a type of tyle
	bool consumable; //you never know, maybe it will hurt you :)
	bool inRange;

	float chargeTime; //for ranged weapons, maybe reload times as well
	float damage;
	float uses; //also accounts for ammo
	float attackRate;
	float heal; //positive value per item use
	float selfHurt; //negative value per item use
	float range;
	
	float actualRange = range * 2 * 3.14159265357989323;
	float rangeArea = 3.14159265357989323 * (range * range);

};

