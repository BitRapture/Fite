#include "Scenes.h"

namespace Scenes
{
	void Game::Update(double& _deltaTime)
	{
		// Spawn enemies in
		mEnemySpawnWait -= (float)_deltaTime;
		if (mEnemySpawnWait <= 0)
		{
			mEnemySpawnWait = mEnemySpawnRate;
			CreateGameObject(new Enemy(mContext, mResources, mPlayer->GetX(), 740, mPlayer->GetX(), mPlayer->GetY(), mEnemyHealth, mEnemySpeed), true);
			CreateGameObject(new Enemy(mContext, mResources, mPlayer->GetX() + 250, 740, mPlayer->GetX(), mPlayer->GetY(), mEnemyHealth, mEnemySpeed), true);
			CreateGameObject(new Enemy(mContext, mResources, mPlayer->GetX(), -32, mPlayer->GetX(), mPlayer->GetY(), mEnemyHealth, mEnemySpeed), true);
			CreateGameObject(new Enemy(mContext, mResources, mPlayer->GetX() - 250, -32, mPlayer->GetX(), mPlayer->GetY(), mEnemyHealth, mEnemySpeed), true);
			if (((Player*)(mPlayer))->GetScore() + 20 > mPreviousScore)
			{
				mPreviousScore = ((Player*)(mPlayer))->GetScore();
				mEnemyHealth++;
				mEnemySpeed += 0.015f;
				mEnemySpawnRate -= (mEnemySpawnRate > 500.f ? 10.f : 0);
			}
		}

		// Update every entity
		for (std::vector<Entity*>::iterator it = mEntityList->begin(); it != mEntityList->end(); ++it)
		{
			(*it)->Update(_deltaTime);
		}
		mPlayer->Update(_deltaTime);

		// If health is 0 finish this scene
		if (((Player*)(mPlayer))->GetHealth() <= 0)
		{
			mFinished = true;
		}

		// Create all GameObjects on GameObject creation queues
		for (size_t it = 0; it < mGameObjects->size(); ++it)
		{
			size_t creationSize = (*mGameObjects)[it]->GetCreationQueueSize();
			for (size_t c = 0; c < creationSize; ++c)
			{
				GameObject* newObject = (*mGameObjects)[it]->AccessCreationQueue(c);
				CreateGameObject(newObject, (*mGameObjects)[it]->AccessCreationQueueCollisions(c));
			}
			(*mGameObjects)[it]->ClearCreationQueue();
		}

		// Update the collision manager object listing
		mCollisions->UpdateCollisionList();

		// Clear the renderer
		SDL_SetRenderDrawColor(mContext, 20, 0, 20, 255);
		SDL_RenderClear(mContext);

		// Render every entity
		for (std::vector<Entity*>::iterator it = mEntityList->begin(); it != mEntityList->end(); ++it)
		{
			(*it)->Render();
		}
		mPlayer->Render();

		// Present buffer 
		SDL_RenderPresent(mContext);
	}

	void Game::Load()
	{
		// Instantiate player
		mPlayer = new Player(mContext, mResources, mEvents);
		mGameObjects->push_back(mPlayer);
		mCollisions->AddObject(mPlayer);

		// Play background music
		mResources->PlayMusic(Music::BACKGROUND_MUSIC);
	}

	void Game::UnLoad()
	{
		mCollisions->RemoveCollisions();
		// Destroy instantiated objects
		// Free all remaining entities from heap
		for (std::vector<Entity*>::iterator it = mEntityList->begin(); it != mEntityList->end(); ++it)
		{
			delete (*it);
		}
		delete mPlayer;
		mEntityList->clear();
		// Clear GameObjects list, since entities deleted all objects from it (just dangling pointers now)
		mGameObjects->clear();
		// Stop music
		Mix_PauseMusic();
		// Set finished to false
		mFinished = false;
		// Reset variables
		mPreviousScore = 0;
		mEnemySpawnRate = 5000.f;
		mEnemySpawnWait = 0;
		mEnemyHealth = 3;
		mEnemySpeed = 0.2f;
	}

	Game::Game(CollisionManager* _collisions, ResourceManager* _resources, EventManager* _events, SDL_Renderer* _context,
		std::vector<Entity*>* _entityList, std::vector<GameObject*>* _gameObjectList)
	:
		Scene(_collisions, _resources, _events, _context, _entityList, _gameObjectList)
	{

	}
	Game::~Game()
	{
		UnLoad();
	}



	void Menu::Update(double& _deltaTime)
	{
		// Update buttons
		mButtonPlay->Update(_deltaTime);
		mButtonExit->Update(_deltaTime);

		if (mButtonPlay->ButtonPressed())
		{
			mFinished = true;
		}
		if (mButtonExit->ButtonPressed())
		{
			mQuit = true;
		}

		// Clear the renderer
		SDL_SetRenderDrawColor(mContext, 0, 0, 0, 255);
		SDL_RenderClear(mContext);

		// Render buttons
		mButtonPlay->Render();
		mButtonExit->Render();

		// Render title
		SDL_RenderCopy(mContext, mTitle->mFont, NULL, &(mTitle->mSize));

		// Render instructions
		SDL_RenderCopy(mContext, mIntKeyboard->mFont, NULL, &(mIntKeyboard->mSize));
		SDL_RenderCopy(mContext, mIntMouse->mFont, NULL, &(mIntMouse->mSize));
		SDL_RenderCopy(mContext, mIntGoal->mFont, NULL, &(mIntGoal->mSize));

		// Present buffer 
		SDL_RenderPresent(mContext);
	}

	void Menu::Load()
	{
		// Create buttons and title text
		mButtonPlay = new Button(mContext, mResources, mEvents, 550, 300, 180, 45, "Play Game");
		mButtonExit = new Button(mContext, mResources, mEvents, 550, 400, 180, 45, "Exit Game");
		mTitle = mResources->StringToFont("FITE: THE GAME", Fonts::ARCADE_32, mContext);
		mTitle->mSize.x = 20;
		mTitle->mSize.y = 20;
		// Create instructions
		mIntKeyboard = mResources->StringToFont("WASD or arrow keys to move!", Fonts::ARCADE_16, mContext);
		mIntKeyboard->mSize.x = 20;
		mIntKeyboard->mSize.y = 600;
		mIntMouse = mResources->StringToFont("Left click to shoot, Right click to sprint!", Fonts::ARCADE_16, mContext);
		mIntMouse->mSize.x = 20;
		mIntMouse->mSize.y = 632;
		mIntGoal = mResources->StringToFont("Survive as long as you can!", Fonts::ARCADE_16, mContext);
		mIntGoal->mSize.x = 20;
		mIntGoal->mSize.y = 664;
	}

	void Menu::UnLoad()
	{
		// Free buttons
		delete mButtonPlay;
		delete mButtonExit;
		delete mTitle;
		// Free instructions
		delete mIntKeyboard;
		delete mIntMouse;
		delete mIntGoal;
		// Set finished to false
		mFinished = false;
	}

	Menu::Menu(CollisionManager* _collisions, ResourceManager* _resources, EventManager* _events, SDL_Renderer* _context,
		std::vector<Entity*>* _entityList, std::vector<GameObject*>* _gameObjectList)
		:
		Scene(_collisions, _resources, _events, _context, _entityList, _gameObjectList)
	{

	}
	Menu::~Menu()
	{
		UnLoad();
	}
}