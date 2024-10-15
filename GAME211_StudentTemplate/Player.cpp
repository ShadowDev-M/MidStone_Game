#include "Player.h"

Player::Player(
    Vec3 pos_, Vec3 vel_, Vec3 accel_,
    float mass_,
    float radius_ = 0.0f,
    float orientation_ = 0.0f,
    float rotation_ = 0.0f,
    float angular_ = 0.0f
)
{
    pos = pos_;
    vel = vel_;
    accel = accel_;
    mass = mass_;
    radius = radius_;
    orientation = orientation_;
    rotation = rotation_;
    angular = angular_;

    image = nullptr;
}


bool Player::OnCreate()
{
   
    // sets up player image and texture
    playerImage = "Pacman.png";
    playerTexture = loadImage(playerImage);

    return true;
}

void Player::Render( float scale )
{   
    // Calls body entity render
    RenderEntity(scale, playerTexture);
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

void Player::OnDestroy()
{
    // Change to Debug::Info after
    std::cout << ("Deleting player assets: ", __FILE__, __LINE__);
    delete playerTexture;
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