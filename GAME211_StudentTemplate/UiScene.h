#ifndef UISCENE_H
#define UISCENE_H

#include <MMath.h>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include <queue>
#include "UiText.h"
#include "UiPanel.h"

using namespace MATH;
class UiScene : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()

	Player* player;

	UiText text;

	//UI PANELS
	UiPanel panel;
	UiPanel space[5];

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
	UiScene(SDL_Window* sdlWindow, GameManager* game_);
	~UiScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	void refreshIcon();
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
	void ButtonTest();
	// Takes game/physics coords of an object 
	// and multiples it by the projection matrix to get screen coords
	Vec3 screenCoords(Vec3 gameCoords);
};

#endif
