#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Body.h"

// Main goal for the camera is to focus on a viewport while screen is being rendered outside of it
// Done by taking screen dimension, scene dimensions, and "World" dimensions


class Camera
{
private:
	//screen //camera

public:
	Camera();
	~Camera();
	bool OnCreate();
	void OnDestroy();
	void Render() const;
	void HandleEvents(const SDL_Event& sdlEvent);


    Quaternion orientation;
    Vec3 position;
    Matrix4 projection;
    Matrix4 view;



    ///// Load an image into a texture object.
    ///// <param name="textureFile">image file</param>
    ///// <returns>The SDL texture of this image</returns>
    //SDL_Texture* loadImage(const char* textureFile);

    ///// Generate a rectangle that will encompass a scaled version of the texture.	
    ///// <param name="objectTexture">The texture object of the image</param>
    ///// <param name="start_x">The new x location of the image's upper left corner</param>
    ///// <param name="start_y">The new y location of the image's upper left corner</param>
    ///// <param name="scale">The scale of the image </param>
    ///// <returns>A rectangle that the texture will be rendered inside</returns>
    //SDL_Rect scale(SDL_Texture* objectTexture,
    //    int start_x = 0, int start_y = 0, float scale = 1.0f);

    ////.pos
    //// Takes game/physics coords of an object 
    //// and multiples it by the projection matrix to get screen coords
    //Vec3 screenCoords(Vec3 gameCoords);

    //Vec3 worldCoords(Vec3 physicsCoords);

    //Matrix4 getProjectionMatrix() { return projectionMatrix; }
    //Matrix4 getInverseMatrix() { return inverseProjection; }
};

