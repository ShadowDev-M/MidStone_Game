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
#include "Player.h"

class Player;

class Enemy : public Body
{
protected:
    enum enemyState
    {
        patrol,
        chase,
        attack,
        dead
    };

    //General
    class GameManager* game;
    enemyState State;
    float speed;
    void MoveTo(float deltaTime);
    int GetRandomNumber(int min, int max);

    

    void onCollisionEnter(const TileFaces& collidedObject);
    
    //Patrolling State
    int patrolRadius;
    bool isMoving = false;
    float patrolDelay;
    float patrolTimer;
    Vec3 newPos;
    Vec3 initPos;
    void Patrol(float deltaTime);

    //Attack State
    float attackCoolDown;
    float attackTimer;
    float damage;
    float attackRange;
    void Attack(float deltaTime);

    //Chase
    float sightRange;
    void Chase(float deltaTime);


    //Box Collider
    bool isWallBouncingY = false; // Is the player in a bounce-back state?
    bool isWallBouncingX = false; // Is the player in a bounce-back state?
    float wallBounceDecay = 0.7f; // Damping factor (adjust as needed)
    int pushBackDirection;
    
    std::vector<TileFaces> permFaces;
    ChunkHandler* region;
    BoxCollider hitbox = BoxCollider();


public:

    Enemy() : Body{}
    {
        game = nullptr;
        player = nullptr;
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
        GameManager* game_,
        Player* player_
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
        ,
        player {player_}
    {}

    // Temp constructer
    Enemy(Vec3 pos_, Vec3 vel_, Vec3 accel_, float mass_, float radius_, float orientation_, float rotation_, float angular_, Player* player);

    Enemy(Vec3 pos_, float dmg, Player* player_);

    //BoxCollider
    void SetRegion(ChunkHandler* region_) { region = region_; };
    void setFaces(std::vector<TileFaces> faces_);
    std::vector<TileFaces> hitFaces;
    ObjectTag objectTag = enemy;

  

    Player* player;

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