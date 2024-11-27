#include "BoxCollider.h"
#include "Camera.h"


void BoxCollider::CheckCollision(Vec3 pos, Vec3 vel)
{
	//Find the worldCoords of the top left corner
	Vec2 topLCorner = Vec2(pos.x, pos.y);
	bool hasVcollision = false, hasHcollision = false;
	TileFaces Vwall, Hwall;


	for (int i = 0; i < collidableObjects.size(); i++)
	{
		TileFaces object = collidableObjects[i];
		
		//Check to see if see this face is vertical or horizontal

		
		//Check to see if see this face is vertical or horizontal
		if (object.PointOne.x == object.PointTwo.x)
		{
			//Vertical
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
				TriggerCollisionEnter(object);
				hasVcollision = true;
				Vwall = object;
				continue;
			}
			continue;
		}

		if (object.PointOne.y == object.PointTwo.y)
		{
			//Horizontal
			//Checking to see which point is on the right side of the wall and which on the left side
			float leftEdge = object.PointOne.x < object.PointTwo.x ? object.PointOne.x : object.PointTwo.x;
			float RightEdge = object.PointOne.x < object.PointTwo.x ? object.PointTwo.x : object.PointOne.x;
			float objectYpos = object.PointTwo.y;


			//If the player is not between two edges on the X axis, don't do the rest of the code
			if ((topLCorner.x < leftEdge && topLCorner.x + worldW < leftEdge) || topLCorner.x > RightEdge)
			{
				if (hasHcollision)
				{
					//std::cout << "Bruh1";
					//onCollisionExit(object);
				}
				continue;
			}



			//AABB Collision Detection (Search on google to undrestand the concept)
			if (topLCorner.y > objectYpos && topLCorner.y - worldH < objectYpos)
			{
				hasHcollision = true;
				Hwall = object;
				TriggerCollisionEnter(object);
				continue;
			}
			else if (hasHcollision)
			{
				//TriggerCollisionExit(object);
				//std::cout << "Bruh1";
			}


		}

		/*if (hasHcollision && hasVcollision)
		{
			float Vpenetration = DetectPenetration(Vwall, pos, vel);
			float Hpenetration = DetectPenetration(Hwall, pos, vel);

			if (Vpenetration < Hpenetration)
			{
				TriggerCollision(Vwall);
			}
			else
			{
				TriggerCollision(Hwall);
			}
		}*/
	}
}
Camera camera;
void BoxCollider::OnCreate(int imageWidth, int imageHeight, float scale)
{
		//Setting colldier faces
		Vec3 dimensions = Vec3(imageWidth * scale, imageHeight * scale, 0);
		camera.OnCreate();

		
		//converting screenCoords to worldCoord
		worldH = dimensions.y * camera.getYAxis() / camera.getWindowHeight();//(15.0f / 600.0f);

		worldW = dimensions.x * camera.getXAxis() / camera.getWindowWidth();//(25.0f / 1000.0f);
		std::cout << "\n World H:" << imageHeight;
		std::cout << "\n World W:" << imageWidth;	
}

float BoxCollider::DetectCollision(TileFaces wall, Vec3 pos, Vec3 vel)
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





