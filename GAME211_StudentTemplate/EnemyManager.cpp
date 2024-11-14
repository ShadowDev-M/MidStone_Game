#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()
}

EnemyManager::EnemyManager(Scene* scene_)
{
	activeScene = scene_;
}

std::vector<Enemy*> EnemyManager::spawnEnemy(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Enemy* myEnemy = new Enemy(Vec3(enemyPositions[i].x, enemyPositions[i].y, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
		myEnemy->OnCreate();
		myEnemy->setRenderer(activeScene->getRenderer());

		enemyList.push_back(myEnemy);
	}

	return enemyList;
}

void EnemyManager::RenderEnemies()
{
	for (Enemy* enemy : enemyList)
	{
		enemy->Render();
	}
}

void EnemyManager::Update(float deltaTime)
{
	for (Enemy* enemy : enemyList)
	{
		enemy->setProjection(projectionMatrix);
		enemy->setInverse(inverseProjection);
	}
}