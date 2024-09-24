//
//  Player.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "Body.h"
#include "GameManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <Vector.h>

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
    
    //Health
    float healthpoints = 10.0f;

    //Speed
    float walkSpeedMax = 3.0f;

    // use the base class versions of getters
    bool OnCreate();
    void Render(float scale = 1.0f);
    void HandleEvents(const SDL_Event& event);
    void Update(float deltaTime);
    void setTexture(SDL_Texture* texture_) {texture = texture_;}
    void takeDamage(float damage);
};

#endif /* PLAYER_H */
