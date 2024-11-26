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
	player->SetRegion(&RegionOne);
	//RegionOne.setPlayer(player);


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
	player->OnCreate();

	projectionMatrix = camera.getProjectionMatrix();

	
	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}
	

	// Creating Chunks and Rendering them should be their own methods
	
	RegionOne.OnCreate();
	changesIndex = {
	{0, 0, 1}, {1, 2, 1}, {2,3,1}, {18,20,1} };


	
	
	
	TileFaces sword1 = TileFaces();
	sword1.PointOne = Vec2(sword->getPos().x - 0.5f, sword->getPos().y);
	sword1.PointTwo = Vec2(sword->getPos().x + 0.5f, sword->getPos().y);
	std::vector<TileFaces> faces;
	faces.push_back(sword1);



	player->hitbox.setObstacles(faces);
	

	//RegionOne.addLoadingEntity(player);


	//std::cout << changesIndex.at(0).id;

	stoneTileTexture = loadImage(stoneTile);

	grassTileTexture = loadImage(grassTile);

	ghostTexture = loadImage(ghost);
	
	swordTexture = loadImage(sword);

	return true;
}

// could add to camera after if it needs to be accesed outside of scenes
SDL_Texture* SceneC::loadImage(Body* body)
{
	SDL_Texture* bodyTexture;
	bodyTexture = camera.loadImage(body->GetTextureFile(), renderer);
	return bodyTexture;
}



void SceneC::Update(const float deltaTime) {
	//// Will make this its own extracted function after (will put in camera class too)

	camera.cameraFollowsPlayer(player, window);
	projectionMatrix = camera.getProjectionMatrix();

	player->Update(deltaTime);
	RegionOne.Update();
	
	if (testh) {
		RegionOne.setTile(changesIndex);
			testh = false;
	};


	//std::cout << "(" << player->getPos().x << ") " << std::endl;

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

	Vec2 playerChunkPos = Vec2(0,0);
	//for (int i = 0; i < 16*16; i++) {
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			Vec2 chunkRenderPos = Vec2((playerChunkPos.x)+i, (playerChunkPos.y)+j);

			for (int x = 0; x < 16; x++) {
				for (int y = 0; y < 16; y++) {
					int id = RegionOne.getChunkTileID(chunkRenderPos, Vec2(x, y));

					Vec3 chunkInfo = Vec3(x + 16 * chunkRenderPos.x, y + 16 * chunkRenderPos.y, id);
					
					if (chunkInfo.z == 0) {

						grassTile->setPos(Vec3(chunkInfo.x, chunkInfo.y, 0.0f));

						Vec3 grassTileCoords = camera.worldToScreenCoords(grassTile->getPos());

						SDL_Rect grassDest = scale(grassTileTexture, grassTileCoords.x, grassTileCoords.y, scalingFactor(grassTileTexture, grassTile) + 0.1f);
						
						SDL_RenderCopy(renderer, grassTileTexture, nullptr, &grassDest);

					}
					if (chunkInfo.z == 1) {
						stoneTile->setPos(Vec3(chunkInfo.x, chunkInfo.y, 0.0f));

						Vec3 stoneTileCoords = camera.worldToScreenCoords(stoneTile->getPos());

						SDL_Rect stoneDest = scale(stoneTileTexture, stoneTileCoords.x, stoneTileCoords.y, scalingFactor(stoneTileTexture, stoneTile) + 0.1f); //+ 0.1f
						
						SDL_RenderCopy(renderer, stoneTileTexture, nullptr, &stoneDest);
					}
				}
			}
		}
	}
	//}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (TileFaces tile : player->permFaces) {
		Vec3 screenCoords1 = projectionMatrix * Vec3(tile.PointOne.x, tile.PointOne.y, 0.0f);
		Vec3 screenCoords2 = projectionMatrix * Vec3(tile.PointTwo.x, tile.PointTwo.y, 0.0f);;

		SDL_RenderDrawLine(renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	}

	
	
	// Everything now needs to use the scalingfactor to properly scale with the screen
	//player->Render(camera.scalingFactor(ghostTexture, player));
	
	
	

	Vec3 ghostLocationTest = camera.worldToScreenCoords(player->getPos());
	SDL_Rect ghostDest = scale(ghostTexture, ghostLocationTest.x, ghostLocationTest.y, scalingFactor(ghostTexture, ghost));
	SDL_RenderCopy(renderer, ghostTexture, nullptr, &ghostDest);

	camera.renderObject(sword, swordTexture, renderer);

	//body->GetTexture() body->

	// update screen
	SDL_RenderPresent(renderer);
}

void SceneC::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	player->HandleEvents(event);
}

float SceneC::scalingFactor(SDL_Texture*& texture, Body* body)
{
	float bodyScreenWidth = body->getWidth() * game->getWindowWidth() / xAxis;
	SDL_Point size{};
	// get the size of the orginal texture
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	// divide the size of the texture I want in pixel / size of orginal texture
	float textureScale = bodyScreenWidth / size.x;
	return textureScale;
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
	//delete stoneTileTexture;
	//delete grassTileTexture;
	//player->OnDestroy();
}


SceneC::~SceneC() {
	std::cout << "deleting child class: SceneC." << std::endl;
	// delete
	
}