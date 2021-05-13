#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include "EventManager.h"
#include "CollisionManager.h"
#include "Projectiles.h"
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
	
	// Full entity list
	// Virtual dispatching system
	std::vector<Entity*> mEntityList;

	// GameObject collision managing system
	CollisionManager mCollisions;

// SDL2 variables
private:
	// The application window
	SDL_Window* mWindow{ nullptr };
	// The renderer
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