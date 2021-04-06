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
	SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(mContext, rawSheet);
	SDL_Texture* spriteESheet = SDL_CreateTextureFromSurface(mContext, rawESheet);

	std::vector<Entity*> entityList;

	entityList.push_back(new Player(mContext, spriteSheet, &mEvents));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 64, 0));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 128, 100));
	entityList.push_back(new Enemy(mContext, spriteSheet, (Player*)entityList[0], 192, 150));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 256, 200));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 320, 250));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 384+64, 300));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 448+64, 350));
	entityList.push_back(new Enemy(mContext, spriteSheet, (Player*)entityList[0], 512+64, 400));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 576+64, 450));
	entityList.push_back(new Enemy(mContext, spriteESheet, (Player*)entityList[0], 640+64, 500));

	while (mGameLoop)
	{
		// Poll all events (keyboard, window, mouse, etc)
		mGameLoop = !mEvents.Poll();

		// Calculate deltaTime (miliseconds)
		timeCurrent = SDL_GetPerformanceCounter();
		deltaTime = (timeCurrent - timeLast) * counterFreq;
		timeLast = timeCurrent;

		// Update methods
		for (int i = 0; i < entityList.size(); ++i) entityList[i]->Update(deltaTime);

		// Render methods
		SDL_RenderClear(mContext);

		for (int i = 0; i < entityList.size(); ++i) entityList[i]->Render();

		SDL_RenderPresent(mContext);
	}

	for (int i = 0; i < entityList.size(); ++i) delete entityList[i];

	SDL_DestroyTexture(spriteSheet);
	SDL_DestroyTexture(spriteESheet);
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