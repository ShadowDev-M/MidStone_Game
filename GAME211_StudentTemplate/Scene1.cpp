#include "Scene1.h"
#include <VMath.h>
#include "Chunk.h"
#include "ChunkHandler.h"
#include "ImageToArrayTool.h"

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

	SDL_Surface* debugChunk;

	playerImage = IMG_Load("pacman.png");

	debugChunk = IMG_Load("debugChunk.png");
	readPixelsInGrayscale(debugChunk);
	playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
	
	// Keeping this in for now to fix merge conflict
	game->getPlayer()->setImage(playerImage);
	game->getPlayer()->setTexture(playerTexture);

	ChunkHandler RegionOne;

	std::vector<TileInfo> changesIndex = {
		{0, 0, 1}, {1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {4, 0, 0}, {5, 0, 0}, {6, 0, 0}, {7, 0, 0}, {8, 0, 0}, {9, 0, 0}, {10, 0, 0}, {11, 0, 0}, {12, 0, 0}, {13, 0, 0}, {14, 0, 0}, {15, 0, 0},
		{0, 1, 0}, {1, 1, 0}, {2, 1, 0}, {3, 1, 0}, {4, 1, 0}, {5, 1, 0}, {6, 1, 0}, {7, 1, 0}, {8, 1, 0}, {9, 1, 0}, {10, 1, 0}, {11, 1, 0}, {12, 1, 0}, {13, 1, 0}, {14, 1, 0}, {15, 1, 0},
		{0, 2, 0}, {1, 2, 1}, {2, 2, 0}, {3, 2, 0}, {4, 2, 0}, {5, 2, 0}, {6, 2, 0}, {7, 2, 0}, {8, 2, 0}, {9, 2, 0}, {10, 2, 0}, {11, 2, 0}, {12, 2, 0}, {13, 2, 0}, {14, 2, 0}, {15, 2, 0},
		{0, 3, 0}, {1, 3, 0}, {2, 3, 0}, {3, 3, 0}, {4, 3, 0}, {5, 3, 0}, {6, 3, 0}, {7, 3, 0}, {8, 3, 0}, {9, 3, 1}, {10, 3, 0}, {11, 3, 0}, {12, 3, 0}, {13, 3, 0}, {14, 3, 0}, {15, 3, 0},
		{0, 4, 0}, {1, 4, 0}, {2, 4, 0}, {3, 4, 0}, {4, 4, 0}, {5, 4, 0}, {6, 4, 0}, {7, 4, 0}, {8, 4, 0}, {9, 4, 0}, {10, 4, 0}, {11, 4, 0}, {12, 4, 0}, {13, 4, 0}, {14, 4, 0}, {15, 4, 0},
		{0, 5, 0}, {1, 5, 0}, {2, 5, 0}, {3, 5, 0}, {4, 5, 0}, {5, 5, 0}, {6, 5, 0}, {7, 5, 0}, {8, 5, 0}, {9, 5, 0}, {10, 5, 0}, {11, 5, 0}, {12, 5, 0}, {13, 5, 0}, {14, 5, 0}, {15, 5, 0},
		{0, 6, 0}, {1, 6, 0}, {2, 6, 0}, {3, 6, 0}, {4, 6, 0}, {5, 6, 0}, {6, 6, 1}, {7, 6, 0}, {8, 6, 0}, {9, 6, 0}, {10, 6, 0}, {11, 6, 0}, {12, 6, 0}, {13, 6, 0}, {14, 6, 0}, {15, 6, 0},
		{0, 7, 0}, {1, 7, 0}, {2, 7, 0}, {3, 7, 0}, {4, 7, 0}, {5, 7, 0}, {6, 7, 0}, {7, 7, 0}, {8, 7, 0}, {9, 7, 0}, {10, 7, 0}, {11, 7, 0}, {12, 7, 0}, {13, 7, 0}, {14, 7, 0}, {15, 7, 0},
		{0, 8, 0}, {1, 8, 0}, {2, 8, 0}, {3, 8, 0}, {4, 8, 0}, {5, 8, 0}, {6, 8, 0}, {7, 8, 0}, {8, 8, 0}, {9, 8, 0}, {10, 8, 0}, {11, 8, 0}, {12, 8, 0}, {13, 8, 0}, {14, 8, 0}, {15, 8, 0},
		{0, 9, 0}, {1, 9, 0}, {2, 9, 0}, {3, 9, 0}, {4, 9, 0}, {5, 9, 0}, {6, 9, 0}, {7, 9, 0}, {8, 9, 0}, {9, 9, 0}, {10, 9, 0}, {11, 9, 0}, {12, 9, 0}, {13, 9, 0}, {14, 9, 0}, {15, 9, 0},
		{0, 10, 0}, {1, 10, 0}, {2, 10, 0}, {3, 10, 0}, {4, 10, 0}, {5, 10, 0}, {6, 10, 0}, {7, 10, 0}, {8, 10, 0}, {9, 10, 0}, {10, 10, 0}, {11, 10, 0}, {12, 10, 0}, {13, 10, 0}, {14, 10, 0}, {15, 10, 0},
		{0, 11, 0}, {1, 11, 0}, {2, 11, 0}, {3, 11, 0}, {4, 11, 0}, {5, 11, 0}, {6, 11, 0}, {7, 11, 0}, {8, 11, 0}, {9, 11, 0}, {10, 11, 0}, {11, 11, 0}, {12, 11, 0}, {13, 11, 0}, {14, 11, 0}, {15, 11, 0},
		{0, 12, 0}, {1, 12, 0}, {2, 12, 0}, {3, 12, 0}, {4, 12, 0}, {5, 12, 0}, {6, 12, 0}, {7, 12, 0}, {8, 12, 0}, {9, 12, 0}, {10, 12, 0}, {11, 12, 0}, {12, 12, 0}, {13, 12, 0}, {14, 12, 0}, {15, 12, 0},
		{0, 13, 0}, {1, 13, 0}, {2, 13, 0}, {3, 13, 0}, {4, 13, 0}, {5, 13, 0}, {6, 13, 0}, {7, 13, 0}, {8, 13, 0}, {9, 13, 0}, {10, 13, 0}, {11, 13, 0}, {12, 13, 0}, {13, 13, 0}, {14, 13, 0}, {15, 13, 0},
		{0, 14, 0}, {1, 14, 0}, {2, 14, 0}, {3, 14, 0}, {4, 14, 0}, {5, 14, 0}, {6, 14, 0}, {7, 14, 0}, {8, 14, 0}, {9, 14, 0}, {10, 14, 0}, {11, 14, 0}, {12, 14, 0}, {13, 14, 0}, {14, 14, 0}, {15, 14, 0},
		{0, 15, 0}, {1, 15, 0}, {2, 15, 0}, {3, 15, 0}, {4, 15, 0}, {5, 15, 0}, {6, 15, 0}, {7, 15, 0}, {8, 15, 0}, {9, 15, 0}, {10, 15, 0}, {11, 15, 0}, {12, 15, 0}, {13, 15, 0}, {14, 15, 0}, {15, 15, 0} };



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