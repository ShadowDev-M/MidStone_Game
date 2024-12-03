#pragma once
#include "Item.h"
#include "Inventory.h"
Inventory playerInventory;
Item* sword = new Item("sword", "textures/sword.png", 300, true, 4, 0);
Item* shield = new Item("shield", "textures/shield.png", 0, false, 0, 0); //remove incoming damage, thats why it has no stats
Item* potion = new Item("potion", "textures/potion.png", 0, false, 3, 0); //heal 40
Item* armor = new Item("armor", "textures/armor.png", 0, false, 0, 0); // mitigate 20% of incoming damage
Item* shoes = new Item("shoes", "textures/shoes.png", 0, false, 6, 0); //double the players maximum move speed