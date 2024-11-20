#ifndef SCENEYB_H
#define SCENEYB_H

#include <MMath.h>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "Camera.h"
#include <queue>

using namespace MATH;
class SceneYB : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()

	Player* player;
	Enemy* enemy;



	EnemyManager* enemyManager;
	Camera camera;
	std::queue<Enemy*> enemyQueue;

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	SceneYB(SDL_Window* sdlWindow, GameManager* game_);
	~SceneYB();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};

#endif