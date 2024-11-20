#include "Player.h"
<<<<<<< Updated upstream
#include "Enemy.h"
=======
//#include "Camera.h"
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
    // sets up player image and texture
    playerImage = "Pacman.png";
    playerTexture = loadImage(playerImage);

=======
    textureFile = "textures/Pacman.png"; //Placeholder image
    SetTextureFile(textureFile);
    texture = loadImage(textureFile);

    
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    hitbox.OnCreate(size.x, size.y, scale);
>>>>>>> Stashed changes
    return true;
}

void Player::Render(float scale)
{   
    // Calls body entity render
    renderEntity(scale);
    
    
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
    //if (VMath::mag(vel) > walkSpeedMax)
    //{
    //    vel = VMath::normalize(vel) * walkSpeedMax; //normalize our speed to prevent this, multiply by our max speed to make it more natural
    //}

}

void Player::Update( float deltaTime )
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update( deltaTime );

}

bool Player::enemyCollision(Body* other)
{
    if (pos.x > other->getPos().x && pos.x < other->getPos().x + other->width
        && pos.y < other->getPos().y && pos.y > other->getPos().y - other->height) 
    {
        return true;
        std::cout << "COLLISION DETECTED" << std::endl;
    }

    return false;
}

void Player::OnDestroy()
{
    // Change to Debug::Info after
    std::cout << ("Deleting player assets: ", __FILE__, __LINE__);
<<<<<<< Updated upstream
    delete playerTexture;
=======
    delete texture;
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


bool Player::enemyCollision(Body* other)
{
    Vec3 playerPos = projectionMatrix * pos; //Need to convert to game space to use SDL_Rect
    Vec3 playerHitboxOffset = projectionMatrix * hitboxOffset;

    SDL_Rect playerRect = { playerPos.x + playerHitboxOffset.x / 2.0f, playerPos.y + playerHitboxOffset.y / 2.0f, widthScreen - playerHitboxOffset.x, heightScreen - playerHitboxOffset.y }; //Width and height are already multiplied by scale in on create

    Vec3 enemyPos = projectionMatrix * other->getPos(); //Need to convert to game space to use SDL_Rect
    Vec3 enemyHitboxOffset = projectionMatrix * hitboxOffset;

    SDL_Rect enemyRect = { enemyPos.x + enemyHitboxOffset.x / 2.0f, enemyPos.y + enemyHitboxOffset.y / 2.0f, other->widthScreen - enemyHitboxOffset.x, other->heightScreen - enemyHitboxOffset.y }; //Width and height are already multiplied by scale in on create

    if (SDL_HasIntersection(&playerRect, &enemyRect))
    {
        return true;
    }

    return false;
>>>>>>> Stashed changes
}