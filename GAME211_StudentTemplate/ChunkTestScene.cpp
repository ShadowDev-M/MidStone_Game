#include "ChunkTestScene.h"
#include <VMath.h>
#include "createItem.h"
#include "UiPanel.h"




Item* currentItem = playerInventory.getItem(0, 3);
int currentItemRow = 0;
int currentItemColumn = 3;


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

	playerInventory.addItem(sword);
	playerInventory.addItem(armor);
	playerInventory.addItem(shield);
	playerInventory.addItem(potion);
	playerInventory.addItem(shoes);
	playerInventory.printInventory();

	healthBar = new HealthBar(10.0f, 200.0f, { 0, 255, 150, 255 });

	panel.OnCreate(renderer, Vec2(w / 30, h / 2 + 160), "textures/stoneTile.png", 7);
	if (currentItem != nullptr)
		panel.AddIcon(currentItem->filePath, 7.0f);
	else
		panel.AddIcon("textures/emptySlot.png", 7.0f);

	for (int i = 0; i < 5; i++)
	{
		if (playerInventory.getItem(0, i) != nullptr)
		{
			// display
			space[i].OnCreate(renderer, Vec2(w / 2.6f + 50 * i + 5 * i, h * 0.9), "textures/itemFrame.png", 0.5);
			space[i].AddIcon(playerInventory.getItem(0, i)->filePath, 0.5);
		}
		else
		{
			// display
			space[i].OnCreate(renderer, Vec2(w / 2.6f + 50 * i + 5 * i, h * 0.9), "textures/itemFrame.png", 0.5);
			space[i].AddIcon("textures/emptySlot.png", 0.5);
		}
	}
	
	return true;
}

void SceneC::refreshIcon() {
	// Clear the current icon
	panel.ClearIcons();

	// Add the new icon based on the current item
	if (currentItem != nullptr) {
		// Add the current item's icon
		panel.AddIcon(currentItem->filePath, 7.0f);
	}
	else {
		// If no item, show an empty slot, which is just a plus icon
		panel.AddIcon("textures/emptySlot.png", 7.0f);
	}

	for (int i = 0; i < 5; i++) {
		space[i].ClearIcons();
		if (playerInventory.getItem(0, i) != nullptr) {
			// Add the current item's icon
			space[i].AddIcon(playerInventory.getItem(0, i)->filePath, 0.5f);
		}
		else {
			// If no item, show an empty slot, which is just a plus icon
			space[i].AddIcon("textures/emptySlot.png", 0.5f);
		}
	}
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
	float currentHP = player->getPlayerHP();
	healthBar->UpdateHealth(currentHP);

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
	
	healthBar->Render(renderer, Vec2(770, 550), 20); // Position, height 20px
	
	panel.Render();

	for (int i = 0; i < 5; i++)
	{
		space[i].Render();
	}

	// update screen
	SDL_RenderPresent(renderer);
}

void SceneC::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	player->HandleEvents(event);

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		// Press number to change your current item
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_1:
			currentItem = playerInventory.getItem(0, 0);
			currentItemColumn = 0;
			break;
		case SDL_SCANCODE_2:
			currentItem = playerInventory.getItem(0, 1);
			currentItemColumn = 1;
			break;
		case SDL_SCANCODE_3:
			currentItem = playerInventory.getItem(0, 2);
			currentItemColumn = 2;
			break;
		case SDL_SCANCODE_4:
			currentItem = playerInventory.getItem(0, 3);
			currentItemColumn = 3;
			break;
		case SDL_SCANCODE_5:
			currentItem = playerInventory.getItem(0, 4);
			currentItemColumn = 4;
			break;
		case SDL_SCANCODE_Z:
			playerInventory.removeItem(currentItemRow, currentItemColumn);
			currentItem = playerInventory.getItem(0, currentItemColumn);
			break;
		case SDL_SCANCODE_E:
			if (currentItem != nullptr && currentItem->itemName == "potion") {
				player->addPlayerHP(-2);
				player->getPlayerHP();
				std::cout << "potion used" << std::endl;
				std::cout << player->getPlayerHP() << std::endl;
				break;
			}
		}
		// Refresh the icon after item change
		refreshIcon();

		// more of a debug/feedback feature. 
/*		if (currentItem) {
			std::cout << "Selected item: " << currentItem->itemName << std::endl;
		}
		else {
			std::cout << "Selected slot is empty." << std::endl;
		}*/

	
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
	delete stoneTileTexture;
	delete grassTileTexture;
	//player->OnDestroy();

	delete healthBar;
	healthBar = nullptr;

	for (int i = 0; i < 5; i++) {
		space[i].OnDestroy();
	}
	panel.OnDestroy();
}


SceneC::~SceneC() {
	std::cout << "deleting child class: SceneC." << std::endl;
	// delete
	
}