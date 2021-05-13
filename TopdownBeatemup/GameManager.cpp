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

	SDL_Surface* sPlayer = IMG_Load("Media/FiteCharacter.png");
	SDL_Surface* sEnemy = IMG_Load("Media/FiteEnemy.png");
	SDL_Surface* sBullet = IMG_Load("Media/ProjectileBullet.png");
	SDL_Texture* tPlayer = SDL_CreateTextureFromSurface(mContext, sPlayer);
	SDL_Texture* tEnemy = SDL_CreateTextureFromSurface(mContext, sEnemy);
	SDL_Texture* tBullet = SDL_CreateTextureFromSurface(mContext, sBullet);

	SDL_FreeSurface(sPlayer);
	SDL_FreeSurface(sEnemy);
	SDL_FreeSurface(sBullet);

	GameObject* player = new Player(mContext, tPlayer, &mEvents);
	GameObject* enemy = new Enemy(mContext, tEnemy, (Player*)player, 128, 128);

	mEntityList.push_back(enemy);
	mEntityList.push_back(player);
	mCollisions.AddObject(enemy);

	int am = 0;

	while (mGameLoop)
	{
		// Poll all events (keyboard, window, mouse, etc)
		mGameLoop = !mEvents.Poll();
	
		// Calculate deltaTime (miliseconds)
		timeCurrent = SDL_GetPerformanceCounter();
		deltaTime = (timeCurrent - timeLast) * counterFreq;
		timeLast = timeCurrent;

		// Update the collision manager
		mCollisions.Update();

		// Remove any entities waiting for destruction
		for (std::vector<Entity*>::iterator it = mEntityList.begin(); it != mEntityList.end(); ++it)
		{
			if ((*it)->CheckDestruction())
			{
				// Destroy entity
				delete (*it);
				// Erase entity pointer and iterate over it
				it = mEntityList.erase(it);
				if (it == mEntityList.end()) { break; }
			}
		}

		if (mEvents.GetMouseL())
		{
			mEntityList.push_back(new Bullet(mContext, tBullet, player));
			mCollisions.AddObject((GameObject*)mEntityList.back());
		}

		// Update every entity
		for (std::vector<Entity*>::iterator it = mEntityList.begin(); it != mEntityList.end(); ++it)
		{
			(*it)->Update(deltaTime);
		}

		// Clear the renderer
		SDL_RenderClear(mContext);
	
		// Render every entity
		for (std::vector<Entity*>::iterator it = mEntityList.begin(); it != mEntityList.end(); ++it)
		{
			(*it)->Render();
		}

		// Present buffer 
		SDL_RenderPresent(mContext);
	}

	SDL_DestroyTexture(tPlayer);
	SDL_DestroyTexture(tEnemy);
	SDL_DestroyTexture(tBullet);
}

GameManager::GameManager()
{
	mWindow = SDL_CreateWindow("Fite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	mContext = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	mInitialised = (mWindow != nullptr && mContext != nullptr);
}

GameManager::~GameManager()
{
	// Free all SDL variables from heap
	SDL_DestroyRenderer(mContext);
	SDL_DestroyWindow(mWindow);
	// Free all remaining entities from heap
	for (std::vector<Entity*>::iterator it = mEntityList.begin(); it != mEntityList.end(); ++it)
	{
		delete (*it);
	}
	mEntityList.clear();
}