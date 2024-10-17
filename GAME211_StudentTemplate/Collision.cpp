#include "Collision.h"

void Collision::CheckCollision()
{

	float x = body->getPos().x;
	float y = body->getPos().y;
	for (int i = 0; i < wallFaces.capacity(); i++)
	{
		ColliderFace temp = wallFaces[i];

		if (temp.point1.y == temp.point2.y)
		{
			float leftEdge = temp.point1.x < temp.point2.x ? temp.point1.x : temp.point2.x;
			float RightEdge = temp.point1.x < temp.point2.x ? temp.point2.x : temp.point1.x;

			if (y == temp.point1.y)
			{
				if (x > leftEdge && x < RightEdge)
					std::cout << "\nCollision Detected1";
			}

			continue;
		}

		if (temp.point1.x == temp.point2.x)
		{
			float BottomEdge = temp.point1.y < temp.point2.y ? temp.point1.y : temp.point2.y;
			float topEdge = temp.point1.y < temp.point2.y ? temp.point2.y : temp.point1.y;


			if (x == temp.point1.x)
			{
				if (y > BottomEdge && y < topEdge)
					std::cout << "\nCollision Detected2";
			}


		}

	}
}

void Collision::Update(float deltaTime)
{
	CheckCollision();
}
