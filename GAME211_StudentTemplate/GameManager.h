#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <SDL.h>
#include <iostream>
#include "Window.h"
#include "Timer.h"
#include "Scene.h"
#include "Player.h"


class GameManager {
private:
	/// These are called "forward declarations" The idea is that a pointer is 
	/// really just an unsigned int, so to create a pointer to it you really only
	/// need to tell the compiler that there is a class called Window and I need
	/// a pointer to it, thus the "class Window*" means trust me, there is a class 
	/// called Window, I just need a pointer to it.

	/// If that was too much for your brain, just #include "Window.h" and declare
	/// Window *ptr and don't use the word "class"  This is a second semester C++
	/// topic anyway
	class Window *windowPtr;
	class Timer *timer;
	bool isRunning;
	class Scene *currentScene;
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	void handleEvents();
	void LoadScene(int i);
	bool ValidateCurrentScene();


public:
	GameManager();
	~GameManager();
	bool OnCreate();
	void OnDestroy();


	// These might be unfamiliar
	float getSceneHeight();
	float getSceneWidth();
	float getWindowHeight() const;
	float getWindowWidth() const;
	//void setWindowHeight(float WindowWidth) const;
	//void setWindowWidth(float WindowHeight) const;

	Matrix4 getProjectionMatrix();
	SDL_Renderer* getRenderer();

	void Run();
    
};
#endif


