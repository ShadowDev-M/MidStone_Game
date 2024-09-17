#pragma once
#include <VMath.h>
#include <Vector.h>
#include <SDL.h>

using namespace MATH;

class Item
{
	bool weapon = false;
	bool utility = false;
	bool tile = false; //if the item is a type of tyle
	bool consumable = false; //you never know, maybe it will hurt you :)
	bool inRange;

	float chargeTime; //for ranged weapons, maybe reload times as well
	float damage;
	float uses; //also accounts for ammo
	float attackRate;
	float heal; //positive value per item use
	float selfHurt; //negative value per item use
	float range;

public:
	void CheckInRange(SDL_Window* window);

};

