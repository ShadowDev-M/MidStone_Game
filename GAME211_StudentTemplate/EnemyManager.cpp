#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	srand((unsigned)time(NULL)); //provide a seed value
}

std::vector<Enemy*> EnemyManager::spawnEnemy(int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Vec2 newPos = Vec2(rand() % 5, rand() % 5);
		//Vec2 newPos = Vec2(14.0f, 7.875f);
		std::cout << "enemy position: ";
		newPos.print();
		std::cout << "\n";

		Enemy* myEnemy = new Enemy(Vec3(newPos.x, newPos.y, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
		myEnemy->setRenderer(renderer);
		myEnemy->OnCreate();
		myEnemy->setWidth(0.5f);
		myEnemy->setHeight(0.5f);
		//myEnemy->hitFaces
		//myEnemy->permFaces 

		enemyList.push_back(myEnemy);
	}

	return enemyList;
}

bool EnemyManager::OnCreate()
{
	
	
	return true;
}

void EnemyManager::RenderEnemies(Camera localCamera)
{
	for (Enemy* enemy : enemyList)
	{
		localCamera.renderObject(enemy, enemy->getTexture(), renderer);
	}
}

void EnemyManager::Update(float deltaTime)
{
	enemyFaces.clear();
	for (Enemy* enemy : enemyList)
	{
		enemy->Update(deltaTime);
		for (int i = 0; i < 4; i++)
		{
			enemyFaces.push_back(enemy->hitFaces[i]);
		}
		//enemy->setProjection(projectionMatrix);
		//enemy->setInverse(inverseProjection);
	}
		

	
}