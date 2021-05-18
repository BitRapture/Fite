#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <vector>

#include "Scenes.h"
#include "EventManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
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
	// Resource managing system
	// contains all resources and media
	ResourceManager mResources;

	// Event managing system
	EventManager mEvents;
	
	// Full entity list
	// Virtual dispatching system
	std::vector<Entity*> mEntityList;

	// List of all GameObjects
	std::vector<GameObject*> mGameObjects;

	// GameObject collision managing system
	CollisionManager mCollisions;

	// Scene manager
	std::vector<Scene*> mScenes;

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