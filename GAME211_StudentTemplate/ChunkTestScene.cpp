#include "ChunkTestScene.h"
#include <VMath.h>



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


	player = new Player(Vec3(xAxis / 2.0f, yAxis / 2.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	player->setRenderer(renderer);
	player->setWidth(1.0f);
	player->setHeight(1.0f);

	stoneTile = new Body(Vec3(xAxis / 2.0f, yAxis / 2.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	stoneTile->SetTextureFile("textures/StoneTile.png");
	stoneTile->setWidth(1.0f);
	stoneTile->setHeight(1.0f);


	grassTile = new Body(Vec3(xAxis / 2.0f, yAxis / 2.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	grassTile->SetTextureFile("textures/GrassTile.png");
	grassTile->setWidth(1.0f);
	grassTile->setHeight(1.0f);

	
	ghost = new Body(Vec3(xAxis / 2.0f, yAxis / 2.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	ghost->SetTextureFile("textures/Pinky.png");
	ghost->setWidth(1.0f);
	ghost->setHeight(1.0f);


	sword = new Body(Vec3(xAxis / 2.0f + 1, yAxis / 2.0f + 1, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	sword->SetTextureFile("textures/sword.png");
	sword->setWidth(1.0f);
	sword->setHeight(1.0f);


	stoneTileTexture = nullptr;
	grassTileTexture = nullptr;
	ghostTexture = nullptr;
	swordTexture = nullptr;

}

// transfer data to heap
bool SceneC::OnCreate() {
	// Check to make sure loading new scene works
	std::cout << "Entering ChunkTest" << std::endl;
	testh = true;

	

	/*int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, LEVEL_WIDTH, 0.0f, LEVEL_HEIGHT, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;*/
	



	camera.OnCreate();	
	projectionMatrix = camera.getProjectionMatrix();
	
	
	player->OnCreate();
	//enemy->OnCreate();

	//enemy->setProjection(projectionMatrix);
	//enemy->setInverse(inverseProjection);

	
	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	

	// Creating Chunks and Rendering them should be their own methods
	

	changesIndex = {
		{0, 0, 1}, {1, 2, 1}, {2,3,1}, {18,20,1} };

	
	RegionOne.addLoadingEntity(player);


	std::cout << changesIndex.at(0).id;

	stoneTileTexture = camera.refinedLoadImage(stoneTile, renderer);

	grassTileTexture = camera.refinedLoadImage(grassTile, renderer);

	ghostTexture = camera.refinedLoadImage(ghost, renderer);
	
	swordTexture = camera.refinedLoadImage(sword, renderer);

	return true;
}



void SceneC::Update(const float deltaTime) {
	//// Will make this its own extracted function after (will put in camera class too)
	
	camera.cameraFollowsPlayer(player, window);
	projectionMatrix = camera.getProjectionMatrix();

	player->Update(deltaTime);
	RegionOne.Update();


	//enemy->Update(deltaTime);
	
	if (testh) {
		RegionOne.setTile(changesIndex);
			testh = false;
	};




	//std::cout << player->getPos().x << ", " << player->getPos().y << "\n";
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



	// Everything now needs to use the scalingfactor to properly scale with the screen
	player->Render(camera.scalingFactor(player->getTexture(), player));

	
	camera.renderObject(sword, swordTexture, renderer);
	

	//body->GetTexture() body->

	// update screen
	SDL_RenderPresent(renderer);
}

void SceneC::OnDestroy() {
	// Free loaded images
	//delete stoneTileTexture;
	//delete grassTileTexture;
	//player->OnDestroy();
}


SceneC::~SceneC() {
	std::cout << "deleting child class: SceneC." << std::endl;
	// delete
	
}