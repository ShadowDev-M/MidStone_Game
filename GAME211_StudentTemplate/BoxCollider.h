#pragma once
#include <vector>;
#include <iostream>;
#include "Vector.h";
#include "Body.h";
#include "ChunkHandler.h"

#include <functional>
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
	using CollisionCallback = std::function<void(const TileFaces&)>;
	
	//List of the solid faces coming from Joel's code
	std::vector<TileFaces> collidableObjects;
	float worldW, worldH;
	
	//Vec3& bodyVel;
	//Vec3& bodyPos;
	CollisionCallback onCollisionEnter;
	CollisionCallback onCollisionExit;

public:

	BoxCollider()//(Vec3& _bodyVel, Vec3& _bodyPos) : bodyVel(_bodyVel), bodyPos(_bodyPos)
	{
		
	}

	//Call this when the object's image is initilized 
	//Set the body's width and height to calculate the collision
	void OnCreate(int imageWidth, int imageHeight, float scale);
	


	//Subscribe your collision response Function using this
	void Subscribe(CollisionCallback enterCallback,CollisionCallback exitCallback) {
		onCollisionEnter = enterCallback;
		onCollisionExit = exitCallback;
	}

	// Trigger the collision callback
	void TriggerCollisionEnter(const TileFaces& collidedObject) {
		if (onCollisionEnter) {
			onCollisionEnter(collidedObject); // Directly invoke the callback
		}
	}
	
	void TriggerCollisionExit(const TileFaces& collidedObject) {
		if (onCollisionExit) {
			onCollisionEnter(collidedObject); // Directly invoke the callback
		}
	}
	

	float DetectCollision(TileFaces wall, Vec3 pos, Vec3 vel);
	
	
	//BoxCollider& operator=(const BoxCollider& other);

	//We load the solid faces here 
	void setObstacles(std::vector<TileFaces> _wallFaces)
	{
		collidableObjects = _wallFaces;
	}

	//Call this in the object's Update function
	//This method gets called by the owner of the collider in the update funtion
	void CheckCollision(Vec3 pos, Vec3 vel);

};


