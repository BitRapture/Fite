#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <SDL.h>

class GameManager
{
// GameManager flags
private:
	// Initialisation flag
	bool mInitialised{ false };

// SDL2 variables
private:
	SDL_Window* mWindow{ nullptr };
	SDL_Renderer* mContext{ nullptr };

public:
	// Constructor
	GameManager();
	// Destructor
	~GameManager();
};

#endif