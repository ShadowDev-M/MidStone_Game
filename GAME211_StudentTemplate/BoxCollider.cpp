#include "BoxCollider.h"

void BoxCollider::CheckCollision(Vec3 pos)
{
	//Find the worldCoords of the top left corner
	Vec2 topLCorner = Vec2(pos.x - width / 2, pos.y - height / 2);
	
	
	for (int i = 0; i < wallFaces.capacity(); i++)
	{
		ColliderFace temp = wallFaces[i];

		//Check to see if see this face is vertical or horizontal
		if (temp.point1.y == temp.point2.y)
		{

			//Checking to see which point is on the right side of the wall and which on the left side
			float leftEdge = temp.point1.x < temp.point2.x ? temp.point1.x : temp.point2.x;
			float RightEdge = temp.point1.x < temp.point2.x ? temp.point2.x : temp.point1.x;
			float wallY = temp.point1.y;

			//If the player is not between two edges on the X axis, don't do the rest of the code
			if (pos.x < leftEdge || pos.x > RightEdge)
				continue;

			//AABB Collision Detection (Search on google to undrestand the concept)
			if (topLCorner.y < wallY && topLCorner.y + height > wallY)
			{
				std::cout << "\nCollision Detected1";
			}

			continue;
		}

		//Check to see if see this face is vertical or horizontal
		if (temp.point1.x == temp.point2.x)
		{
			//Checking to see which point is on the top side of the wall and which on the buttom side
			float BottomEdge = temp.point1.y < temp.point2.y ? temp.point1.y : temp.point2.y;
			float topEdge = temp.point1.y < temp.point2.y ? temp.point2.y : temp.point1.y;
			float wallX = temp.point1.x;

			//If the player is not between two edges on the Y axis, don't do the rest of the code
			if (pos.y > topEdge || pos.y < BottomEdge)
				continue;

			//AABB Collision Detection (Search on google to undrestand the concept)
			if (topLCorner.x < wallX && topLCorner.x + width > wallX)
			{
				std::cout << "\nCollision Detected2";
			}


		}

	}
}


