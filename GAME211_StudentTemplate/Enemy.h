//
//  Player.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <Vector.h>
#include "BoxCollider.h"

class Enemy : public Body
{
protected:
    class GameManager* game;

public:

    Enemy() : Body{}
    {
        game = nullptr;
    }

    // Note the last parameter in this constructor!
    // Look in GameManager.cpp to see how this is called.
    // Look in .cpp file, at Render(), to see why game_ is a parameter.
    Enemy(
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
    },
        game{ game_ }
    {}

    // Temp constructer
    Enemy(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, float radius_, float orientation_, float rotation_, float angular_);

    Enemy(Vec3 pos_, float dmg);

    //const char* enemyImage;
    //SDL_Texture* enemyTexture;
    //SDL_Surface* enemySurface;
    std::vector<TileFaces> hitFaces;
    //std::vector<TileFaces> permFaces;
    ObjectTag objectTag = enemy;

    BoxCollider hitbox = BoxCollider();

    float damage;

    // use the base class versions of getters
    bool OnCreate();
    void OnDestroy();
    void Render(float scale = 1.0f);
    void HandleEvents(const SDL_Event& event);
    void Update(float deltaTime);
    float getDamage() { return damage; }

    // Call in the scene to pass the scenes renderer and projection matrix onto the player (Will change/get better when camera class is done)
    void setRenderer(SDL_Renderer* renderer_) { renderer = renderer_; } //renderer is defined in body

};

#endif /* ENEMY_H */