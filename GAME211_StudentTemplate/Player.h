#ifndef PLAYER_H
#define PLAYER_H

#include "UiPanel.h"
//#include "Camera.h"
#include "Item.h"
#include "Inventory.h"
#include <stdio.h>
#include "Body.h"
#include "Inventory.h"
#include "GameManager.h"
#include "Enemy.h"
#include <SDL.h>
#include <SDL_image.h>
#include <Vector.h>
#include "BoxCollider.h"
#include "ChunkHandler.h"
#include "BoxCollider.h"
#include "HPbar.h"

class Player : public Body
{
	using OnAttackCallBack = std::function<void(Vec3, float)>;
protected:
	class GameManager* game;
	bool isWallBouncingY = false; // Is the player in a bounce-back state?
	bool isWallBouncingX = false; // Is the player in a bounce-back state?
	float wallBounceDecay = 0.7f; // Damping factor (adjust as needed)
	int pushBackDirection;
	OnAttackCallBack onAttackCallBack;
private:
    Item* currentItem;
    UiPanel panel;
    UiPanel space[5];
    HealthBar* healthBar;
	Window* window;
    //Camera camera;

public:
    float panelScaling = 1.7f;
    Player() : Body{}
    {
        game = nullptr;
    }

	// Note the last parameter in this constructor!
	// Look in GameManager.cpp to see how this is called.
	// Look in .cpp file, at Render(), to see why game_ is a parameter.
	Player(
		Vec3 pos_, Vec3 vel_, Vec3 accel_,
		float mass_,
		float radius_,
		float orientation_,
		float rotation_,
		float angular_,
		GameManager* game_
	) : Body{
		  pos_,
		  vel_,
		  accel_,
		  mass_,
		  radius_,
		  orientation_,
		  rotation_,
		  angular_
	}
		, game{ game_ }
	{}

	// Temp constructer
	Player(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, float radius_, float orientation_, float rotation_, float angular_);

	// Variables
	float healthpointsMax = 10.0f;
	float healthpoints = healthpointsMax;

	int invulTimerMax = 60;
	int invulTimer = 0;

	int dmgValue = 5;

	float walkSpeedMax = 2.0f;
	Inventory playerInventory;
	std::vector<TileFaces> hitFaces;
	std::vector<TileFaces> permFaces;

	bool hasArmor();
    bool hasShoes();
    bool isHoldingShield() const; 
    void setCurrentItem(Item* item) { currentItem = item; }
    void refreshIcons();
	bool CheckInRange(float posX, float posY, float range);

	ChunkHandler* region;

	BoxCollider hitbox = BoxCollider();
	// use the base class versions of getters
	void SetRegion(ChunkHandler* region_) { region = region_; };
	float getPlayerHP() { return healthpoints; }

	// Damage and Health Should be Body varibles that are set and accesed via player and enemy
	int getPlayerDamage() { return dmgValue; }
    float addPlayerHP(float heal) { healthpoints += heal; if (healthpoints >= healthpointsMax) { healthpoints = healthpointsMax; } return healthpoints; }
    bool OnCreate();
    void setupCollision();
    void OnDestroy();
    void Render();
    void RenderUI();
    void HandleEvents(const SDL_Event& event);
    void Update(float deltaTime);
    

	void takeDamage(float damage);

	//void setItem(Item* newItem) { currentItem = newItem; }
	void setFaces(std::vector<TileFaces> faces_); //


	// Call in the scene to pass the scenes renderer and projection matrix onto the player (Will change/get better when camera class is done)
	void setRenderer(SDL_Renderer* renderer_) { renderer = renderer_; }
	void setProjection(Matrix4 projectionMatrix_) { projectionMatrix = projectionMatrix_; }
	void setInverse(Matrix4 inverseMatrix_) { inverseProjection = inverseMatrix_; } //projection matrix is defined in body
	void onCollisionEnter(const TileFaces& collidedObject);
	void onCollisionExit(const TileFaces& collidedObject);

	void SubscribeToOnAttack(OnAttackCallBack callBack)
	{
		onAttackCallBack = callBack;
	}

	void TriggerOnAttack(Vec3 mousePos, float damage);


};

#endif /* PLAYER_H */
