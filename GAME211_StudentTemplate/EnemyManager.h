#pragma once
#include <Vector>
#include <Vector.h>
#include "Enemy.h"
#include "ChunkHandler.h"
#include "Camera.h"

class EnemyManager 
{
private:
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()
public:
	
	EnemyManager();

	//List of enemies and their faces
	std::vector<Enemy*> enemyList = {};
	std::vector<TileFaces> enemyFaces;

	//Spawn enemies
	std::vector<Enemy*> spawnEnemy(int amount);
	bool OnCreate();

	void setRenderer(SDL_Renderer* renderer_) { renderer = renderer_; } //renderer is defined in body

	//Render enemies
	void RenderEnemies(Camera camera);

	void Update(float deltaTime);
};