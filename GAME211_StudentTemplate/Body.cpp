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


void Body::renderEntity(float scaleFactor)
{
    Vec3 screenCoords;

    // convert the position from game coords to screen coords.
    screenCoords = projectionMatrix * pos;

    // Get size of the input texture in pixels
    SDL_Point size{};
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    SDL_Rect dest = { screenCoords.x, screenCoords.y, size.x * scaleFactor, size.y * scaleFactor };

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI;

    SDL_RenderCopyEx(renderer, texture, nullptr, &dest,
        orientationDegrees, nullptr, SDL_FLIP_NONE);
}

void Body::renderPlayer(float scaleFactor, int frames)
{
    Uint32 ticks = SDL_GetTicks();
    Uint32 sprite = (ticks / 200) % frames;

    SDL_Rect srcrect = { sprite * (getImage()->w / frames), 0, getImage()->w / frames, getImage()->h };

    Vec3 screenCoords = projectionMatrix * pos;

    SDL_Point size{};
    SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
    SDL_Rect dest = { screenCoords.x, screenCoords.y, size.x * scaleFactor, size.y * scaleFactor };

    // Convert character orientation from radians to degrees.
    float orientationDegrees = orientation * 180.0f / M_PI;

    SDL_RenderCopyEx(renderer, texture, &srcrect, &dest,
        orientationDegrees, nullptr, SDL_FLIP_NONE);
}

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

void Body::changeTexture(const char* fileName)
{
    // Update position, call Update from base class
    textureFile = fileName;//Placeholder image
    SetTextureFile(textureFile);
    texture = loadImage(textureFile);
    // Image Surface used for animations
    setImage(IMG_Load(textureFile));
}


//bool Body::mouseInsideObject(Vec3 mouseCoords)
//{
//    if ((mouseCoords.x >= getPos().x - width) &&
//        (mouseCoords.x <= getPos().x + width) &&
//        (mouseCoords.y >= getPos().y - height) &&
//        (mouseCoords.y <= getPos().y + height)) {
//        return true;
//    }
//    return false;
//}



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
