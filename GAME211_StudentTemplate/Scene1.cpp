#include "Scene1.h"
#include <VMath.h>
#include "Chunk.h"
#include "ChunkHandler.h"


// See notes about this constructor in Scene1.h.
Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

// To render chunks and set id to tiles need to setup camera first
// Once camera is set, use it to only render tiles inside the camera (good for optimizaion)

// Once that is done, setup attaching tile ids to specific images to load in. 

bool Scene1::OnCreate() {
	// Check to make sure loading scene works
	std::cout << "Entering Scene1" << std::endl;
	
	int w, h;
	SDL_GetWindowSize(window,&w,&h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	// This way of rendering the player is fine since most of the information for the player is stored in its own class
	// However any new rendering should be done with the new methods

	// Set player image to PacMan
	SDL_Surface* playerImage;
	SDL_Texture* playerTexture;

	playerImage = IMG_Load("pacman.png");
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
	
	// Keeping this in for now to fix merge conflict
	game->getPlayer()->setImage(playerImage);
	game->getPlayer()->setTexture(playerTexture);

	ChunkHandler RegionOne;

	std::vector<TileInfo> changesIndex = {
		{0,0,0}, {0,1,1}, {0,2,1}, {0,3,1}, {0,4,1}, {0,5,1}, {0,6,1}, {0,7,1}, {0,8,1}, {0,9,1}, {0,10,1}, {0,11,1}, {0,12,1}, {0,13,1}, {0,14,1}, {0,15,1},
		{1,0,0}, {1,1,1}, {1,2,1}, {1,3,1}, {1,4,1}, {1,5,1}, {1,6,1}, {1,7,1}, {1,8,1}, {1,9,1}, {1,10,1}, {1,11,1}, {1,12,1}, {1,13,1}, {1,14,1}, {1,15,1},
		{2,0,1}, {2,1,1}, {2,2,1}, {2,3,1}, {2,4,1}, {2,5,1}, {2,6,1}, {2,7,1}, {2,8,1}, {2,9,1}, {2,10,1}, {2,11,1}, {2,12,1}, {2,13,1}, {2,14,1}, {2,15,1} };



	RegionOne.setTile(changesIndex);

	TileFaces intersectedTile = RegionOne.getFaces(Vec2(4.5, 6.5), Vec2(-4.0, 2.0));

	// Print the intersected tiles
	std::cout << " (" << intersectedTile.PointOne.x << ", " << intersectedTile.PointOne.y << ") (" << intersectedTile.PointTwo.x << ", " << intersectedTile.PointTwo.y << ")\n";


	//RegionOne.getFaces(Vec2(0.5, 0.7), Vec2(20.3, 30.4));


	return true;
}

void Scene1::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);

	
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// 

	

	// render the player
	game->RenderPlayer(0.10f);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

Vec3 Scene1::screenCoords(Vec3 gameCoords)
{
	return projectionMatrix * gameCoords;
}

Vec3 Scene1::worldCoords(Vec3 physicsCoords)
{
	return inverseProjection * physicsCoords;
}

// Creates a surface (cpu) and converts it to a texture (gpu)
// Surface is better for rendering single objects like the player
// However the gpu is most of the time always better in all cases
// mostly because its faster and can handle more (use for tiling and chunks)
SDL_Texture* Scene1::loadImage(const char* textureFile)
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

//
SDL_Rect Scene1::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale)
{
	// Get size of the input texture in pixels
	SDL_Point size{};
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void Scene1::OnDestroy() {

}

Scene1::~Scene1() {
}