#include "MenuScene.h"
#include <VMath.h>

// See notes about this constructor in Scene1.h.
SceneM::SceneM(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;


	// Default way to create a new surface/texture for this engine
	// going to rework it cause its not efficient
	/*
	test = new Body();
	SDL_Texture* texture;
	texture = IMG_LoadTexture(renderer, "pinky.png");

	test->setTexture(texture);
	*/

	test = new Body();
	test->SetTextureFile("textures/pinky.png");

	testTexture = nullptr;

}

bool SceneM::OnCreate() {
	// Check to make sure loading new scene works
	std::cout << "Entering MainMenu" << std::endl;

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	testTexture = loadImage(test->GetTextureFile());
	
	return true;
}

void SceneM::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);


}

void SceneM::Render() {
	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	
	// Clear the screen
	SDL_RenderClear(renderer);

	// test
	SDL_RenderCopy(renderer, testTexture, nullptr, nullptr);

	// update screen
	SDL_RenderPresent(renderer);
}

void SceneM::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}

Vec3 SceneM::screenCoords(Vec3 gameCoords)
{	
	return projectionMatrix * gameCoords;
}


// Creates a surface (cpu) and converts it to a texture (gpu)
// Surface is better for rendering single objects like the player
// However the gpu is most of the time always better in all cases
// mostly because its faster and can handle more (use for tiling and chunks)
SDL_Texture* SceneM::loadImage(const char* textureFile)
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
SDL_Rect SceneM::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale)
{
	// Get size of the input texture in pixels
	SDL_Point size{};
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

void SceneM::OnDestroy() {
	// Free loaded images
	SDL_DestroyTexture(testTexture);
	testTexture = nullptr;
}


SceneM::~SceneM() {
	std::cout << "deleting child class: SceneM." << std::endl;
	// delete
	delete test;
}