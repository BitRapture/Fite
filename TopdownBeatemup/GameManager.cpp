#include "GameManager.h"

void GameManager::Run()
{
	mGameLoop = mInitialised;

	double tempTime = 0.1;

	SDL_Surface* rawSheet = IMG_Load("Media/FiteCharacter.png");
	SDL_Texture* spriteSheet = SDL_CreateTextureFromSurface(mContext, rawSheet);

	Player mPlayer(mContext, spriteSheet, &mEvents);

	while (mGameLoop)
	{
		mGameLoop = !mEvents.Poll();

		SDL_RenderClear(mContext);

		mPlayer.Update(tempTime);
		mPlayer.Render();

		SDL_RenderPresent(mContext);
	}

	SDL_DestroyTexture(spriteSheet);
	SDL_FreeSurface(rawSheet);
}

GameManager::GameManager()
{
	mWindow = SDL_CreateWindow("Fite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	mContext = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	mInitialised = (mWindow != nullptr && mContext != nullptr);
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(mContext);
	SDL_DestroyWindow(mWindow);
}