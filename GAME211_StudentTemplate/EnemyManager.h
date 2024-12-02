#pragma once
#include <Vector>
#include <Vector.h>
#include "Enemy.h"
#include "ChunkHandler.h"
#include "Camera.h"
#include "Player.h"

class EnemyManager
{
private:
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()
public:

	EnemyManager();

	//List of enemies and their faces
	std::vector<Enemy*> enemyList;
	std::vector<TileFaces> enemyFaces;

	//Spawn enemies
	void SpawnEnemy(int amount, Player* player_);
	bool OnCreate();
	void OnDestroy();
	void SetRegion(ChunkHandler* region_);
	void setRenderer(SDL_Renderer* renderer_) { renderer = renderer_; } //renderer is defined in body
	void AttackEnemy(Vec3 mouseCoord, float damage);
	bool mouseInsideObject(Vec3 mouseCoords, Body* body);
	//Render enemies
	void RenderEnemies(Camera camera);

	void Update(float deltaTime);
};