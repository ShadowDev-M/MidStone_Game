#include "BoxCollider.h"



void BoxCollider::CheckCollision()
{
	//Find the worldCoords of the top left corner
	Vec2 topLCorner = Vec2(bodyPos.x, bodyPos.y);


	for (int i = 0; i < wallFaces.capacity(); i++)
	{
		TileFaces temp = wallFaces[i];

		//Check to see if see this face is vertical or horizontal
		if (temp.PointOne.y == temp.PointTwo.y)
		{

			//Checking to see which point is on the right side of the wall and which on the left side
			float leftEdge = temp.PointOne.x < temp.PointTwo.x ? temp.PointOne.x : temp.PointTwo.x;
			float RightEdge = temp.PointOne.x < temp.PointTwo.x ? temp.PointTwo.x : temp.PointOne.x;
			float wallY = temp.PointTwo.y;

			//If the player is not between two edges on the X axis, don't do the rest of the code
			if (bodyPos.x < leftEdge || bodyPos.x > RightEdge)
				continue;


			//AABB Collision Detection (Search on google to undrestand the concept)
			if (topLCorner.y > wallY && topLCorner.y - worldH < wallY)
			{
				//Reverse the velocity to create a bouncing effect (This caused a problem, we're not using it now)
				float penetration = DetectPenetration(temp, bodyPos, bodyVel);
				std::cout << "\nPen Amount: " << penetration;
				temp.PointTwo.print();
				//Return player by the penetration amount
				bodyPos.y -= penetration;
				Vec3 newVel = Vec3(bodyVel.x, 0, bodyVel.z);
				bodyVel = newVel;

			}

			continue;
		}

		//Check to see if see this face is vertical or horizontal
		if (temp.PointOne.x == temp.PointTwo.x)
		{
			//Checking to see which point is on the top side of the wall and which on the buttom side
			float BottomEdge = temp.PointOne.y < temp.PointTwo.y ? temp.PointOne.y : temp.PointTwo.y;
			float topEdge = temp.PointOne.y < temp.PointTwo.y ? temp.PointTwo.y : temp.PointOne.y;
			float wallX = temp.PointOne.x;

			//If the player is not between two edges on the Y axis, don't do the rest of the code
			if (bodyPos.y > topEdge || bodyPos.y < BottomEdge)
				continue;

			//AABB Collision Detection (Search on google to undrestand the concept)
			if (topLCorner.x < wallX && topLCorner.x + worldW > wallX)
			{
				//Reverse the velocity to create a bouncing effect (This caused a problem, we're not using it now)
				float penetration = DetectPenetration(temp, bodyPos, bodyVel);
				std::cout << "\nPen Amount: " << penetration;

				//Return player by the penetration amount
				bodyPos.x -= penetration;
				Vec3 newVel = Vec3(0, bodyVel.y, bodyVel.z);
				bodyVel = newVel;
			}


		}

	}
}

float BoxCollider::DetectPenetration(TileFaces wall, Vec3 pos, Vec3 vel)
{
	float penetration;
	//If the wall is horizontal
	if (wall.PointOne.y == wall.PointTwo.y)
	{
		bool movingDown = vel.y <= 0;

		if (movingDown)
		{
			//Compare bottom face of the player with the colliding wall
			float ColliderBottomFaceY = pos.y - worldH ;
			penetration =  ColliderBottomFaceY - wall.PointOne.y;
			return penetration;
		}

		//Compare top face of the player with the colliding wall
		float ColliderTopFaceY = pos.y ;
		penetration =  ColliderTopFaceY - wall.PointOne.y;
		return penetration;
	}
	else
	{
		bool movingRight = vel.x >= 0;
		std::cout << vel.x;
		if (movingRight)
		{
			//Compare right face of the player with the colliding wall
			float ColliderRightFaceX = pos.x + worldW ;
			penetration = ColliderRightFaceX - wall.PointOne.x;
			//test
			return penetration;
		}

		//Compare left face of the player with the colliding wall
		float ColliderLeftFaceX = pos.x ;
		penetration = ColliderLeftFaceX - wall.PointOne.x;
		return penetration;

	}

}



