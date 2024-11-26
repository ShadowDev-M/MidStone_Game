#include "Enemy.h"

Enemy::Enemy(
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

bool Enemy::OnCreate()
{
    textureFile = "textures/Blinky.png"; //Placeholder image
    SetTextureFile(textureFile);
    texture = loadImage(textureFile);

    // sets up enemy image and texture
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    hitbox.OnCreate(size.x, size.y, scale);

    return true;
}

void Enemy::Render(float scale)
{
    // Calls body entity render
    renderEntity(scale);
}

void Enemy::HandleEvents(const SDL_Event& event)
{

}

void Enemy::Update(float deltaTime)
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update(deltaTime);
    hitbox.CheckCollision(Vec2(pos.x,pos.y));
}

void Enemy::OnDestroy()
{
    // Change to Debug::Info after
    std::cout << ("Deleting enemy assets: ", __FILE__, __LINE__);
    delete texture;
    delete textureFile;

}