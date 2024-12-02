#pragma once
#include <SDL.h>

class Item
{
	float one, two, three;
	float range;
	bool inRange;
	bool enhancement; //if a weapon is enhanced, like an enchantment in minecraft
public:
	Item();
	void CheckInRange(SDL_Window* window);
	Item(const char* itemName, const char* filePath, float range, float one, float two);
	const char* itemName;
	const char* filePath;
};

