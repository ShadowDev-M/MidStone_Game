#include <Vector>
#include <Vector.h>
#include "Enemy.h"

class EnemyManager 
{
private:
	std::vector<Vec2> enemyPositions;
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4 inverseProjection;	// set in OnCreate()
	Scene* activeScene;
public:
	
	EnemyManager();
	EnemyManager(Scene* activeScene_);

	//List of enemies
	std::vector<Enemy*> enemyList = {};
	
	//Spawn enemies
	std::vector<Enemy*> spawnEnemy(int amount);

	//Render enemies
	void RenderEnemies();

	void Update(float deltaTime);
};