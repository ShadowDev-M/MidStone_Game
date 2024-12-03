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


	player = new Player(Vec3(1000 -2, 1000 -3, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	player->setRenderer(renderer);
	player->SetTextureFile("textures/PlayerFacingFrontIdle.png");
	player->setWidth(1.0f);
	player->setHeight(1.0f);
	player->SetRegion(&RegionOne);
	player->SubscribeToOnAttack(
		[this](Vec3 mousePos, float damage) {
			PlayerAttack(mousePos, damage);
		});
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
	enemyManager->SpawnEnemy(10, player);

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
	{989, 987, 1}, {990, 987, 1}, {991, 987, 1}, {992, 987, 1}, {993, 987, 1},
{988, 988, 1}, {989, 988, 1}, {990, 988, 1}, {991, 988, 1}, {992, 988, 1}, {993, 988, 1}, {994, 988, 1},
{988, 989, 1}, {989, 989, 1}, {990, 989, 1}, {991, 989, 1}, {992, 989, 1}, {993, 989, 1}, {994, 989, 1}, {995, 989, 1},
{987, 990, 1}, {988, 990, 1}, {989, 990, 1}, {990, 990, 1}, {991, 990, 1}, {992, 990, 1}, {993, 990, 1}, {994, 990, 1}, {995, 990, 1},
{986, 991, 1}, {987, 991, 1}, {988, 991, 1}, {989, 991, 1}, {990, 991, 1}, {991, 991, 1}, {992, 991, 1}, {993, 991, 1}, {994, 991, 1}, {995, 991, 1}, {996, 991, 1},
{986, 992, 1}, {987, 992, 1}, {988, 992, 1}, {989, 992, 1}, {990, 992, 1}, {991, 992, 1}, {992, 992, 1}, {993, 992, 1}, {994, 992, 1}, {995, 992, 1}, {996, 992, 1}, {997, 992, 1},
{986, 993, 1}, {987, 993, 1}, {988, 993, 1}, {989, 993, 1}, {990, 993, 1}, {991, 993, 1}, {992, 993, 1}, {993, 993, 1}, {994, 993, 1}, {995, 993, 1}, {996, 993, 1}, {997, 993, 1},
{986, 994, 1}, {987, 994, 1}, {988, 994, 1}, {989, 994, 1}, {990, 994, 1}, {991, 994, 1}, {992, 994, 1}, {993, 994, 1}, {994, 994, 1}, {995, 994, 1}, {996, 994, 1},
{987, 995, 1}, {988, 995, 1}, {989, 995, 1}, {990, 995, 1}, {991, 995, 1}, {992, 995, 1}, {993, 995, 1}, {994, 995, 1}, {995, 995, 1},
		
	{1001, 1001, 1}, {1002, 1001, 1}, {1003, 1001, 1},
{1001, 1002, 1}, {1002, 1002, 1}, {1003, 1002, 1}, {1010, 1002, 1}, {1011, 1002, 1},
{1001, 1003, 1}, {1002, 1003, 1}, {1003, 1003, 1}, {1009, 1003, 1}, {1010, 1003, 1}, {1011, 1003, 1}, {1012, 1003, 1},
{1008, 1004, 1}, {1009, 1004, 1}, {1010, 1004, 1}, {1011, 1004, 1}, {1012, 1004, 1},
{1008, 1005, 1}, {1009, 1005, 1}, {1010, 1005, 1}, {1011, 1005, 1}, {1012, 1005, 1},
{1010, 1006, 1},




{1012, 1011, 1}, {1013, 1011, 1},
{1011, 1012, 1}, {1012, 1012, 1}, {1013, 1012, 1}, {1014, 1012, 1},
{1010, 1013, 1}, {1011, 1013, 1}, {1012, 1013, 1}, {1013, 1013, 1}, {1014, 1013, 1}, {1015, 1013, 1},
{1010, 1014, 1}, {1011, 1014, 1}, {1012, 1014, 1}, {1013, 1014, 1}, {1014, 1014, 1}, {1015, 1014, 1},
{1010, 1015, 1}, {1011, 1015, 1}, {1012, 1015, 1}, {1013, 1015, 1}, {1014, 1015, 1},

{1021, 1019, 1}, {1022, 1019, 1}, {1023, 1019, 1}, {1024, 1019, 1}, {1025, 1019, 1},
{1020, 1020, 1}, {1021, 1020, 1}, {1022, 1020, 1}, {1023, 1020, 1}, {1024, 1020, 1}, {1025, 1020, 1}, {1026, 1020, 1},
{1020, 1021, 1}, {1021, 1021, 1}, {1022, 1021, 1}, {1023, 1021, 1}, {1024, 1021, 1}, {1025, 1021, 1}, {1026, 1021, 1}, {1027, 1021, 1},
{1019, 1022, 1}, {1020, 1022, 1}, {1021, 1022, 1}, {1022, 1022, 1}, {1023, 1022, 1}, {1024, 1022, 1}, {1025, 1022, 1}, {1026, 1022, 1}, {1027, 1022, 1},
{1018, 1023, 1}, {1019, 1023, 1}, {1020, 1023, 1}, {1021, 1023, 1}, {1022, 1023, 1}, {1023, 1023, 1}, {1024, 1023, 1}, {1025, 1023, 1}, {1026, 1023, 1}, {1027, 1023, 1}, {1028, 1023, 1},
{1018, 1024, 1}, {1019, 1024, 1}, {1020, 1024, 1}, {1021, 1024, 1}, {1022, 1024, 1}, {1023, 1024, 1}, {1024, 1024, 1}, {1025, 1024, 1}, {1026, 1024, 1}, {1027, 1024, 1}, {1028, 1024, 1}, {1029, 1024, 1},
{1018, 1025, 1}, {1019, 1025, 1}, {1020, 1025, 1}, {1021, 1025, 1}, {1022, 1025, 1}, {1023, 1025, 1}, {1024, 1025, 1}, {1025, 1025, 1}, {1026, 1025, 1}, {1027, 1025, 1}, {1028, 1025, 1}, {1029, 1025, 1},
{1018, 1026, 1}, {1019, 1026, 1}, {1020, 1026, 1}, {1021, 1026, 1}, {1022, 1026, 1}, {1023, 1026, 1}, {1024, 1026, 1}, {1025, 1026, 1}, {1026, 1026, 1}, {1027, 1026, 1}, {1028, 1026, 1},
{1019, 1027, 1}, {1020, 1027, 1}, {1021, 1027, 1}, {1022, 1027, 1}, {1023, 1027, 1}, {1024, 1027, 1}, {1025, 1027, 1}, {1026, 1027, 1}, {1027, 1027, 1},

	};


	//player->hitbox.setObstacles(faces);


	RegionOne.addLoadingEntity(player);


	//std::cout << changesIndex.at(0).id;

	stoneTileTexture = camera.refinedLoadImage(stoneTile, renderer);

	grassTileTexture = camera.refinedLoadImage(grassTile, renderer);

	return true;
}

void SceneC::PlayerAttack(Vec3 mouseCoord_, float damage_)
{

	std::cout << "Bruh Was Called" << endl;
	mousePhysicsCoords = camera.ScreenToWorldCoords(Vec3(mouseCoord_.x + mouseOffSet, mouseCoord_.y + mouseOffSet, 0.0f));

	enemyManager->AttackEnemy(mousePhysicsCoords, damage_);
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
	
	if (player->hasShoes()) {
		player->walkSpeedMax = 3.0f;
	}
	else {
		player->walkSpeedMax = 2.0f;
	}
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
			Vec2 chunkRenderPos = Vec2((playerChunkPos.x - 1) + i, (playerChunkPos.y - 1) + j);

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