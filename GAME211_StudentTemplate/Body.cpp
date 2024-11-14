#include "Body.h"

Body::Body()
{
    pos = Vec3();
    vel = Vec3();
    accel = Vec3();
	mass = 1.0f;
    radius = 0.0f;
    orientation = 0.0f;
    rotation = 0.0f;
    angular = 0.0f;

	image = nullptr;
}

Body::Body(
    Vec3 pos_, Vec3 vel_, Vec3 accel_,
    float mass_,
    float radius_ = 0.0f,
    float orientation_ = 0.0f,
    float rotation_ = 0.0f,
    float angular_ = 0.0f
)
{
    pos = pos_;
    vel = vel_;
    accel = accel_;
    mass = mass_;
    radius = radius_;
    orientation = orientation_;
    rotation = rotation_;
    angular = angular_;

    image = nullptr;
}

Body::Body(int hp, Vec3 pos_)
{
    healthpointsMax = hp;
    healthpoints = hp;
}

Body::~Body(){
}

bool Body::OnCreate()
{


    return true;
}

void Body::OnDestroy()
{

}


// Both loading and rendering can now be accessed through body and scenes using the same functions
SDL_Texture* Body::loadImage(const char* textureFile)
{
    // The following is a typical chunk of code for creating 
    // a texture in SDL

    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(textureFile);
    if (!loadedSurface)
    {
        std::cout << "Unable to load image " << textureFile <<
            "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!newTexture)
        {
            std::cout << "Unable to create texture " << textureFile <<
                "! SDL Error: " << SDL_GetError() << std::endl;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void Body::RenderEntity(float scale, SDL_Texture* entityTexture)
{
    Vec3 screenCoords;
    
    // convert the position from game coords to screen coords.
    screenCoords = projectionMatrix * pos;

    // Get size of the input texture in pixels
    
    SDL_QueryTexture(entityTexture, nullptr, nullptr, &size.x, &size.y);
    SDL_Rect dest = { screenCoords.x, screenCoords.y, size.x * scale, size.y * scale };

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI;

    SDL_RenderCopyEx(renderer, entityTexture, nullptr, &dest,
        orientationDegrees, nullptr, SDL_FLIP_NONE);

    //SDL_Rect myRect = { screenCoords.x, screenCoords.y, screenCoords.x + size.x * scale, screenCoords.y - size.y * scale };
    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    //SDL_RenderDrawRect(renderer, &myRect);
}

void Body::ApplyForce( Vec3 force_ ) {
    accel = force_ / mass;
}

void Body::Update( float deltaTime ){
    pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime);
    vel = vel + accel * deltaTime;
    // Update orientation
    orientation += rotation * deltaTime;
    rotation += angular * deltaTime;
}


// Remove later if not needed
void Body::HandleEvents( const SDL_Event& event )
{
    if ( event.type == SDL_MOUSEBUTTONDOWN )
    {
        printf("Mousedown\n");
    }
    else if ( event.type == SDL_KEYDOWN )
    {
        if ( event.key.keysym.scancode == SDL_SCANCODE_SPACE)
        {
            printf("Space\n");
        }
    }
    // etc
}
