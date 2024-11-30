#include "EnemyManager.h"

EnemyManager::EnemyManager()
{
	srand((unsigned)time(NULL)); //provide a seed value
}

std::vector<Enemy*> EnemyManager::spawnEnemy(int amount, Player* player_)
{
	for (int i = 0; i < amount; i++)
	{
		Vec2 newPos = Vec2(rand() % 5, rand() % 5);
		//Vec2 newPos = Vec2(14.0f, 7.875f);
		std::cout << "enemy position: ";
		newPos.print();
		std::cout << "\n";

		Enemy* myEnemy = new Enemy(Vec3(newPos.x, newPos.y, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0,player_);
		myEnemy->setRenderer(renderer);
		myEnemy->OnCreate();
		myEnemy->setWidth(1.0f);
		myEnemy->setHeight(1.0f);
		enemyList.push_back(myEnemy);
	}

	return enemyList;
}

bool EnemyManager::OnCreate()
{
	
	
	return true;
}

void EnemyManager::SetRegion(ChunkHandler* region_)
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList[i]->SetRegion(region_);
	}
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