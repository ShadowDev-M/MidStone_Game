#include "CollisionScene.h"
#include "BoxCollider.h"
#include "ChunkHandler.h"
#include <VMath.h>


// See notes about this constructor in Scene1.h.
CollisionScene::CollisionScene(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	player = new Player(Vec3(xAxis / 2.0f, yAxis / 2.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	player->setRenderer(renderer);
}


CollisionScene::~CollisionScene() {
}

bool CollisionScene::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	std::cout << w << " " << h;
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	player->setProjection(projectionMatrix);

	

	player->setImage(image);
	player->setTexture(texture);
	player->OnCreate();
	//Vec3 pos = game->getPlayer()->getPos();

	float mass = 1.0f;
	float radius = 0.5f;
	float orientation = 0.0f;
	float rotation = 0.0f;
	float angular = 0.0f;
	Vec3 position(0.5f * xAxis + 5, 0.5f * yAxis, 0.0f + 5);
	Vec3 velocity(0.0f, 0.0f, 0.0f);
	Vec3 acceleration(0.0f, 0.0f, 0.0f);

	block1 = new TestBlock
	(
		position,
		velocity,
		acceleration,
		mass,
		radius,
		orientation,
		rotation,
		angular,
		game
	);
	if (block1->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	std::vector<TileFaces> faces;

	TileFaces wall1(
		Vec2(block1->getPos().x - 2, block1->getPos().y),
		Vec2(block1->getPos().x + 2, block1->getPos().y),
		enemy
	);
	
	faces.push_back(wall1);
	// Second wall or enemy
	TileFaces enemy1(Vec2(7, 3), Vec2(7, 7),wall);
	
	faces.push_back(enemy1);
	
	
	
	//Creating wall


	/*TileFaces wall1 = TileFaces();
	wall1.PointOne = Vec2(block1->getPos().x - 2, block1->getPos().y);
	wall1.PointTwo = Vec2(block1->getPos().x + 2, block1->getPos().y);
	wall1.collisionType = wall;*/
	//Creating a vector
	
	
	//faces.push_back(wall1);

	/*wall1.PointOne = Vec2(7, 3);
	wall1.PointTwo = Vec2(7, 7);
	wall1.collisionType = enemy;
	faces.push_back(wall1);
	*/
	//Pass the vector to the player
	player->hitbox.setObstacles(faces);



	/*p1 = Vec2(300, 250);
	p2 = Vec2(600, 250);*/
	return true;
}

void CollisionScene::OnDestroy() {}

void CollisionScene::Update(const float deltaTime) {

	// Update player
	player->Update(deltaTime);
}

void CollisionScene::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Draw a line for testing
	Matrix4 projectionMat = game->getProjectionMatrix();
	Vec3 screenCoords1 = projectionMatrix * block1->getPos();
	Vec3 screenCoords2 = projectionMatrix * (block1->getPos() + Vec3(2, 0, 0));
	Vec3 screenCoords3 = projectionMatrix * (block1->getPos() + Vec3(-2, 0, 0));
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);
	SDL_RenderDrawLine(renderer, screenCoords1.x, screenCoords1.y, screenCoords3.x, screenCoords3.y);

	screenCoords1 = projectionMatrix * Vec3(7, 3, 0);
	screenCoords2 = projectionMatrix * Vec3(7, 7, 0);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, screenCoords1.x, screenCoords1.y, screenCoords2.x, screenCoords2.y);


	//Box Collider Debug Tool (Don't delete)
	/*Vec3 screenCoord = projectionMatrix * player->getPos();
	Vec2 imageSize = Vec2(player->getImage()->w * 0.1f, player->getImage()->h * 0.1f);
	Vec3 one = Vec3(screenCoord.x , screenCoord.y , 0);
	Vec3 two = Vec3(screenCoord.x + imageSize.x , screenCoord.y , 0);
	Vec3 three = Vec3(screenCoord.x, screenCoord.y + imageSize.y , 0);
	Vec3 four = Vec3(screenCoord.x + imageSize.x , screenCoord.y + imageSize.y , 0);*/
	//SDL_RenderDrawLine(renderer, one.x, one.y, two.x, two.y);
	//SDL_RenderDrawLine(renderer, one.x, one.y, three.x, three.y);
	//SDL_RenderDrawLine(renderer, three.x, three.y, four.x, four.y);
	//SDL_RenderDrawLine(renderer, two.x, two.y, four.x, four.y);

	// render the player
	player->Render(0.1f);
	block1->Render(0.10f);

	SDL_RenderPresent(renderer);
}

void CollisionScene::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	player->HandleEvents(event);
	
}
