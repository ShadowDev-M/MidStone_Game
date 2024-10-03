#ifndef SCENEM_H
#define SCENEM_H

#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Scene.h"

using namespace MATH;
class SceneM : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()


	Body* playGameButton;
	SDL_Texture* playGameBTexture;

	//Setting up new stuff, important some from old framework
	// will put in a better place after to use everywhere

	// Rendering text using SDL_TFF is very costly 
	// because it always creates a new surface


	/// Load an image into a texture object.
	/// <param name="textureFile">image file</param>
	/// <returns>The SDL texture of this image</returns>
	SDL_Texture* loadImage(const char* textureFile);

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
	SceneM(SDL_Window* sdlWindow, GameManager* game_);
	~SceneM();
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

	//.pos
	// Takes game/physics coords of an object 
	// and multiples it by the projection matrix to get screen coords
	Vec3 screenCoords(Vec3 gameCoords);

	Vec3 worldCoords(Vec3 physicsCoords);

};

#endif
