#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <MMath.h>
#include "Body.h"
#include "GameManager.h"
#include "Player.h"
// Main goal for the camera is to focus on a viewport while screen is being rendered outside of it
// Done by taking screen dimension, scene dimensions, and "World" dimensions


class Camera
{
private:


    // Max Screen/Level Size
    static const int SCREEN_WIDTH = 1920;
    static const int SCREEN_HEIGHT = 1080;

    // The Cameras Current Location In Physics Space
    // This sets up the physics space/what the camera renders
    float LEVEL_WIDTH = SCREEN_WIDTH * 16 / SCREEN_HEIGHT;
    float LEVEL_HEIGHT = LEVEL_WIDTH * 9 / 16;




    float xAxis = LEVEL_WIDTH;	// scene width, in game coords, set in constructor
    float yAxis = LEVEL_HEIGHT;	// scene height, in game coords, set in constructor

    Matrix4 projectionMatrix;	// set in OnCreate()
    Matrix4     inverseProjection;	// set in OnCreate()

    SDL_Window* window;		// an SDL window with a SDL renderer
    SDL_Renderer* renderer;	// the renderer associated with SDL window

    GameManager game;

    int WINDOW_WIDTH = game.getWindowWidth();
    int WINDOW_HEIGHT = game.getWindowHeight();

    Player player;

public:
    Camera();
    Camera(SDL_Window* sdlWindow_);
    ~Camera();
    bool OnCreate();
    void Update(const float deltaTime);
    void OnDestroy();
    void Render() const;
    void HandleEvents(const SDL_Event& sdlEvent);

    // 28
    float getXAxis() const { return LEVEL_WIDTH; }
    // 15.75
    float getYAxis() const { return LEVEL_HEIGHT; }

    // Returns Projection Matrix
    Matrix4 getProjectionMatrix() const { return projectionMatrix; }
    Matrix4 getInverseMatrix() const { return inverseProjection; }
    int getWindowWidth() { return WINDOW_WIDTH; }
    int getWindowHeight() { return WINDOW_HEIGHT; }

    

    void cameraFollowsPlayer(Player* player, SDL_Window* window);

    ////.pos
    //// Takes game/physics coords of an object 
    //// and multiples it by the projection matrix to get screen coords
    //Vec3 screenCoords(Vec3 gameCoords);

    //Vec3 worldCoords(Vec3 physicsCoords);

    //Matrix4 getProjectionMatrix() { return projectionMatrix; }
    //Matrix4 getInverseMatrix() { return inverseProjection; }


    /// Load an image into a texture object.
    /// <param name="textureFile">image file</param>
    /// <returns>The SDL texture of this image</returns>
    SDL_Texture* loadImage(const char* textureFile, SDL_Renderer* renderer);

    /// Generate a rectangle that will encompass a scaled version of the texture.	
    /// <param name="objectTexture">The texture object of the image</param>
    /// <param name="start_x">The new x location of the image's upper left corner</param>
    /// <param name="start_y">The new y location of the image's upper left corner</param>
    /// <param name="scale">The scale of the image </param>
    /// <returns>A rectangle that the texture will be rendered inside</returns>
    SDL_Rect scale(SDL_Texture* objectTexture,
        int start_x = 0, int start_y = 0, float scale = 1.0f);

    /// <summary>
    /// Images will scale acording to screen size properly while maintaining proper physics.
    /// </summary>
    /// <param name="texture"></param>The texture object of the image
    /// <param name="body"></param>The body of the object
    /// <returns></returns>
    float scalingFactor(SDL_Texture*& texture, Body* body);

    void renderObject(Body* object, SDL_Texture* objectTexture, SDL_Renderer* renderer);

    Vec3 worldToScreenCoords(Vec3 gameCoords);

    Vec3 ScreenToWorldCoords(Vec3 physicsCoords);
};

