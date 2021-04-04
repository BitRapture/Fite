#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>

#include "EventManager.h"
#include "Player.h"

class GameManager
{
// GameManager flags
private:
	// Initialisation flag
	bool mInitialised{ false };
	// Main gameloop flag
	bool mGameLoop{ false };

// GameManager systems
private:
	// Event managing system
	EventManager mEvents;

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