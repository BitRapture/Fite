#include "GameManager.h"

GameManager::GameManager()
{
	mWindow = SDL_CreateWindow("Fite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_INPUT_GRABBED);
	mContext = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	mInitialised = (mWindow != nullptr && mContext != nullptr);
}

GameManager::~GameManager()
{

}