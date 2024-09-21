#pragma once
#include "Body.h"
#include <stdio.h>
#include "GameManager.h"



class TestBlock :Body
{
protected:
	class GameManager* game;

public:
	TestBlock() : Body{}
	{
		game = nullptr;
	}

	// Note the last parameter in this constructor!
	// Look in GameManager.cpp to see how this is called.
	// Look in .cpp file, at Render(), to see why game_ is a parameter.
	TestBlock(
		Vec3 pos_, Vec3 vel_, Vec3 accel_,
		float mass_,
		float radius_,
		float orientation_,
		float rotation_,
		float angular_,
		GameManager* game_
	) : Body{
		  pos_
		, vel_
		, accel_
		, mass_
		, radius_
		, orientation_
		, rotation_
		, angular_
	}
		, game{ game_ }
	{

	}

	// use the base class versions of getters

	bool OnCreate();
	void Render(float scale = 1.0f);
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	Vec3 getPos() { return pos; }

};

