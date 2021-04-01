#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>
#include "EventManager.h"

class GameManager
{
// GameManager flags
private:
	// Initialisation flag
	bool mInitialised{ false };
	// Main gameloop flag
	bool mGameLoop{ false };

// SDL2 variables
private:
	SDL_Window* mWindow{ nullptr };
	SDL_Renderer* mContext{ nullptr };

public:
	// Run the game
	void Run();

	// Constructor
	GameManager();
	// Destructor
	~GameManager();
};

#endif