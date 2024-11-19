#include "SceneYB.h"
#include <VMath.h>
#include "Chunk.h"
#include "ChunkHandler.h"

// See notes about this constructor in Scene1.h.
SceneYB::SceneYB(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// player spawns in middle of screen
	player = new Player(Vec3(xAxis / 2.0f, yAxis / 2.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	player->setRenderer(renderer);

	enemy = new Enemy(Vec3(xAxis / 3.0f, yAxis / 3.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	enemy->setRenderer(renderer);
}

// To render chunks and set id to tiles need to setup camera first
// Once camera is set, use it to only render tiles inside the camera (good for optimizaion)

// Once that is done, setup attaching tile ids to specific images to load in. 

bool SceneYB::OnCreate() {
	// Check to make sure loading scene works
	std::cout << "Entering SceneYB" << std::endl;

	Item* sword = new Item("Sword");
	Item* shield = new Item("Shield");
	Inventory inventory;
	inventory.addItem(sword);
	inventory.printInventory();

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	inverseProjection = MMath::inverse(projectionMatrix);

	player->setProjection(projectionMatrix);
	enemy->setProjection(projectionMatrix);

	player->setInverse(inverseProjection);
	enemy->setInverse(inverseProjection);

	//for (int i = 0; i < enemyQueue.size(); i++) 
	//{
	//	&enemyQueue[i]->setProjection(projectionMatrix);
	//}

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	enemyManager = new EnemyManager(this);
	enemyManager->spawnEnemy(4);

	player->OnCreate();
	enemy->OnCreate();

	player->setWidth(player->width * (xAxis / w) * player->scale);
	player->setHeight(player->height * (yAxis / h) * player->scale);

	enemy->setWidth(enemy->width * (xAxis / w) * enemy->scale);
	enemy->setHeight(enemy->height * (yAxis / h) * enemy->scale);

	//for (int i = 0; i < enemyList.size(); i++)
	//{
	//	enemyList[i]->OnCreate();
	//}

	// Chunk rendering and testing in ChunkTestScene
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

void SceneYB::Update(const float deltaTime) {

	// Update player
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

	inverseProjection = MMath::inverse(projectionMatrix);

	// Update players projection matrix
	player->setProjection(projectionMatrix);

	player->setInverse(inverseProjection);

	player->Update(deltaTime);

	if (player->enemyCollision(enemy))
	{
		std::cout << "COLLISION DETECTED" << std::endl;
	}

	enemy->Update(deltaTime);
}

void SceneYB::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderClear(renderer);

	// render the player
	player->Render(player->scale);
	//enemy->Render(enemy->scale);

	//PLAYER COLLISION BOX DEBUG
	Vec3 playerPos = screenCoords(player->getPos());
	Vec3 playerHitboxOffset = player->hitboxOffset;

	SDL_Rect playerRect = { playerPos.x + playerHitboxOffset.x / 2.0f, playerPos.y + playerHitboxOffset.y / 2.0f, player->widthScreen - playerHitboxOffset.x, player->heightScreen - playerHitboxOffset.y }; //Width and height are already multiplied by scale in on create
	//SDL_Rect playerRect = { player->widthScreen - playerHitboxOffset.x, player->heightScreen - playerHitboxOffset.y, playerPos.x + playerHitboxOffset.x, playerPos.y + playerHitboxOffset.y };

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &playerRect);

	//ENEMY COLLISION BOX DEBUG
	Vec3 enemyPos = screenCoords(enemy->getPos());
	Vec3 enemyHitboxOffset = screenCoords(enemy->hitboxOffset);

	SDL_Rect enemyRect = { enemyPos.x + enemyHitboxOffset.x, enemyPos.y + enemyHitboxOffset.y, enemy->widthScreen - enemyHitboxOffset.x, enemy->heightScreen - enemyHitboxOffset.y }; //Width and height are already multiplied by scale in on create
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &enemyRect);

	SDL_RenderPresent(renderer);
}

void SceneYB::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	player->HandleEvents(event);
}

Vec3 SceneYB::screenCoords(Vec3 gameCoords)
{
	return projectionMatrix * gameCoords;
}

Vec3 SceneYB::worldCoords(Vec3 physicsCoords)
{
	return inverseProjection * physicsCoords;
}

// Creates a surface (cpu) and converts it to a texture (gpu)
// Surface is better for rendering single objects like the player
// However the gpu is most of the time always better in all cases
// mostly because its faster and can handle more (use for tiling and chunks)
SDL_Texture* SceneYB::loadImage(const char* textureFile)
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
SDL_Rect SceneYB::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale)
{
	// Get size of the input texture in pixels
	SDL_Point size{};
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void SceneYB::OnDestroy() {
	//player->OnDestroy();
}

SceneYB::~SceneYB() {
}