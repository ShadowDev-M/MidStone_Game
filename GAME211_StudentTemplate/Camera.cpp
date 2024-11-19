#include "Camera.h"

Camera::Camera()
{

}

Camera::Camera(SDL_Window* sdlWindow_)
{
	window = sdlWindow_;
	renderer = SDL_GetRenderer(window);
}

Camera::~Camera()
{

}

bool Camera::OnCreate()
{


	Matrix4 ndc = MMath::viewportNDC(WINDOW_WIDTH, WINDOW_HEIGHT);
	Matrix4 ortho = MMath::orthographic(0.0f, LEVEL_WIDTH, 0.0f, LEVEL_HEIGHT, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	inverseProjection = MMath::inverse(projectionMatrix);

	// Initialize PNG image loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		std::cout << "SDL_image Error: " << IMG_GetError() << std::endl;
		return false;
	}

	return true;
}

void Camera::Update(const float deltaTime)
{

}

void Camera::OnDestroy()
{

}

void Camera::Render() const
{

}

void Camera::HandleEvents(const SDL_Event& sdlEvent)
{

}

void Camera::cameraFollowsPlayer(Player* player, SDL_Window* window)
{
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

}

// Creates a surface (cpu) and converts it to a texture (gpu)
// Surface is better for rendering single objects like the player
// However the gpu is most of the time always better in all cases
// mostly because its faster and can handle more (use for tiling and chunks)
SDL_Texture* Camera::loadImage(const char* textureFile, SDL_Renderer* renderer)
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

// Proper scaling to window size, scale offset default is 1
SDL_Rect Camera::scale(SDL_Texture* objectTexture, int start_x, int start_y, float scale)
{
	// Get size of the input texture in pixels
	SDL_Point size{};
	SDL_QueryTexture(objectTexture, nullptr, nullptr, &size.x, &size.y);
	SDL_Rect dest = { start_x, start_y, size.x * scale, size.y * scale };
	return dest;
}

float Camera::scalingFactor(SDL_Texture*& texture, Body* body)
{
	float bodyScreenWidth = body->getWidth() * WINDOW_WIDTH / LEVEL_WIDTH;
	SDL_Point size{};
	// get the size of the orginal texture
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	// divide the size of the texture I want in pixel / size of orginal texture
	float textureScale = bodyScreenWidth / size.x;
	return textureScale;
}

void Camera::renderObject(Body* object, SDL_Texture* objectTexture, SDL_Renderer* renderer)
{
	Vec3 worldCoords = worldToScreenCoords(object->getPos());
	SDL_Rect Dest = scale(objectTexture, worldCoords.x, worldCoords.y, scalingFactor(objectTexture, object));
	SDL_RenderCopy(renderer, objectTexture, nullptr, &Dest);
}

Vec3 Camera::worldToScreenCoords(Vec3 gameCoords)
{
	return projectionMatrix * gameCoords;
}

Vec3 Camera::ScreenToWorldCoords(Vec3 physicsCoords)
{
	return inverseProjection * physicsCoords;
}
