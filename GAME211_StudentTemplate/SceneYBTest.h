#pragma once
#ifndef SCENEYBTEST_H
#define SCENEYBTEST_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Scene.h"
#include "Player.h"
#include "Camera.h"

#include "Enemy.h"
#include "EnemyManager.h"

#include "Chunk.h"
#include "ChunkHandler.h"

#include "BoxCollider.h"

using namespace MATH;
class SceneYBTest : public Scene {
private:

	// Screen/Level Size
	static const int SCREEN_WIDTH = 1920;
	static const int SCREEN_HEIGHT = 1080;

	// The cameras current location
	float LEVEL_WIDTH = SCREEN_WIDTH * 16 / SCREEN_HEIGHT;
	float LEVEL_HEIGHT = LEVEL_WIDTH * 9 / 16;



	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4     inverseProjection;	// set in OnCreate()
	bool testh;
	Player* player;
	ChunkHandler RegionOne;
	Camera camera;

	Scene* scene;

	EnemyManager* enemyManager;
	Enemy* enemy;

	

	// Testing the loading of tiles
	// Starting off with a single tile and assigning it an ID

	Body* stoneTile;
	SDL_Texture* stoneTileTexture;
	Body* grassTile;
	SDL_Texture* grassTileTexture;

	Body* ghost;
	SDL_Texture* ghostTexture;

	Body* sword;
	SDL_Texture* swordTexture;

	//Enemy* enemy;



	std::vector<TileInfo> changesIndex;
	std::vector<Body*> tiles;

	int tileOffset = 8;

	// One tile is 16x16 pixels * 3
	// Each object should follow 48 pixels
	// One chunk is made up of 16x16 tiles




public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	SceneYBTest(SDL_Window* sdlWindow, GameManager* game_);
	~SceneYBTest();
	bool OnCreate();



	void renderLinesMethod(TileFaces info) {
		SDL_RenderDrawLine(renderer, info.PointOne.x, info.PointOne.y, info.PointTwo.x, info.PointTwo.y);
	};
	std::vector<TileFaces> getFacesFromChunks(Vec2 entityPos_, Vec2 velVector_) { return RegionOne.getFaces(entityPos_, velVector_); }
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