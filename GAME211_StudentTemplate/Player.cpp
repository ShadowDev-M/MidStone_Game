//
//  Player.cpp
//  DemoAI
//
//  Created by Gail Harris on 2021-Dec-23.
//

#include "Player.h"

bool Player::OnCreate()
{
    image = IMG_Load( "Pacman.png" ); //Placeholder image
    SDL_Renderer *renderer = game->getRenderer();
    texture = SDL_CreateTextureFromSurface( renderer, image );
    if (image == nullptr) {
        std::cerr << "Can't open the image" << std::endl;
        return false;
    }
    return true;
}

void Player::Render( float scale )
{
    // This is why we need game in the constructor, to get the renderer, etc.
    SDL_Renderer *renderer = game->getRenderer();
    Matrix4 projectionMatrix = game->getProjectionMatrix();

    // square represents the position and dimensions for where to draw the image
    SDL_Rect square;
    Vec3 screenCoords;
    float w, h;

    // convert the position from game coords to screen coords.
    screenCoords = projectionMatrix * pos;

    // Scale the image, in case the .png file is too big or small
    w = image->w * scale;
    h = image->h * scale;

    // The square's x and y values represent the top left corner of 
    // where SDL will draw the .png image.
    // The 0.5f * w/h offset is to place the .png so that pos represents the center
    // (Note the y axis for screen coords points downward, hence subtraction!!!!)
    square.x = static_cast<int>(screenCoords.x - 0.5f * w);
    square.y = static_cast<int>(screenCoords.y - 0.5f * h);
    square.w = static_cast<int>(w);
    square.h = static_cast<int>(h);

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI ;

    SDL_RenderCopyEx( renderer, texture, nullptr, &square,
        orientationDegrees, nullptr, SDL_FLIP_NONE );
}

void Player::HandleEvents( const SDL_Event& event )
{
    //event.key.repeat == 0 prevents weirdness with normalizing the velocity later on
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        if (event.key.keysym.scancode == SDL_SCANCODE_W)
            vel.y = walkSpeedMax;
        
        if (event.key.keysym.scancode == SDL_SCANCODE_S)
            vel.y = -walkSpeedMax;

        if (event.key.keysym.scancode == SDL_SCANCODE_D)
            vel.x = walkSpeedMax;
        
        if (event.key.keysym.scancode == SDL_SCANCODE_A)
            vel.x = -walkSpeedMax;
    }

    //If we release one of the keys, stop velocity in that direction
    if (event.type == SDL_KEYUP)
    {
        //All the vel checks are needed because otherwise controls can be finicky if moving in one direction and releasing a different key
        if (event.key.keysym.scancode == SDL_SCANCODE_W && vel.y >= 0)
            vel.y = 0.0f;

        if (event.key.keysym.scancode == SDL_SCANCODE_S && vel.y <= 0)
            vel.y = 0.0f;

        if (event.key.keysym.scancode == SDL_SCANCODE_D && vel.x >= 0)
            vel.x = 0.0f;

        if (event.key.keysym.scancode == SDL_SCANCODE_A && vel.x <= 0)
            vel.x = 0.0f;
    }

    //Don't exceed our max speed when moving diagonally
    if (VMath::mag(vel) > walkSpeedMax)
    {
        vel = VMath::normalize(vel) * walkSpeedMax; //normalize our speed to prevent this, multiply by our max speed to make it more natural
    }
}

void Player::Update( float deltaTime )
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update( deltaTime );

}

void Player::takeDamage(float damage)
{
    //The player takes damage
    healthpoints -= damage;
}

void Player::setItem(Item newItem)
{
    //Set the player's current item to the new item
    currentItem = newItem;
}