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
    textureFile = "textures/Pacman.png"; //Placeholder image
    SetTextureFile(textureFile);
    texture = loadImage(textureFile);
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    hitbox.OnCreate(size.x, size.y, 0.1f);
    hitbox.Subscribe(
        [this](const TileFaces& collidedObject) {
            onCollisionEnter(collidedObject);
        }, [this](const TileFaces& collidedObject) {
            onCollisionExit(collidedObject);
        });

    //hitbox.Subscribe(onCollisionTrigger);
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

        isWallBouncing = false;
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
    
    hitbox.CheckCollision(pos,vel);
     
    if (isWallBouncing) {
        // Gradually reduce horizontal velocity
        if (fabs(vel.x) > 0.01f) {
            vel.x *= wallBounceDecay; // Apply damping
        }
        else {
            vel.x = 0; // Stop when velocity is small enough
        }

        // Gradually reduce vertical velocity
        if (fabs(vel.y) > 0.01f) {
            vel.y *= wallBounceDecay; // Apply damping
        }
        else {
            vel.y = 0; // Stop when velocity is small enough
        }

        // Stop bounce-back when both velocities are zero
        if (vel.x == 0 && vel.y == 0) {
            isWallBouncing = false; // End bounce-back state
        }
    }

}

void Player::OnDestroy()
{
    // Change to Debug::Info after
    std::cout << ("Deleting player assets: ", __FILE__, __LINE__);
    //delete textureFile;
    //delete texture;
}


void Player::onCollisionEnter(const TileFaces& collidedObject)
{
    
    switch (collidedObject.objectTag)
    {
    case none:
        break;
    case wall:
                
        if (collidedObject.PointOne.y == collidedObject.PointTwo.y) {
            // Horizontal wall adjustment
            if (vel.y != 0) {
                vel.y = -vel.y; // Reverse velocity to simulate bounce-back
                isWallBouncing = true; // Trigger bounce-back state
            }
        }
        else {
            // Vertical wall adjustment
            if (vel.x != 0) {
                vel.x = -vel.x; // Reverse velocity to simulate bounce-back
                isWallBouncing = true; // Trigger bounce-back state
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

void Player::onCollisionExit(const TileFaces& collidedObject)
{
    std::cout << "Exit Collision";
}
