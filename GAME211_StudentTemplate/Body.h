#ifndef BODY_H
#define BODY_H

#include <MMath.h>
#include <VMath.h>
#include <SDL.h>
#include <SDL_image.h>

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

	Vec3 imageSizeWorldCoords;
    SDL_Surface* image;
    SDL_Texture* texture;
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
	virtual ~Body();
    virtual void Update(float deltaTime);
    virtual void ApplyForce(Vec3 force_);
    virtual Vec3 getPos() { return pos; }
    virtual Vec3 getVel() { return vel; }
    virtual Vec3 getAccel() { return accel; }
    virtual float getMass() { return mass; }
    virtual float getOrientation() { return orientation; }
    virtual float getRotation() { return rotation; }
    virtual float getAngular() { return angular; }

    virtual void setImage(SDL_Surface* image_) { image = image_; }
    virtual SDL_Surface* getImage() { return image; }

    virtual void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_)
    {
        imageSizeWorldCoords = imageSizeWorldCoords_;
	}

    virtual void setTexture( SDL_Texture* texture_ ) { texture = texture_; }
    virtual SDL_Texture* getTexture() { return texture; }

     /// Set a new texture file for this body	
    /// <param name="textureFile_">The new texture file</param>
    virtual void SetTextureFile(const char* textureFile_) {
        textureFile = textureFile_;
    }

    /// <returns>The texture of this body</returns>
    virtual const char* GetTextureFile() {
        return textureFile;
    }


    virtual void HandleEvents( const SDL_Event& event );

	// Added this as public to deal with my demo
	// so that mouse position can be copied into a Body.
    virtual void setPos( Vec3 pos );

    //CUSTOM FUNCTIONS
    virtual void takeDamage(float damage) { healthpoints -= damage; }
    virtual void setItem(Item newItem) { currentItem = newItem; }

    //VARIABLES
    float healthpointsMax; //The max HP of the entity
    float healthpoints = healthpointsMax; 
    float walkSpeedMax; //The default speed of the entity
    Item currentItem; //Currently equipped item the entity is using

};

#endif /* BODY_H */
