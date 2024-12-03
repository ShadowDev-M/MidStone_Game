#include "Item.h"
#include "player.h"
#include <cmath>

//
// THIS SECTION HAS PLACEHOLDERS, THE CHECKINRANGE FUNCTION CURRENTLY CHECKS THE MOUSE POSITION AND COMPARES IT TO THE CENTRE OF THE SCREEN
// cont'd. WHAT IT WILL COMPARE IN THE FUTURE, IS PLAYERS POSITION TO ENEMY POSITION
//

Item::Item()
{
}


Item::Item(const char* name_, const char* filePath_, float range_, bool isWeapon_, float one_, float two_) {
    itemName = name_;
    filePath = filePath_;
    one = one_;
    two = two_;
    range = range_;
    isWeapon = isWeapon_;
}
