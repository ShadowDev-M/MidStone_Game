#ifndef BODY_H
#define BODY_H

#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Item.h"

using namespace MATH;

class Body {
protected:
	// inherited classes can access this
    class GameManager* game;

	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
    float orientation;		// facing this direction
    float rotation;			// rotating at this speed (radians per second?)
    float angular;          // angular acceleration
    float radius;           // for getting near walls

    // Mostly rendering stuff
	Vec3 imageSizeWorldCoords;
    SDL_Surface* image;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    Matrix4 projectionMatrix;
    Matrix4 inverseProjection;

    // For new texture rendering
    const char* textureFile = "";

public:
    Body();
    Body(
        Vec3 pos_, Vec3 vel_, Vec3 accel_,
        float mass_,
        float radius_,
        float orientation_,
        float rotation_,
        float angular_
    );
    Body(int hp, Vec3 pos_);
    SDL_Point size{};

    //DESTRUCTOR
    virtual ~Body();

    //ESSENTIAL FUNCTIONS
    virtual bool OnCreate();
    virtual void OnDestroy();
    virtual void Update(float deltaTime);
    virtual void HandleEvents(const SDL_Event& event);

    //PHYSICS FUNCTIONS
    //Getters
    virtual Vec3 getPos() { return pos; }
    virtual Vec3 getVel() { return vel; }
    virtual Vec3 getAccel() { return accel; }
    virtual float getMass() { return mass; }
    virtual float getOrientation() { return orientation; }
    virtual float getRotation() { return rotation; }
    virtual float getAngular() { return angular; }

    //Other
    virtual void ApplyForce(Vec3 force_);
    virtual void setPos(Vec3 pos_) { pos = pos_; }

    //TEXTURES AND IMAGES
    virtual void setImage(SDL_Surface* image_) { image = image_; }
    virtual SDL_Surface* getImage() { return image; }
    virtual void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_) { imageSizeWorldCoords = imageSizeWorldCoords_; }
    virtual void setTexture(SDL_Texture* texture_) { texture = texture_; }
    virtual void renderEntity(float scaleFactor);
    virtual void renderPlayer(float scaleFactor, int frames);
    virtual Vec3 getImageSizeWorldCoords() { return imageSizeWorldCoords; }
    virtual SDL_Texture* getTexture() { return texture; }
    virtual SDL_Texture* loadImage(const char* textureFile);
    virtual void setScale(float scale_) { scale = scale_;  }
    // Extracted function that sets and loads a new texture
    virtual void changeTexture(const char* fileName);
    
    //virtual bool mouseInsideObject(Vec3 mouseCoords);
    

    /// Set a new texture file for this body	
   /// <param name="textureFile_">The new texture file</param>
    virtual void SetTextureFile(const char* textureFile_) {
        textureFile = textureFile_;
    }

    /// <returns>The texture of this body</returns>
    virtual const char* GetTextureFile() {
        return textureFile;
    }

    //CUSTOM FUNCTIONS
    virtual void takeDamage(float damage) { healthpoints -= damage; }
    virtual void setItem(Item newItem) { currentItem = newItem; }
    virtual void setHealthPoints(float entityHealth) { healthpointsMax = entityHealth; healthpoints = entityHealth; }
    
    virtual void setWidth(float w_) { width = w_; }
    virtual void setHeight(float h_) { height = h_; }
    virtual float getWidth() { return width; }
    virtual float getHeight() { return height; }
    virtual void setProjection(Matrix4 projectionMatrix_) { projectionMatrix = projectionMatrix_; }
    virtual void setInverse(Matrix4 inverseProjection_) { inverseProjection = inverseProjection_; }

    //VARIABLES

    //Rendering and Collision
    float width;
    float height;
    float scale = 1.0f;

    float widthScreen;
    float heightScreen;

    Vec3 hitboxOffset;

    float healthpointsMax; //The max HP of the entity
    float healthpoints = healthpointsMax;
    float walkSpeedMax; //The default speed of the entity
    Item currentItem; //Currently equipped item the entity is using
};

#endif /* BODY_H */
