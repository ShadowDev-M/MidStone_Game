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
	testh = true;
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
		{0, 0, 1}, {1, 2, 1}, {2,3,1}, {18,20,1} };

	
		
	player->OnCreate();
	RegionOne.addLoadingEntity(player);


	std::cout << changesIndex.at(0).id;

	stoneTileTexture = loadImage(stoneTile->GetTextureFile());

	grassTileTexture = loadImage(grassTile->GetTextureFile());
	
	return true;
}

void SceneC::Update(const float deltaTime) {
	// Will make this its own extracted function after (will put in camera class too)
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	float left, right, bottom, top;

	left = 0.0f;
	right = xAxis;
	bottom = 0.0f;
	top = yAxis;

	left = player->getPos().x - xAxis / 2.0f;
	right = player->getPos().x + xAxis / 2.0f;
	bottom = player->getPos().y - yAxis / 2.0f;
	top = player->getPos().y + yAxis / 2.0f;


	Matrix4 ortho = MMath::orthographic(left, right, bottom, top, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// Update players projection matrix
	player->setProjection(projectionMatrix);

	player->Update(deltaTime);
	RegionOne.Update();
	
	if (testh) {
		RegionOne.setTile(changesIndex);
			testh = false;
	};


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

	Vec2 playerChunkPos = RegionOne.getChunkLocation(Vec2(player->getPos().x, player->getPos().y));
	//for (int i = 0; i < 16*16; i++) {
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Vec2 chunkRenderPos = Vec2((playerChunkPos.x-1)+i, (playerChunkPos.y-1)+j);

			for (int x = 0; x < 16; x++) {
				for (int y = 0; y < 16; y++) {
					int id = RegionOne.getChunkTileID(chunkRenderPos, Vec2(x, y));

					Vec3 chunkInfo = Vec3(x + 16 * chunkRenderPos.x, y + 16 * chunkRenderPos.y, id);
					if (chunkInfo.z == 0) {

						grassTile->setPos(Vec3(chunkInfo.x, chunkInfo.y, 0.0f));

						Vec3 grassTileCoords = screenCoords(grassTile->getPos());

						SDL_Rect grassDest = scale(grassTileTexture, grassTileCoords.x, grassTileCoords.y, 2.0f);
						SDL_RenderCopy(renderer, grassTileTexture, nullptr, &grassDest);

					}
					if (chunkInfo.z == 1) {
						stoneTile->setPos(Vec3(chunkInfo.x, chunkInfo.y, 0.0f));

						Vec3 stoneTileCoords = screenCoords(stoneTile->getPos());

						SDL_Rect stoneDest = scale(stoneTileTexture, stoneTileCoords.x, stoneTileCoords.y, 2.0f);
						SDL_RenderCopy(renderer, stoneTileTexture, nullptr, &stoneDest);
					}
				}
			}
		}
	}
	//}
			
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