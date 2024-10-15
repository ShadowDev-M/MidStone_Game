#include "ChunkTestScene.h"
#include <VMath.h>



// See notes about this constructor in Scene1.h.
SceneC::SceneC(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;

	
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 16.0f;
	yAxis = 16.0f;
	
	player = new Player(Vec3(8.0f, 8.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	player->setRenderer(renderer);

	stoneTile = new Body(Vec3(1.0f, 1.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	stoneTile->SetTextureFile("textures/StoneTile.png");

	grassTile = new Body(Vec3(1.0f, 1.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	grassTile->SetTextureFile("textures/GrassTile.png");

	stoneTileTexture = nullptr;
	grassTileTexture = nullptr;

}

// transfer data to heap
bool SceneC::OnCreate() {
	// Check to make sure loading new scene works
	std::cout << "Entering ChunkTest" << std::endl;

	int w, h;
	SDL_GetWindowSize(window, &w, &h);


	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	player->setProjection(projectionMatrix);

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	

	// Creating Chunks and Rendering them should be their own methods
	

	changesIndex = {
		{0, 0, 1}, {1, 0, 0}, {2, 0, 1}, {3, 0, 1}, {4, 0, 1}, {5, 0, 0}, {6, 0, 1}, {7, 0, 1}, {8, 0, 0}, {9, 0, 0}, {10, 0, 0}, {11, 0, 0}, {12, 0, 0}, {13, 0, 0}, {14, 0, 0}, {15, 0, 1},
		{0, 1, 1}, {1, 1, 0}, {2, 1, 1}, {3, 1, 1}, {4, 1, 1}, {5, 1, 0}, {6, 1, 1}, {7, 1, 1}, {8, 1, 0}, {9, 1, 0}, {10, 1, 0}, {11, 1, 0}, {12, 1, 0}, {13, 1, 0}, {14, 1, 0}, {15, 1, 0},
		{0, 2, 1}, {1, 2, 0}, {2, 2, 1}, {3, 2, 1}, {4, 2, 1}, {5, 2, 0}, {6, 2, 1}, {7, 2, 1}, {8, 2, 0}, {9, 2, 0}, {10, 2, 0}, {11, 2, 0}, {12, 2, 0}, {13, 2, 0}, {14, 2, 0}, {15, 2, 0},
		{0, 3, 1}, {1, 3, 0}, {2, 3, 1}, {3, 3, 1}, {4, 3, 1}, {5, 3, 0}, {6, 3, 1}, {7, 3, 1}, {8, 3, 0}, {9, 3, 0}, {10, 3, 0}, {11, 3, 0}, {12, 3, 0}, {13, 3, 0}, {14, 3, 0}, {15, 3, 0},
		{0, 4, 1}, {1, 4, 0}, {2, 4, 1}, {3, 4, 1}, {4, 4, 1}, {5, 4, 0}, {6, 4, 1}, {7, 4, 1}, {8, 4, 0}, {9, 4, 0}, {10, 4, 0}, {11, 4, 0}, {12, 4, 0}, {13, 4, 0}, {14, 4, 0}, {15, 4, 0},
		{0, 5, 0}, {1, 5, 0}, {2, 5, 0}, {3, 5, 0}, {4, 5, 0}, {5, 5, 0}, {6, 5, 0}, {7, 5, 0}, {8, 5, 0}, {9, 5, 0}, {10, 5, 0}, {11, 5, 0}, {12, 5, 0}, {13, 5, 0}, {14, 5, 0}, {15, 5, 0},
		{0, 6, 0}, {1, 6, 0}, {2, 6, 0}, {3, 6, 0}, {4, 6, 0}, {5, 6, 0}, {6, 6, 0}, {7, 6, 0}, {8, 6, 0}, {9, 6, 0}, {10, 6, 0}, {11, 6, 0}, {12, 6, 0}, {13, 6, 0}, {14, 6, 0}, {15, 6, 0},
		{0, 7, 0}, {1, 7, 0}, {2, 7, 0}, {3, 7, 0}, {4, 7, 0}, {5, 7, 0}, {6, 7, 0}, {7, 7, 0}, {8, 7, 0}, {9, 7, 0}, {10, 7, 0}, {11, 7, 0}, {12, 7, 0}, {13, 7, 0}, {14, 7, 0}, {15, 7, 0},
		{0, 8, 0}, {1, 8, 0}, {2, 8, 0}, {3, 8, 0}, {4, 8, 0}, {5, 8, 0}, {6, 8, 0}, {7, 8, 0}, {8, 8, 0}, {9, 8, 0}, {10, 8, 0}, {11, 8, 0}, {12, 8, 0}, {13, 8, 0}, {14, 8, 0}, {15, 8, 0},
		{0, 9, 0}, {1, 9, 0}, {2, 9, 0}, {3, 9, 0}, {4, 9, 0}, {5, 9, 0}, {6, 9, 0}, {7, 9, 0}, {8, 9, 0}, {9, 9, 0}, {10, 9, 0}, {11, 9, 0}, {12, 9, 0}, {13, 9, 0}, {14, 9, 0}, {15, 9, 0},
		{0, 10, 0}, {1, 10, 0}, {2, 10, 0}, {3, 10, 0}, {4, 10, 0}, {5, 10, 0}, {6, 10, 0}, {7, 10, 0}, {8, 10, 0}, {9, 10, 0}, {10, 10, 0}, {11, 10, 0}, {12, 10, 0}, {13, 10, 0}, {14, 10, 0}, {15, 10, 0},
		{0, 11, 0}, {1, 11, 0}, {2, 11, 0}, {3, 11, 0}, {4, 11, 0}, {5, 11, 0}, {6, 11, 0}, {7, 11, 0}, {8, 11, 0}, {9, 11, 0}, {10, 11, 0}, {11, 11, 0}, {12, 11, 0}, {13, 11, 0}, {14, 11, 0}, {15, 11, 1},
		{0, 12, 0}, {1, 12, 0}, {2, 12, 0}, {3, 12, 0}, {4, 12, 0}, {5, 12, 0}, {6, 12, 0}, {7, 12, 0}, {8, 12, 0}, {9, 12, 0}, {10, 12, 0}, {11, 12, 0}, {12, 12, 0}, {13, 12, 0}, {14, 12, 1}, {15, 12, 1},
		{0, 13, 0}, {1, 13, 0}, {2, 13, 0}, {3, 13, 0}, {4, 13, 0}, {5, 13, 0}, {6, 13, 0}, {7, 13, 0}, {8, 13, 0}, {9, 13, 0}, {10, 13, 0}, {11, 13, 0}, {12, 13, 1}, {13, 13, 0}, {14, 13, 1}, {15, 13, 1},
		{0, 14, 0}, {1, 14, 0}, {2, 14, 0}, {3, 14, 0}, {4, 14, 0}, {5, 14, 0}, {6, 14, 0}, {7, 14, 0}, {8, 14, 0}, {9, 14, 0}, {10, 14, 0}, {11, 14, 0}, {12, 14, 1}, {13, 14, 0}, {14, 14, 1}, {15, 14, 1},
		{0, 15, 0}, {1, 15, 0}, {2, 15, 0}, {3, 15, 0}, {4, 15, 0}, {5, 15, 0}, {6, 15, 0}, {7, 15, 0}, {8, 15, 0}, {9, 15, 0}, {10, 15, 0}, {11, 15, 0}, {12, 15, 1}, {13, 15, 0}, {14, 15, 1}, {15, 15, 1}, };

	
	RegionOne.setTile(changesIndex);

	player->OnCreate();

	std::cout << changesIndex.at(0).id;

	stoneTileTexture = loadImage(stoneTile->GetTextureFile());

	grassTileTexture = loadImage(grassTile->GetTextureFile());
	
	return true;
}

void SceneC::Update(const float deltaTime) {
	player->Update(deltaTime);

	// Will make this its own extracted function after (will put in camera class too)
	int w, h;

	SDL_GetWindowSize(window, &w, &h);
	
	 multW = (float)1000/w;
	 multH = (float)1000/h;
	//std::cout << multH, " ";

	
	//std::cout << multH, " ";



	//h *= multH;
	 xAxis = 16;
	 yAxis = 16;

	Matrix4 ndc = MMath::viewportNDC(w * multW, h *multH) ;
	float left, right, bottom, top;

	left = 0.0f;
	right = xAxis;
	bottom = 0.0f;
	top = yAxis;

	left = player->getPos().x - xAxis / 2.0f;
	right = player->getPos().x + xAxis / 2.0f;
	bottom = (player->getPos().y - yAxis / 4) - yAxis / 2.0f;
	top = (player->getPos().y - yAxis / 4) + yAxis / 2.0f;


	Matrix4 ortho = MMath::orthographic(left, right, bottom, top, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// Update players projection matrix
	player->setProjection(projectionMatrix);

}

void SceneC::Render() {
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	
	// Clear the screen
	SDL_RenderClear(renderer);

	// unified measurement system
	// Render Chunks
	// Camera

	// NOT FINAL, just temp rendering for chunks just to get something on screen that can also be changed and used with physics and collision
	// Will get fixed up afterwards
	for (int i = 0; i < changesIndex.size(); i++) {
		Vec3 chunkInfo = Vec3(changesIndex.at(i).x, changesIndex.at(i).y, changesIndex.at(i).id);
		if (chunkInfo.z == 0) {

			grassTile->setPos(Vec3(chunkInfo.x, chunkInfo.y, 0.0f));

			Vec3 grassTileCoords = screenCoords(grassTile->getPos());

			SDL_Rect grassDest = scale(grassTileTexture, grassTileCoords.x, grassTileCoords.y, 4.0f);
			SDL_RenderCopy(renderer, grassTileTexture, nullptr, &grassDest);

		}
		if (chunkInfo.z == 1) {
			stoneTile->setPos(Vec3(chunkInfo.x, chunkInfo.y, 0.0f));

			Vec3 stoneTileCoords = screenCoords(stoneTile->getPos());

			SDL_Rect stoneDest = scale(stoneTileTexture, stoneTileCoords.x, stoneTileCoords.y, 4.0f);
			SDL_RenderCopy(renderer, stoneTileTexture, nullptr, &stoneDest);
		}

	}
			
	player->Render(0.1f);
	

	// update screen
	SDL_RenderPresent(renderer);
}

void SceneC::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	player->HandleEvents(event);
}

Vec3 SceneC::screenCoords(Vec3 gameCoords)
{	
	return projectionMatrix * gameCoords;
}

Vec3 SceneC::worldCoords(Vec3 physicsCoords)
{
	return inverseProjection * physicsCoords;
}


// Creates a surface (cpu) and converts it to a texture (gpu)
// Surface is better for rendering single objects like the player
// However the gpu is most of the time always better in all cases
// mostly because its faster and can handle more (use for tiling and chunks)
SDL_Texture* SceneC::loadImage(const char* textureFile)
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
SDL_Rect SceneC::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale)
{
	// Get size of the input texture in pixels
	SDL_Point size{};
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void SceneC::OnDestroy() {
	// Free loaded images
	delete stoneTileTexture;
	delete grassTileTexture;
	//player->OnDestroy();
}


SceneC::~SceneC() {
	std::cout << "deleting child class: SceneC." << std::endl;
	// delete
	
}