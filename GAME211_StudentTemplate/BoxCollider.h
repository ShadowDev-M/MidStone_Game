#pragma once
#include <vector>;
#include <iostream>;
#include "Vector.h";
#include "Body.h";
#include "ChunkHandler.h"
using namespace MATH;

//struct ColliderFace
//{
//	//This may change depended on Joel's code
//	Vec2 point1;
//	Vec2 point2;
//
//	ColliderFace() {};
//	ColliderFace(Vec2 p1, Vec2 p2)
//	{
//		point1 = p1;
//		point2 = p2;
//	};
//};


class BoxCollider
{

private:
	//List of the solid faces coming from Joel's code
	std::vector<TileFaces> wallFaces;
	float worldW, worldH;
	Vec3& bodyVel;
	Vec3& bodyPos;
	
	float DetectPenetration(TileFaces wall, Vec3 pos, Vec3 vel);
	ChunkHandler* chunkHandler;

public:
	BoxCollider(Vec3& _bodyVel, Vec3& _bodyPos) : bodyVel(_bodyVel), bodyPos(_bodyPos)
	{

	}

	//We load the solid faces here 
	void setObstacles(std::vector<TileFaces> _wallFaces)
	{
		wallFaces = _wallFaces;
	}

	//Set the body's width and height to calculate the collision
	void OnCreate(int imageWidth, int imageHeight, float scale)
	{
		//Setting colldier faces
		Vec3 dimensions = Vec3(imageWidth * scale, imageHeight * scale, 0);

		//TODO: Replace these two lines by the function that Massimo is gonna write for 
		//converting screenCoords to worldCoord
		worldH = dimensions.y * (15.0f / 600.0f);
		worldW = dimensions.x * (25.0f / 1000.0f);
	}

	//This method gets called by the owner of the collider in the update funtion
	void CheckCollision();

};


