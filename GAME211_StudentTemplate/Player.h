#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "Body.h"
#include "Inventory.h"
#include "GameManager.h"
#include "Enemy.h"
#include <SDL.h>
#include <SDL_image.h>
#include <Vector.h>
#include "BoxCollider.h"

class Player : public Body
{
protected:
    class GameManager* game;

public:

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
    //
    float walkSpeedMax = 3.0f;
    Inventory playerInventory;

    std::vector<TileFaces> hitFaces;
    
    BoxCollider hitbox = BoxCollider();
    // use the base class versions of getters
    bool OnCreate();
    void OnDestroy();
    void Render(float scale = 1.0f);
    void HandleEvents(const SDL_Event& event);
    void Update(float deltaTime);

    void setTexture(SDL_Texture* texture_) {texture = texture_;}
    void takeDamage(float damage) { healthpoints -= damage; }
    void setItem(Item newItem) { currentItem = newItem; }



    // Call in the scene to pass the scenes renderer and projection matrix onto the player (Will change/get better when camera class is done)
    void setRenderer(SDL_Renderer* renderer_) { renderer = renderer_; } //renderer is defined in body
    void setProjection(Matrix4 projectionMatrix_) { projectionMatrix = projectionMatrix_; } //projection matrix is defined in body
    void setInverse(Matrix4 inverseMatrix_) { inverseProjection = inverseMatrix_; } //projection matrix is defined in body
    void onCollisionTrigger(const TileFaces& collidedObject);

};

#endif /* PLAYER_H */
