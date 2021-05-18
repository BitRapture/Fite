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

	// scenes 0 = menu, 1 = game
	bool scene = 0;

	// Load first scene
	mScenes[scene]->Load();

	while (mGameLoop)
	{
		// Poll all events (keyboard, window, mouse, etc)
		mGameLoop = !mEvents.Poll();
	
		// Calculate deltaTime (miliseconds)
		timeCurrent = SDL_GetPerformanceCounter();
		deltaTime = (timeCurrent - timeLast) * counterFreq;
		timeLast = timeCurrent;

		// Update the collision manager
		mCollisions.UpdateCollisions();

		// Remove any GameObjects from the GameObjects list waiting for destruction
		for (std::vector<GameObject*>::iterator it = mGameObjects.begin(); it != mGameObjects.end(); ++it)
		{
			if ((*it)->CheckDestruction())
			{
				it = mGameObjects.erase(it);
				if (it == mGameObjects.end()) { break; }
			}
		}

		// Remove any entities waiting for destruction
		for (std::vector<Entity*>::iterator it = mEntityList.begin(); it != mEntityList.end(); ++it)
		{
			if ((*it)->CheckDestruction())
			{
				// Destroy entity
				delete (*it);
				// Remove dangling pointer
				(*it) = nullptr;
				// Erase entity pointer and iterate over it
				it = mEntityList.erase(it);
				if (it == mEntityList.end()) { break; }
			}
		}

		// Update scene
		mScenes[scene]->Update(deltaTime);

		if (mScenes[scene]->Finished())
		{
			mScenes[scene]->UnLoad();
			scene = !scene;
			mScenes[scene]->Load();
		}

		if (mScenes[scene]->Quit())
		{
			mGameLoop = false;
		}
	}
}

GameManager::GameManager()
{
	// Create window and render context
	mWindow = SDL_CreateWindow("Fite", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	mContext = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);

	// Create scenes
	Scenes::Game* sGame = new Scenes::Game(&mCollisions, &mResources, &mEvents, mContext, &mEntityList, &mGameObjects);
	Scenes::Menu* sMenu = new Scenes::Menu(&mCollisions, &mResources, &mEvents, mContext, &mEntityList, &mGameObjects);

	// Add them to scene manager
	mScenes.push_back(sMenu);
	mScenes.push_back(sGame);

	mInitialised = (mWindow != nullptr && mContext != nullptr && mResources.Init(mContext) && sGame != nullptr);
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
	// Clear GameObjects list, since entities deleted all objects from it (just dangling pointers now)
	mGameObjects.clear();
	// Free scenes
	for (std::vector<Scene*>::iterator it = mScenes.begin(); it != mScenes.end(); ++it)
	{
		delete (*it);
	}
	mScenes.clear();
}