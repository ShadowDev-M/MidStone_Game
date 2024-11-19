#ifndef SCENEC_H
#define SCENEC_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Scene.h"
#include "Player.h"
#include "Camera.h"


#include "Chunk.h"
#include "ChunkHandler.h"

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
	ChunkHandler RegionOne;
	Camera camera;
	
	Scene* scene;

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


	std::vector<TileInfo> changesIndex;
	std::vector<Body*> tiles;

	int tileOffset = 8;

	// One tile is 16x16 pixels * 3
	// Each object should follow 48 pixels
	// One chunk is made up of 16x16 tiles
	
	
	//Setting up new stuff, important some from old framework
	// will put in a better place after to use everywhere

	// Rendering text using SDL_TFF is very costly 
	// because it always creates a new surface
	float scalingFactor(SDL_Texture*& texture, Body* body);

	/// Generate a rectangle that will encompass a scaled version of the texture.	
	/// <param name="objectTexture">The texture object of the image</param>
	/// <param name="start_x">The new x location of the image's upper left corner</param>
	/// <param name="start_y">The new y location of the image's upper left corner</param>
	/// <param name="scale">The scale of the image </param>
	/// <returns>A rectangle that the texture will be rendered inside</returns>
	SDL_Rect scale(SDL_Texture* objectTexture,
		int start_x = 0, int start_y = 0, float scale = 1.0f);

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	SceneC(SDL_Window* sdlWindow, GameManager* game_);
	~SceneC();
	bool OnCreate();
	
	SDL_Texture* loadImage(Body* body);
	
	void OnDestroy();
	void Update(const float time);	
	void Render();
	void renderObject(Body* object, SDL_Texture* objectTexture);
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }

	//.pos
	// Takes game/physics coords of an object 
	// and multiples it by the projection matrix to get screen coords
	Vec3 worldToScreenCoords(Vec3 gameCoords);

	Vec3 ScreenToWorldCoords(Vec3 physicsCoords);

};

#endif
