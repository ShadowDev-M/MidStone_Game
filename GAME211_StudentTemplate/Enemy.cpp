#include "Enemy.h"
#include <random>

Enemy::Enemy(
	Vec3 pos_, Vec3 vel_, Vec3 accel_,
	float mass_,
	float radius_ = 0.0f,
	float orientation_ = 0.0f,
	float rotation_ = 0.0f,
	float angular_ = 0.0f,
	Player* player_ = nullptr
) : player(player_)
{
	pos = pos_;
	vel = vel_;
	accel = accel_;
	mass = mass_;
	patrolRadius = radius_;
	orientation = orientation_;
	rotation = rotation_;
	angular = angular_;
	State = patrol;
	image = nullptr;

	//Patrol state
	speed = 2;
	patrolRadius = 10;
	patrolTimer = patrolDelay;
	patrolDelay = 5;
	sightRange = 10;


	//Attack state
	attackRange = 2;
	attackCoolDown = 1.5f;
	damage = 2;
	attackTimer = attackCoolDown;
}

Enemy::Enemy(Vec3 pos_, float dmg, Player* player_) : player(player_)
{
	pos = pos_;
	damage = dmg;
	player = player_;
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

	initPos = pos;
	// sets up enemy image and texture
	//SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	//hitbox.OnCreate(size.x, size.y, scale);

	hitbox.OnCreate(size.x, size.y, 0.05f);
	hitbox.Subscribe(
		[this](const TileFaces& collidedObject) {
			onCollisionEnter(collidedObject);
		});




	return true;
}

void Enemy::Render(float scale)
{
	// Calls body entity render
	if (isMoving)
	{
		SDL_RenderDrawLine(renderer, pos.x, pos.y, newPos.x, newPos.y);

	}
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
	hitbox.CheckCollision(pos, vel);

	if (region != nullptr) {
		std::vector<TileFaces> tempFaces;

		permFaces = region->getFaces(Vec2(pos.x, pos.y), Vec2(vel.x, vel.y));

		hitbox.setObstacles(permFaces);
	}



	hitbox.CheckCollision(pos, vel);

	Body::Update(deltaTime);

	hitbox.CheckCollision(pos, vel);


	switch (State)
	{
	case Enemy::patrol:
		Patrol(deltaTime);
		break;
	case Enemy::attack:

		Attack(deltaTime);
		break;
	case Enemy::chase:
		Chase(deltaTime);
		break;
	case Enemy::dead:
		break;
	default:
		break;
	}

	if (isMoving)
		MoveTo(deltaTime);
	else
		vel = Vec3();

}



void Enemy::Patrol(float deltaTime)
{
	float playerDist = VMath::distance(pos, player->getPos());

	if (playerDist < attackRange)
	{
		State = attack;
		return;
	}

	if (playerDist < sightRange)
	{
		State = chase;
		return;
	}

	if (isMoving)
		return;
	patrolTimer -= deltaTime;

	if (patrolTimer <= 0)
	{
		//Generate a new pos
		float newPosX = GetRandomNumber(-patrolRadius, patrolRadius);
		float newPosY = GetRandomNumber(-patrolRadius, patrolRadius);
		newPos = Vec3(initPos.x + newPosX, initPos.y + newPosY, 0);

		//Reset timer and move
		patrolTimer = patrolDelay;
		State = patrol;
		isMoving = true;
	}
}

void Enemy::Attack(float deltaTime)
{
	float playerDist = VMath::distance(pos, player->getPos());

	//Attack to chase
	if (playerDist > attackRange)
	{
		State = chase;
		return;
	}

	attackTimer -= deltaTime;
	if (attackTimer < VERY_SMALL)
	{
		attackTimer = attackCoolDown;
		player->takeDamage(damage);

	}
}

void Enemy::Chase(float deltaTime)
{
	float playerDist = VMath::distance(pos, player->getPos());
	newPos = player->getPos();
	isMoving = true;


	//Chase to Patrol
	if (playerDist > sightRange)
	{
		State = patrol;
		isMoving = false;
		return;
	}

	//Chase to Attack
	if (playerDist < attackRange)
	{
		State = attack;
		isMoving = false;
	}

}

void Enemy::MoveTo(float deltaTime)
{
	Vec3 dist = newPos - pos;
	Vec3 dir = VMath::normalize(dist);

	//Enemy got to the destination
	if (VMath::mag(dist) < 1)
	{
		vel = Vec3();
		isMoving = false;
		return;
	}

	vel = Vec3(speed * dir.x, speed * dir.y, 0);
}


void Enemy::OnDestroy()
{
	// Change to Debug::Info after
	std::cout << ("Deleting enemy assets: ", __FILE__, __LINE__);
	delete texture;
	delete textureFile;

}

int Enemy::GetRandomNumber(int min, int max) {
	std::random_device rd;                         // Seed
	std::mt19937 gen(rd());                        // Mersenne Twister RNG
	std::uniform_int_distribution<> dist(min, max); // Uniform distribution
	return dist(gen);
}

void Enemy::setFaces(std::vector<TileFaces> faces_)
{
	hitbox.setObstacles(faces_);
}

void Enemy::Die()
{
	State = dead;

}

void Enemy::Damage(float damage_)
{
	healthpoints -= damage_;

	if (healthpoints <= 0)
		Die();

}

void Enemy::onCollisionEnter(const TileFaces& collidedObject)
{

	switch (collidedObject.objectTag)
	{
	case none:
		break;
	case wall || enemy:

		if (collidedObject.PointOne.y == collidedObject.PointTwo.y) {
			//
			if (abs(vel.y) != 0) {
				int direction = vel.y > 0 ? 1 : -1;

				if (isWallBouncingY == false)
					vel.y = -direction * 4.0f; // Reverse velocity to simulate bounce-back


				isWallBouncingY = true; // Trigger bounce-back state
			}
		}

		else if (collidedObject.PointOne.x == collidedObject.PointTwo.x) {
			// Vertical wall adjustment
			if (abs(vel.x) != 0) {

				int direction = vel.x > 0 ? 1 : -1;
				if (isWallBouncingX == false)
					vel.x = -direction * 4.0f; // Reverse velocity to simulate bounce-back

				isWallBouncingX = true;// Trigger bounce-back state
				printf("%f ", vel.x);
			}

		}
		break;

	default:
		break;
	}
}
