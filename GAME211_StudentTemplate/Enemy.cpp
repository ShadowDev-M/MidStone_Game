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
    enemyImage = "Blinky.png"; //Placeholder image
    enemyTexture = loadImage(enemyImage);
    SetTextureFile(enemyImage);

    // sets up player image and texture
    SDL_Surface* enemySurface = IMG_Load(enemyImage);
    setWidth(enemySurface->w); //This is in pixels
    setHeight(enemySurface->h); //This is in pixels

    scale = 0.2f;

    widthScreen = enemySurface->w * scale;
    heightScreen = enemySurface->h * scale;

    return true;
}

void Enemy::Render(float scale)
{
    // Calls body entity render
    RenderEntity(scale, enemyTexture);
}

void Enemy::HandleEvents(const SDL_Event& event)
{

}

void Enemy::Update(float deltaTime)
{
    // Update position, call Update from base class
    // Note that would update velocity too, and rotation motion

    Body::Update(deltaTime);
}

void Enemy::OnDestroy()
{
    // Change to Debug::Info after
    std::cout << ("Deleting enemy assets: ", __FILE__, __LINE__);
    delete enemyImage;
    delete enemyTexture;
}