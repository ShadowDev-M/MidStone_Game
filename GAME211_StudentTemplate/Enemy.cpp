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

Enemy::Enemy(Vec3 pos_, float dmg)
{
    pos = pos_;
    damage = dmg;
}

bool Enemy::OnCreate()
{
    textureFile = "textures/Blinky.png"; //Placeholder image
    SetTextureFile(textureFile);
    texture = loadImage(textureFile);
    hitFaces.resize(4);
    //1
    hitFaces[0].PointOne = Vec2(pos.x, pos.y);
    hitFaces[0].PointTwo = Vec2(pos.x, pos.y - height);
    hitFaces[0].objectTag = enemy;

    //2
    hitFaces[1].PointOne = Vec2(pos.x + width, pos.y);
    hitFaces[1].PointTwo = Vec2(pos.x + width, pos.y - height);
    hitFaces[1].objectTag = enemy;
    //3
    hitFaces[2].PointOne = Vec2(pos.x, pos.y);
    hitFaces[2].PointTwo = Vec2(pos.x + width, pos.y);
    hitFaces[2].objectTag = enemy;
    //4
    hitFaces[3].PointOne = Vec2(pos.x, pos.y - height);
    hitFaces[3].PointTwo = Vec2(pos.x + width, pos.y - height);
    hitFaces[3].objectTag = enemy;


    // sets up enemy image and texture
    //SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    //hitbox.OnCreate(size.x, size.y, scale);



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


    //1
    hitFaces[0].PointOne = Vec2(pos.x, pos.y);
    hitFaces[0].PointTwo = Vec2(pos.x, pos.y - height);
    //2
    hitFaces[1].PointOne = Vec2(pos.x + width, pos.y);
    hitFaces[1].PointTwo = Vec2(pos.x + width, pos.y - height);
    //3
    hitFaces[2].PointOne = Vec2(pos.x, pos.y);
    hitFaces[2].PointTwo = Vec2(pos.x + width, pos.y);
    //4
    hitFaces[3].PointOne = Vec2(pos.x, pos.y - height);
    hitFaces[3].PointTwo = Vec2(pos.x + width, pos.y - height);

    hitbox.setObstacles(hitFaces);



    Body::Update(deltaTime);
    hitbox.CheckCollision(pos,vel);
}

void Enemy::OnDestroy()
{
    // Change to Debug::Info after
    std::cout << ("Deleting enemy assets: ", __FILE__, __LINE__);
    delete texture;
    delete textureFile;

}