#include "GameManager.h"

void GameManager::Run()
{
	// Check SDL has initialised everything
	if (!mInitialised) return;

	// Declare and init time variables
	Uint64 timeCurrent = 0, timeLast = SDL_GetPerformanceCounter();
	// Delta time for object movement
	double deltaTime = 0;
	// Counter frequency
	double counterFreq = 1000.0 / SDL_GetPerformanceFrequency();

	SDL_Surface* rawSheet = IMG_Load("Media/FiteCharacter.png");
	SDL_Surface* rawESheet = IMG_Load("Media/FiteEnemy.png");

	while (mGameLoop)
	{
		// Poll all events (keyboard, window, mouse, etc)
		mGameLoop = !mEvents.Poll();

		// Calculate deltaTime (miliseconds)
		timeCurrent = SDL_GetPerformanceCounter();
		deltaTime = (timeCurrent - timeLast) * counterFreq;
		timeLast = timeCurrent;

		// Update methods

		// Render methods
		SDL_RenderClear(mContext);

		SDL_RenderPresent(mContext);
	}

	SDL_FreeSurface(rawSheet);
	SDL_FreeSurface(rawESheet);
}

GameManager::GameManager()
{
	mWindow = SDL_CreateWindow("Fite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	mContext = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	mInitialised = (mWindow != nullptr && mContext != nullptr);
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(mContext);
	SDL_DestroyWindow(mWindow);
}