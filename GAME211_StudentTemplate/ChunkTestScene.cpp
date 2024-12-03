#include "ChunkTestScene.h"
#include <VMath.h>
#include "UiPanel.h"


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


	player = new Player(Vec3(1000 +2, 1000 +3, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
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

		
		
{1004, 1002, 1}, {1005, 1002, 1}, {1006, 1002, 1}, {1007, 1002, 1}, {1008, 1002, 1},
{1003, 1003, 1}, {1004, 1003, 1}, {1005, 1003, 1}, {1006, 1003, 1}, {1007, 1003, 1}, {1008, 1003, 1}, {1009, 1003, 1}, {1010, 1003, 1},
{1002, 1004, 1}, {1003, 1004, 1}, {1004, 1004, 1}, {1005, 1004, 1}, {1006, 1004, 1}, {1007, 1004, 1}, {1008, 1004, 1}, {1009, 1004, 1}, {1010, 1004, 1}, {1011, 1004, 1},
{1002, 1005, 1}, {1003, 1005, 1}, {1004, 1005, 1}, {1005, 1005, 1}, {1006, 1005, 1}, {1007, 1005, 1}, {1008, 1005, 1}, {1009, 1005, 1}, {1010, 1005, 1}, {1011, 1005, 1},
{1003, 1006, 1}, {1004, 1006, 1}, {1005, 1006, 1}, {1006, 1006, 1}, {1007, 1006, 1}, {1008, 1006, 1}, {1009, 1006, 1}, {1010, 1006, 1}, {1011, 1006, 1},
{1004, 1007, 1}, {1005, 1007, 1}, {1006, 1007, 1}, {1007, 1007, 1}, {1008, 1007, 1}, {1009, 1007, 1}, {1010, 1007, 1},
{1005, 1008, 1}, {1006, 1008, 1}, {1007, 1008, 1}, {1008, 1008, 1}, {1009, 1008, 1},
{1020, 1018, 1}, {1021, 1018, 1}, {1022, 1018, 1}, {1023, 1018, 1}, {1024, 1018, 1},
{1019, 1019, 1}, {1020, 1019, 1}, {1021, 1019, 1}, {1022, 1019, 1}, {1023, 1019, 1}, {1024, 1019, 1}, {1025, 1019, 1}, {1026, 1019, 1},
{1018, 1020, 1}, {1019, 1020, 1}, {1020, 1020, 1}, {1021, 1020, 1}, {1022, 1020, 1}, {1023, 1020, 1}, {1024, 1020, 1}, {1025, 1020, 1}, {1026, 1020, 1}, {1027, 1020, 1},
{1018, 1021, 1}, {1019, 1021, 1}, {1020, 1021, 1}, {1021, 1021, 1}, {1022, 1021, 1}, {1023, 1021, 1}, {1024, 1021, 1}, {1025, 1021, 1}, {1026, 1021, 1}, {1027, 1021, 1},
{1019, 1022, 1}, {1020, 1022, 1}, {1021, 1022, 1}, {1022, 1022, 1}, {1023, 1022, 1}, {1024, 1022, 1}, {1025, 1022, 1}, {1026, 1022, 1}, {1027, 1022, 1},
{1020, 1023, 1}, {1021, 1023, 1}, {1022, 1023, 1}, {1023, 1023, 1}, {1024, 1023, 1}, {1025, 1023, 1}, {1026, 1023, 1},
{1021, 1024, 1}, {1022, 1024, 1}, {1023, 1024, 1}, {1024, 1024, 1}, {1025, 1024, 1}

	};


	//player->hitbox.setObstacles(faces);
	

	RegionOne.addLoadingEntity(player);


	//std::cout << changesIndex.at(0).id;

	stoneTileTexture = camera.refinedLoadImage(stoneTile, renderer);

	grassTileTexture = camera.refinedLoadImage(grassTile, renderer);

	return true;
}


bool SceneC::mouseInsideObject(Vec3 mouseCoords, Body* body)
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

	player->RenderUI();


	


	// TileFaces newTile = TileFaces(Vec2(5, 4), Vec2(10, 4), wall);
	/*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, newTile.PointOne.x, newTile.PointOne.y, newTile.PointTwo.x, newTile.PointTwo.y);*/


	// update screen
	SDL_RenderPresent(renderer);
}

void SceneC::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	player->HandleEvents(event);



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
				if (mouseInsideObject(mousePhysicsCoords, enemyList[i]) == true) {
					enemyList[i]->healthpoints -= player->dmgValue;
					std::cout << "\n" << "Clicked/Enemy Takes Damage";

					std::cout << "Damage Value: " << tempHealth << std::endl;

					if (enemyList[i]->healthpoints <= 0) {


						// Instead of settingTexture Call EnemyDeath function
						std::cout << "\n" << "Enemy Dies";
						enemyList[i]->setTexture(nullptr);
						//enemy = nullptr;

					//enemy = nullptr;
					//enemy = new Enemy();
					}
				}
				
			}
			
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

	enemyManager->OnDestroy();
	delete enemyManager;
}


SceneC::~SceneC() {
	std::cout << "deleting child class: SceneC." << std::endl;
	// delete
	
}