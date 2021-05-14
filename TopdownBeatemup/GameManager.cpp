#include "GameManager.h"

void GameManager::CreateGameObject(GameObject* _object, bool _isSelfCollidable)
{
	mGameObjects.push_back(_object);
	mEntityList.push_back(_object);
	mCollisions.AddObject(_object, _isSelfCollidable);
}

void GameManager::CreateEntity(Entity* _entity)
{
	mEntityList.push_back(_entity);
}

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

	SDL_Surface* sPlayer = IMG_Load("Media/FiteCharacterSheet.png");
	SDL_Surface* sEnemy = IMG_Load("Media/FiteEnemy.png");
	SDL_Surface* sBullet = IMG_Load("Media/ProjectileBullet.png");
	SDL_Texture* tPlayer = SDL_CreateTextureFromSurface(mContext, sPlayer);
	SDL_Texture* tEnemy = SDL_CreateTextureFromSurface(mContext, sEnemy);
	SDL_Texture* tBullet = SDL_CreateTextureFromSurface(mContext, sBullet);

	SDL_FreeSurface(sPlayer);
	SDL_FreeSurface(sEnemy);
	SDL_FreeSurface(sBullet);

	GameObject* player = new Player(mContext, &mResources, &mEvents);

	CreateGameObject(player);

	CreateGameObject(new Enemy(mContext, &mResources, (Player*)player, 300, 300), true);
	CreateGameObject(new Enemy(mContext, &mResources, (Player*)player, 128, 128), true);
	CreateGameObject(new Enemy(mContext, &mResources, (Player*)player, 700, 700), true);
	CreateGameObject(new Enemy(mContext, &mResources, (Player*)player, 500, 200), true);

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

		// Create all GameObjects on GameObject creation queues
		for (size_t it = 0; it < mGameObjects.size(); ++it)
		{
			size_t creationSize = mGameObjects[it]->GetCreationQueueSize();
			for (size_t c = 0; c < creationSize; ++c)
			{
				GameObject* newObject = mGameObjects[it]->AccessCreationQueue(c);
				CreateGameObject(newObject, mGameObjects[it]->AccessCreationQueueCollisions(c));
			}
			mGameObjects[it]->ClearCreationQueue();
		}

		// Update every entity
		for (std::vector<Entity*>::iterator it = mEntityList.begin(); it != mEntityList.end(); ++it)
		{
			(*it)->Update(deltaTime);
		}

		// Update the collision manager object listing
		mCollisions.UpdateCollisionList();

		// Clear the renderer
		SDL_SetRenderDrawColor(mContext, 0, 0, 0, 255);
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

	mInitialised = (mWindow != nullptr && mContext != nullptr && mResources.Init(mContext));
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
}