//
//  Player.h
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#ifndef PLAYER_H
#define PLAYER_H
#include "GameManager.h"
#include "Body.h"
#include <SDL.h>
#include <SDL_image.h>
#include <Vector.h>

class Player : Body
{

protected:
    class GameManager* game;

public:
    Player();
    Player(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_,
        float radius_,
        float orientation_,
        float rotation_,
        float angular_
    );

    virtual ~Player();
    virtual bool OnCreate();
    virtual void Render(float scale);
    virtual void Update(float deltaTime);
    virtual void HandleEvents(const SDL_Event& event);
};

#endif /* PLAYERBODY_H */
