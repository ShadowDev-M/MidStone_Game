#include "ChunkTestScene.h"
#include <VMath.h>



// See notes about this constructor in Scene1.h.
SceneC::SceneC(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 16.0f;
	yAxis = 16.0f;


	game->getPlayer()->setPos(Vec3(8.0f, 8.0f, 0.0f));
	
	stoneTile = new Body(Vec3(4.0f, 4.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	stoneTile->SetTextureFile("textures/StoneTile.png");

	stoneTileTexture = nullptr;

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

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	


	// Creating Chunks and Rendering them should be their own methods
	ChunkHandler RegionOne;

	std::vector<TileInfo> changesIndex = {
		{0,0,1}, {0,1,1}, {0,2,1}, {0,3,1}, {0,4,1}, {0,5,1}, {0,6,1}, {0,7,1}, {0,8,1}, {0,9,1}, {0,10,1}, {0,11,1}, {0,12,1}, {0,13,1}, {0,14,1}, {0,15,1},
		{1,0,1}, {1,1,1}, {1,2,1}, {1,3,1}, {1,4,1}, {1,5,1}, {1,6,1}, {1,7,1}, {1,8,1}, {1,9,1}, {1,10,1}, {1,11,1}, {1,12,1}, {1,13,1}, {1,14,1}, {1,15,1},
		{2,0,1}, {2,1,1}, {2,2,1}, {2,3,1}, {2,4,1}, {2,5,1}, {2,6,1}, {2,7,1}, {2,8,1}, {2,9,1}, {2,10,1}, {2,11,1}, {2,12,1}, {2,13,1}, {2,14,1}, {2,15,1} };

	

	RegionOne.setTile(changesIndex);


	for (int i = 0; i < changesIndex.size(); i++) 
	{
		tiles.push_back(stoneTile);
	}
	
	

	//TileFaces intersectedTile = RegionOne.getFaces(Vec2(4.5, 6.5), Vec2(-4.0, 2.0));

	// Print the intersected tiles
	//std::cout << " (" << intersectedTile.PointOne.x << ", " << intersectedTile.PointOne.y << ") (" << intersectedTile.PointTwo.x << ", " << intersectedTile.PointTwo.y << ")\n";


	//RegionOne.getFaces(Vec2(0.5, 0.7), Vec2(20.3, 30.4));

	stoneTileTexture = loadImage(stoneTile->GetTextureFile());
	
	return true;
}

void SceneC::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);

	std::cout << tiles.size() << std::endl;;
}

void SceneC::Render() {
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	
	// Clear the screen
	SDL_RenderClear(renderer);

	// unified measurement system
	// Render Chunks
	// Camera


	Vec3 stoneTileCoords = screenCoords(stoneTile->getPos());
	SDL_Rect dest = scale(stoneTileTexture, stoneTileCoords.x, stoneTileCoords.y, 3.0f);

	for (int i = 0; i < tiles.size(); i++) {
		stoneTileCoords.x + tileOffset;
		stoneTileCoords.y + tileOffset;
	}

	for (Body* stoneTile : tiles) {
		SDL_RenderCopy(renderer, stoneTileTexture, nullptr, &dest);
	}

	// Render certain temporary blocks ontop on the chunks to test collision
	//

	game->RenderPlayer(0.10f);
	

	// update screen
	SDL_RenderPresent(renderer);
}

void SceneC::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);

	switch (event.type) {
	case SDL_MOUSEMOTION:
		
		break;
	case SDL_MOUSEBUTTONDOWN:
		
		break;
	case SDL_MOUSEBUTTONUP:
		
		break;

	}
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
	
}


SceneC::~SceneC() {
	std::cout << "deleting child class: SceneC." << std::endl;
	// delete
	
}