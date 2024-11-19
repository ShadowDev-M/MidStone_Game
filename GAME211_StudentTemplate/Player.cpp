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
    SDL_QueryTexture(playerTexture, nullptr, nullptr, &size.x, &size.y);
    hitbox.OnCreate(size.x, size.y, 0.1f);
    hitbox.Subscribe(
        [this](const TileFaces& collidedObject) {
            onCollisionTrigger(collidedObject);
        });

    //hitbox.Subscribe(onCollisionTrigger);
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
   // if (VMath::mag(vel) > walkSpeedMax)
   // {
    //    vel = VMath::normalize(vel) * walkSpeedMax; //normalize our speed to prevent this, multiply by our max speed to make it more natural
   // }
}

void Player::Update( float deltaTime )
{
    // Update position, call Update from base class
    
    
    // Note that would update velocity too, and rotation motion
    
    //hitbox.setObstacles(hitFaces);

    //hitFaces.empty();
    Body::Update( deltaTime );

    //std::cout << region->getFaces(Vec2(pos.x, pos.y), Vec2(vel.x, vel.y)).objectTag << std::endl;
    if (region != nullptr) {
        std::vector<TileFaces> tempFaces;
        tempFaces.push_back(region->getFaces(Vec2(pos.x, pos.y), Vec2(vel.x, vel.y)));
        permFaces.push_back(region->getFaces(Vec2(pos.x, pos.y), Vec2(vel.x, vel.y)));
        
        hitbox.setObstacles(permFaces);
        //SDL_RenderDrawLine(renderer, 0, 0, 1, 1);
    }
    hitbox.CheckCollision(Vec2(pos.x,pos.y));
    

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



void Player::onCollisionTrigger(const TileFaces& collidedObject)
{
    switch (collidedObject.objectTag)
    {
    case none:
        break;
    case wall:
        if (collidedObject.PointOne.y == collidedObject.PointTwo.y) {
            // Horizontal wall adjustment
            if (vel.y < 0) { // Moving down
                pos.y += hitbox.DetectPenetration(collidedObject,pos,vel); // Move player back up
                vel.y = 0; // Stop downward movement
            }
            else { // Moving up
                pos.y -= hitbox.DetectPenetration(collidedObject, pos, vel); // Move player back down
                vel.y = 0; // Stop upward movement
            }
        }
        else {
            // Vertical wall adjustment
            if (vel.x > 0) { // Moving right
                pos.x += hitbox.DetectPenetration(collidedObject, pos, vel); // Move player back to the left
                vel.x = 0; // Stop rightward movement
            }
            else { // Moving left
                pos.x -= hitbox.DetectPenetration(collidedObject, pos, vel); // Move player back to the right
                vel.x = 0; // Stop leftward movement
            }
        }
        break;

    case enemy:
        std::cout << "\nplayer gets damaged";
        break;

    case loot:
        
        break;

    default:
        break;
    }
}
