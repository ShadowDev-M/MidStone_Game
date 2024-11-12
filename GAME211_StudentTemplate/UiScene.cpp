#include "UiScene.h"
#include <VMath.h>
#include <functional>
#include "CreateItems.h"


// See notes about this constructor in Scene1.h.
UiScene::UiScene(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;

	// player spawns in middle of screen
	player = new Player(Vec3(xAxis / 2.0f, yAxis / 2.0f, 0.0f), Vec3(), Vec3(), 1.0f, 0, 0, 0, 0);
	player->setRenderer(renderer);
	player->setWidth(1.0f);
	player->setHeight(1.0f);
}

// To render chunks and set id to tiles need to setup camera first
// Once camera is set, use it to only render tiles inside the camera (good for optimizaion)

// Once that is done, setup attaching tile ids to specific images to load in. 


//defualt initial item
Item* currentItem = playerInventory.getItem(0, 3);

bool UiScene::OnCreate() {
	// Check to make sure loading scene works
	std::cout << "Entering UiScene" << std::endl;
	playerInventory.addItem(sword);
	playerInventory.addItem(shield);
	playerInventory.printInventory();


	int w, h;
	SDL_GetWindowSize(window,&w,&h);

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

	player->OnCreate();
	
	
	text.OnCreate(renderer,
		Vec2(w/2 - 150, h/2 - 100) //Pos
		, "Fonts/SuperDream-ax3vE.ttf" //Font Path
		, { 255, 255, 255 } //Color
		, 100 //Font Size
		, 100.0f // Height
		, 450.0f //Width
		, "Unreal Engine Is Dumb"); //Message

	panel.OnCreate(renderer, Vec2(w / 2 , h / 2 + 100), "textures/StoneTile.png", 5);
	if(currentItem != nullptr)
		panel.AddIcon(currentItem->filePath, 3.0f).AddButton(std::bind(&UiScene::ButtonTest, this));
	else
		panel.AddIcon("textures/emptySlot.png", 3.0f).AddButton(std::bind(&UiScene::ButtonTest, this));
	return true;
}

void UiScene::ButtonTest()
{
	text.ChangeMessage("Please Stop Using Unreal Engine");
}

void UiScene::Update(const float deltaTime) {

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

	// Update players projection matrix
	player->setProjection(projectionMatrix);

	player->Update(deltaTime);
}

void UiScene::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render the player
	player->Render(0.1f);
	text.Render();
	panel.Render();
	
	SDL_RenderPresent(renderer);
}

void UiScene::refreshIcon() {
	// Clear the current icon
	panel.ClearIcons();

	// Add the new icon based on the current item
	if (currentItem != nullptr) {
		// Add the current item's icon
		panel.AddIcon(currentItem->filePath, 3.0f).AddButton(std::bind(&UiScene::ButtonTest, this));
	}
	else {
		// If no item, show an empty slot, which is just a plus icon
		panel.AddIcon("textures/emptySlot.png", 3.0f).AddButton(std::bind(&UiScene::ButtonTest, this));
	}
}

void UiScene::HandleEvents(const SDL_Event& event)
{
	player->HandleEvents(event);
	panel.HandleEvent(event);

	if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
		// Press number to change your current item
		switch (event.key.keysym.scancode) {
		case SDL_SCANCODE_1:
			currentItem = playerInventory.getItem(0, 0);
			break;
		case SDL_SCANCODE_2:
			currentItem = playerInventory.getItem(0, 1);
			break;
		case SDL_SCANCODE_3:
			currentItem = playerInventory.getItem(0, 2);
			break;
		case SDL_SCANCODE_4:
			currentItem = playerInventory.getItem(0, 3);
			break;
		case SDL_SCANCODE_5:
			currentItem = playerInventory.getItem(0, 4);
			break;
		default:
			break;
		}

		// Refresh the icon after item change
		refreshIcon();

		// more of a debug/feedback feature. 
		if (currentItem) {
			std::cout << "Selected item: " << currentItem->itemName << std::endl;
		}
		else {
			std::cout << "Selected slot is empty." << std::endl;
		}
	}
}

Vec3 UiScene::screenCoords(Vec3 gameCoords)
{
	return projectionMatrix * gameCoords;
}

// Creates a surface (cpu) and converts it to a texture (gpu)
// Surface is better for rendering single objects like the player
// However the gpu is most of the time always better in all cases
// mostly because its faster and can handle more (use for tiling and chunks)
SDL_Texture* UiScene::loadImage(const char* textureFile)
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
SDL_Rect UiScene::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale)
{
	// Get size of the input texture in pixels
	SDL_Point size{};
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void UiScene::OnDestroy() {
	//player->OnDestroy();
}

UiScene::~UiScene() {
}