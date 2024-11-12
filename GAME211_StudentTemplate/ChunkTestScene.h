#ifndef SCENEC_H
#define SCENEC_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Scene.h"
#include "Player.h"

#include "Chunk.h"
#include "ChunkHandler.h"

using namespace MATH;
class SceneC : public Scene {
private:

	static const int LEVEL_WIDTH = 1920;
	static const int LEVEL_HEIGHT = 1080;

	//Screen dimension constants
	static const int SCREEN_WIDTH = 1000;
	static const int SCREEN_HEIGHT = 600;


	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4     inverseProjection;	// set in OnCreate()
	bool testh;
	Player* player;
	ChunkHandler RegionOne;

	// Testing the loading of tiles
	// Starting off with a single tile and assigning it an ID

	Body* stoneTile;
	SDL_Texture* stoneTileTexture;
	Body* grassTile;
	SDL_Texture* grassTileTexture;

	Body* ghost;
	SDL_Texture* ghostTexture;

	//Body* ghost;
	//SDL_Texture* ghostTexture;

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };



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


	/// Load an image into a texture object.
	/// <param name="textureFile">image file</param>
	/// <returns>The SDL texture of this image</returns>
	SDL_Texture* loadImage(const char* textureFile);

	float scalingFactor(SDL_Texture*& texture, float& textureScale, Body* body);

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
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }

	void moveCamera();

	//.pos
	// Takes game/physics coords of an object 
	// and multiples it by the projection matrix to get screen coords
	Vec3 screenCoords(Vec3 gameCoords);

	Vec3 worldCoords(Vec3 physicsCoords);

};

#endif
