#pragma once
#include <SDL.h>

class Item
{
	bool weapon = false;
	bool utility = false;
	bool tile = false; //if the item is a type of tyle
	bool consumable = false; //you never know, maybe it will hurt you :)
	
	bool inRange;
	bool enhancement; //if a weapon is enhanced, like an enchantment in minecraft

	float resistance; //this is for when the player may equip armor, and may reduce incoming damage
	float bonusMoveSpeed;//one is just a flat bonus
	float moveSpeedMultiplier;// the other is an adaptive bonus that will change based on the base number
	float chargeTime; //for ranged weapons, maybe reload times as well
	float damage;
	float enhancementDamage; //can be used as an addition the the default damage
	float durabilityPoints;
	float uses; //also accounts for ammo
	float attackRate;
	float heal; //positive value per item use
	float selfHurt; //negative value per item use
	float range;

public:
	void CheckInRange(SDL_Window* window);

};

