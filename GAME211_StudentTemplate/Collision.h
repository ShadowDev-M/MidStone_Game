#pragma once
#include <vector>;
#include <iostream>;
#include "Vector.h";
#include "Body.h";
using namespace MATH;

struct ColliderFace
{
	Vec2 point1;
	Vec2 point2;

	ColliderFace() {};
	ColliderFace(Vec2 p1, Vec2 p2)
	{
		point1 = p1;
		point2 = p2;
	};
};


class Collision
{

private:
	Body* body;
	std::vector<ColliderFace> wallFaces;
	std::vector<ColliderFace> PlayerFaces;
	void SortWallFaces();

public:
	Collision() {};
	Collision(Body* _body)
	{
		float w = 1000;
		float h = 600;
		body = _body;
		/*WallFace s;
		Vec2 p1 = Vec2(300, 250);
		Vec2 p2 = Vec2(600, 250);

		s.point1.x = static_cast<int>(p1.x - 0.5f * w);
		s.point1.y = static_cast<int>(p1.y - 0.5f * h);
		s.point2.x = static_cast<int>(p2.x - 0.5f * w);
		s.point2.y = static_cast<int>(p2.y - 0.5f * h);
		std::cout << "\n P1: " << s.point1.x << " " << s.point1.y;*/

	}
	void setObstacles(std::vector<ColliderFace> _wallFaces)
	{
		wallFaces = _wallFaces;
	}

	void SetPlayerCollider(std::vector<ColliderFace>_playerFaces)
	{
		PlayerFaces = _playerFaces;
	}
	void CheckCollision();
	void Update(float deltaTime);

};


