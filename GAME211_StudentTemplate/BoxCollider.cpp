#include "BoxCollider.h"



void BoxCollider::CheckCollision(Vec2 pos)
{
	//Find the worldCoords of the top left corner
	Vec2 topLCorner = Vec2(pos.x, pos.y);


	for (int i = 0; i < collidableObjects.size(); i++)
	{
		TileFaces object = collidableObjects[i];
		
		//Check to see if see this face is vertical or horizontal
		if (object.PointOne.y == object.PointTwo.y)
		{

			//Checking to see which point is on the right side of the wall and which on the left side
			float leftEdge = object.PointOne.x < object.PointTwo.x ? object.PointOne.x : object.PointTwo.x;
			float RightEdge = object.PointOne.x < object.PointTwo.x ? object.PointTwo.x : object.PointOne.x;
			float objectYpos = object.PointTwo.y;

		
			//If the player is not between two edges on the X axis, don't do the rest of the code
			if ((topLCorner.x < leftEdge && topLCorner.x + worldW < leftEdge) || topLCorner.x > RightEdge)
			{
				continue;
			}

			

			//AABB Collision Detection (Search on google to undrestand the concept)
			if (topLCorner.y > objectYpos && topLCorner.y - worldH < objectYpos)
			{
				//Reverse the velocity to create a bouncing effect (This caused a problem, we're not using it now)
				//float penetration = DetectPenetration(temp, bodyPos, bodyVel);
				//std::cout << "\nPen Amount: " << penetration;
				
				//Return player by the penetration amount
				//bodyPos.y -= penetration;
				//Vec3 newVel = Vec3(bodyVel.x, 0, bodyVel.z);
				//bodyVel = newVel;
				TriggerCollision(object);
				
			}

			continue;
		}

		//Check to see if see this face is vertical or horizontal
		if (object.PointOne.x == object.PointTwo.x)
		{
			//Checking to see which point is on the top side of the wall and which on the buttom side
			float BottomEdge = object.PointOne.y < object.PointTwo.y ? object.PointOne.y : object.PointTwo.y;
			float topEdge = object.PointOne.y < object.PointTwo.y ? object.PointTwo.y : object.PointOne.y;
			float objectXpos = object.PointOne.x;

			//If the player is not between two edges on the Y axis, don't do the rest of the code
			if ((topLCorner.y > topEdge && topLCorner.y - worldH > topEdge) || topLCorner.y < BottomEdge)
				continue;

			//AABB Collision Detection (Search on google to undrestand the concept)
			if (topLCorner.x < objectXpos && topLCorner.x + worldW > objectXpos)
			{
				//Reverse the velocity to create a bouncing effect (This caused a problem, we're not using it now)
				//float penetration = DetectPenetration(temp, bodyPos, bodyVel);
				//std::cout << "\nPen Amount: " << penetration;

				//Return player by the penetration amount
				//bodyPos.x -= penetration;
				//Vec3 newVel = Vec3(0, bodyVel.y, bodyVel.z);
				//bodyVel = newVel;
				TriggerCollision(object);
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
		//std::cout << vel.x;
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



