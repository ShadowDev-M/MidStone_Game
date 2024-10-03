#pragma once
#include <vector>;
#include <iostream>;
#include "Vector.h";
#include "Body.h";
using namespace MATH;

struct ColliderFace
{
	//This may change depended on Joel's code
	Vec2 point1;
	Vec2 point2;

	ColliderFace() {};
	ColliderFace(Vec2 p1, Vec2 p2)
	{
		point1 = p1;
		point2 = p2;
	};
};


class BoxCollider
{

private:
	//List of the solid faces coming from Joel's code
	std::vector<ColliderFace> wallFaces;
	float width, height;
	void SortWallFaces();

public:
	BoxCollider() {};
	BoxCollider(Body* _body)
	{
		float w = 1000;
		float h = 600;
	}

	//We load the solid faces here 
	void setObstacles(std::vector<ColliderFace> _wallFaces)
	{
		wallFaces = _wallFaces;
	}

	//Set the body's width and height to calculate the collision
	void SetCollider(float w, float h)
	{
		width = w;
		height = h;
	}

	//This method gets called by the owner of the collider in the update funtion
	void CheckCollision(Vec3 pos);

};


