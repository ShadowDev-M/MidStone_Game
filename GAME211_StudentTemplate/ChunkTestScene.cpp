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
	
	// 28
	xAxis = camera.getXAxis();
	// 16
	// yAxis = static_cast<int>(LEVEL_HEIGHT) + 1
	
	// 15.75
	yAxis = camera.getYAxis();


	player = new Player(Vec3(1, 1, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	player->setRenderer(renderer);
	player->SetTextureFile("textures/PlayerFacingFrontIdle.png");
	player->setWidth(1.0f);
	player->setHeight(1.0f);
	player->SetRegion(&RegionOne);
	//RegionOne.setPlayer(player);


	stoneTile = new Body(Vec3(0, 0, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	stoneTile->SetTextureFile("textures/StoneTile.png");
	stoneTile->setWidth(1.0f);
	stoneTile->setHeight(1.0f);


	grassTile = new Body(Vec3(0, 0, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	grassTile->SetTextureFile("textures/GrassTile.png");
	grassTile->setWidth(1.0f);
	grassTile->setHeight(1.0f);

	enemyManager = new EnemyManager();
	enemyManager->setRenderer(renderer);
	enemyList = enemyManager->spawnEnemy(10, player);

	//enemy = new Enemy(Vec3(4, 4, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0, player);
	//enemy->setRenderer(renderer);
	//enemy->setWidth(1.0f);
	//enemy->setHeight(1.0f);

	//enemy1 = new Enemy(Vec3(6, 6, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0, player);
	//enemy1->setRenderer(renderer);
	//enemy1->setWidth(1.0f);
	//enemy1->setHeight(1.0f);

	

	stoneTileTexture = nullptr;
	grassTileTexture = nullptr;
	
	

}

// transfer data to heap
bool SceneC::OnCreate() {
	// Check to make sure loading new scene works
	std::cout << "Entering ChunkTest" << std::endl;
	testh = true;



	camera.OnCreate();	
	projectionMatrix = camera.getProjectionMatrix();
	
	
	
	player->OnCreate();
	
	player->setScale(camera.scalingFactor(player->getTexture(), player));

	player->setupCollision();

	//enemy->OnCreate();

	//enemy->setProjection(projectionMatrix);

	//enemy1->OnCreate();

	//enemy1->setProjection(projectionMatrix);
	//enemy->setInverse(inverseProjection);
	

	// Creating Chunks and Rendering them should be their own methods
	
	RegionOne.OnCreate();
	changesIndex = {
		{0, 0, 1}

	};


	//player->hitbox.setObstacles(faces);
	

	RegionOne.addLoadingEntity(player);


	//std::cout << changesIndex.at(0).id;

	stoneTileTexture = camera.refinedLoadImage(stoneTile, renderer);

	grassTileTexture = camera.refinedLoadImage(grassTile, renderer);

	

	playerInventory.addItem(sword);
	playerInventory.addItem(armor);
	playerInventory.addItem(shield);
	playerInventory.addItem(potion);
	playerInventory.addItem(shoes);
	playerInventory.printInventory();

	healthBar = new HealthBar(10.0f, 200.0f, { 0, 255, 150, 255 });

	panel.OnCreate(renderer, Vec2(camera.getWindowWidth() / 30, camera.getWindowHeight() / 2 + 160), "textures/stoneTile.png", 7);
	if (currentItem != nullptr)
		panel.AddIcon(currentItem->filePath, 7.0f);
	else
		panel.AddIcon("textures/emptySlot.png", 7.0f);

	for (int i = 0; i < 5; i++)
	{
		if (playerInventory.getItem(0, i) != nullptr)
		{
			// display
			space[i].OnCreate(renderer, Vec2(camera.getWindowWidth() / 2.6f + 50 * i + 5 * i, camera.getWindowHeight() * 0.9), "textures/itemFrame.png", 0.5);
			space[i].AddIcon(playerInventory.getItem(0, i)->filePath, 0.5);
		}
		else
		{
			// display
			space[i].OnCreate(renderer, Vec2(camera.getWindowWidth() / 2.6f + 50 * i + 5 * i, camera.getWindowHeight() * 0.9), "textures/itemFrame.png", 0.5);
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


bool SceneC::mouseInsideEnemy(Vec3 mouseCoords, Body* body)
{
	if ((mouseCoords.x >= body->getPos().x - body->width) &&
		(mouseCoords.x <= body->getPos().x + body->width) &&
		(mouseCoords.y >= body->getPos().y - body->height) &&
		(mouseCoords.y <= body->getPos().y + body->height)) {
		return true;
	}
	return false;
} 

void SceneC::Update(const float deltaTime) {
	//// Will make this its own extracted function after (will put in camera class too)

	camera.cameraFollowsPlayer(player, window);
	projectionMatrix = camera.getProjectionMatrix();

	player->Update(deltaTime);
	RegionOne.Update();

	enemyManager->Update(deltaTime);


	//enemy->Update(deltaTime);

	//enemy1->Update(deltaTime);
	
	if (testh) {
		RegionOne.setTile(changesIndex);
			testh = false;
	};
	float currentHP = player->getPlayerHP();
	healthBar->UpdateHealth(currentHP);

	
	SDL_GetMouseState(&mouseX, &mouseY);
	mousePhysicsCoords = camera.ScreenToWorldCoords(Vec3(mouseX + mouseOffSet, mouseY + mouseOffSet, 0.0f));
	


	//if (mouseInsideEnemy(mousePhysicsCoords, sword) == true) {
	//	std::cout << "ENEMY UNDER CURSOR";
	//}

	

	//std::cout << "Mouse Coords: " << mousePhysicsCoords.x << ", " << mousePhysicsCoords.y << "\n";
	//std::cout << "Sword Pos: " << sword->getPos().x << ", " << sword->getPos().y << "\n";

	//std::cout << player->getPos().x << ", " << player->getPos().y << "\n";
	//std::cout << "TILE LOCATIONS:" << stoneTile->getPos().x << ", " << stoneTile->getPos().y << "\n";
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

						Vec3 grassTileCoords = camera.worldToScreenCoords(grassTile->getPos());

						SDL_Rect grassDest = camera.scale(grassTileTexture, grassTileCoords.x, grassTileCoords.y, camera.scalingFactor(grassTileTexture, grassTile) + 0.1f);
						
						SDL_RenderCopy(renderer, grassTileTexture, nullptr, &grassDest);

					}
					if (chunkInfo.z == 1) {
						stoneTile->setPos(Vec3(chunkInfo.x, chunkInfo.y, 0.0f));

						Vec3 stoneTileCoords = camera.worldToScreenCoords(stoneTile->getPos());

						SDL_Rect stoneDest = camera.scale(stoneTileTexture, stoneTileCoords.x, stoneTileCoords.y, camera.scalingFactor(stoneTileTexture, stoneTile) + 0.1f); //+ 0.1f
						
						SDL_RenderCopy(renderer, stoneTileTexture, nullptr, &stoneDest);
					}
				}
			}
		}
	}
	//}


	// Renders line of Tile Collison
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (TileFaces tile : player->permFaces) {
		Vec3 screenCoords1 = projectionMatrix * Vec3(tile.PointOne.x, tile.PointOne.y, 0.0f);
		Vec3 screenCoords2 = projectionMatrix * Vec3(tile.PointTwo.x, tile.PointTwo.y, 0.0f);;

		SDL_RenderDrawLine(renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	}


	
	/*
	SDL_Rect srcRect = PlayerAnimation(2);*/

	Vec3 worldCoords = camera.worldToScreenCoords(player->getPos());
	SDL_Rect Dest = camera.scale(player->getTexture(), worldCoords.x, worldCoords.y, camera.scalingFactor(player->getTexture(), player));
	
	if (player->invulTimer % 2 == 0 || player->invulTimer <= 0)
		player->renderPlayer(player->scale, 2);

	enemyManager->RenderEnemies(camera);

	//camera.renderEntity(enemy, enemy->getTexture(), renderer);

	//camera.renderEntity(enemy1, enemy1->getTexture(), renderer);


	


	// TileFaces newTile = TileFaces(Vec2(5, 4), Vec2(10, 4), wall);
	/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, newTile.PointOne.x, newTile.PointOne.y, newTile.PointTwo.x, newTile.PointTwo.y);*/

				
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


	AttackEnemy(event);




}

void SceneC::AttackEnemy(const SDL_Event& event)
{
	if (event.type == SDL_MOUSEBUTTONDOWN) { // mouse button down event
		if (event.button.button == SDL_BUTTON_LEFT) { // left click on mouse
			// Using function to check if mouse click is within the bounds of the image "bounds"
			
			for (int i = 0; i < enemyList.size(); i++)
			{
				// Change player sprite when attacking
				if (mouseInsideEnemy(mousePhysicsCoords, enemyList[i]) == true) {
					tempHealth -= tempDamage;
					std::cout << "\n" << "Clicked/Enemy Takes Damage";

					std::cout << "Damage Value: " << tempHealth << std::endl;

					if (tempHealth <= 0) {
						std::cout << "\n" << "Enemy Dies";
						enemyList[i]->setTexture(nullptr);
						//enemy = nullptr;

						//enemy = nullptr;
						//enemy = new Enemy();
					}

				}
			}

			// Change player sprite when attacking
			//if (mouseInsideEnemy(mousePhysicsCoords, enemy1) == true) {
			//	tempHealth -= tempDamage;
			//	std::cout << "\n" << "Clicked/Enemy Takes Damage";

			//	std::cout << "Damage Value: " << tempHealth << std::endl;

			//	if (tempHealth <= 0) {
			//		std::cout << "\n" << "Enemy Dies";
			//		enemy1->setTexture(nullptr);
			//		//enemy = nullptr;

			//		//enemy = nullptr;
			//		//enemy = new Enemy();
			//	}

			//}
			


		}
	}

	else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) { // when the left click of the mouse is released
		
	}

	//else if (event.type == SDL_MOUSEMOTION && movedObject) { // When movedStar is equal to one of the stars, use mouse motion to move the planet around 
	//	// set the poistion of the movedStar to that of the mouse when moving it around
	//	movedObject->getPos() = mousePhysicsCoords;
	//}
}

void SceneC::OnDestroy() {
	// Free loaded images
	//delete stoneTileTexture;
	//delete grassTileTexture;
	//player->OnDestroy();

	delete healthBar;
	healthBar = nullptr;

	for (int i = 0; i < 5; i++) {
		space[i].OnDestroy();
	}
	panel.OnDestroy();
	enemyManager->OnDestroy();
	delete enemyManager;
}


SceneC::~SceneC() {
	std::cout << "deleting child class: SceneC." << std::endl;
	// delete
	
}