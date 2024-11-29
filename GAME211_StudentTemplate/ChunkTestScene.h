#ifndef SCENEC_H
#define SCENEC_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Scene.h"
#include "Player.h"
#include "Camera.h"

#include "Enemy.h"


#include "Chunk.h"
#include "ChunkHandler.h"

#include "BoxCollider.h"

using namespace MATH;
class SceneC : public Scene {
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
	Enemy* enemy;
	ChunkHandler RegionOne;
	Camera camera;
	
	Scene* scene;

	// Testing the loading of tiles
	// Starting off with a single tile and assigning it an ID

	Body* stoneTile;
	SDL_Texture* stoneTileTexture;
	Body* grassTile;
	SDL_Texture* grassTileTexture;

	Body* sword;
	SDL_Texture* swordTexture;

	//Enemy* enemy;

	// Mouse coords
	int mouseOffSet = -5;
	int mouseX;
	int mouseY;
	Vec3 mousePhysicsCoords;

	bool mouseInsideEnemy(Vec3 mouseCoords, Body* body);
	SDL_Event event;

	int tempHealth = 5;
	int tempDamage = 3;

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
	SceneC(SDL_Window* sdlWindow, GameManager* game_);
	~SceneC();
	bool OnCreate();
	

	
	void renderLinesMethod(TileFaces info) {
		SDL_RenderDrawLine(renderer, info.PointOne.x, info.PointOne.y, info.PointTwo.x, info.PointTwo.y);
	};
	std::vector<TileFaces> getFacesFromChunks(Vec2 entityPos_, Vec2 velVector_) { return RegionOne.getFaces(entityPos_, velVector_); }
	void OnDestroy();
	void Update(const float time);	
	void Render();
	SDL_Rect PlayerAnimation(int frames);
	void HandleEvents(const SDL_Event& event);
	void MoveSword(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};

#endif
