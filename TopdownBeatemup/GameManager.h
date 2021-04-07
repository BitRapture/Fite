#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include "EventManager.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "Enemy.h"

class GameManager
{
// GameManager flags
private:
	// Initialisation flag
	bool mInitialised{ false };
	// Main gameloop flag
	bool mGameLoop{ true };

// GameManager systems
private:
	// Event managing system
	EventManager mEvents;
	// Object managing system
	GameObjectManager mObjects;
	
	// Full entity list
	// Virtual dispatching system
	std::vector<Entity*> mEntityList;

// SDL2 variables
private:
	SDL_Window* mWindow{ nullptr };
	SDL_Renderer* mContext{ nullptr };

// Public methods
public:
	// Run the game
	void Run();

	// Constructor
	GameManager();
	// Destructor
	~GameManager();
};

#endif