#ifndef _SCENES_H_
#define _SCENES_H_

#include "Scene.h"
#include "Button.h"

namespace Scenes
{
	// The main game, where the main game updates happen
	class Game : public Scene
	{
	// Hidden variables
	private:
		// Previous player score for comparison
		int mPreviousScore{ 0 };
		// Spawn enemies on an interval
		float mEnemySpawnRate{ 5000.f };
		float mEnemySpawnWait{ 0 };
		// Enemies get faster and stronger as time goes on
		int mEnemyHealth{ 3 };
		float mEnemySpeed{ 0.2f };

		// Save player as seperate entity
		GameObject* mPlayer{ nullptr };

	// Public methods
	public:
		// Override update method
		void Update(double& _deltaTime) override;
		// Override load method
		void Load() override;
		// Override unload method
		void UnLoad() override;

		// Constructor
		Game(CollisionManager* _collisions, ResourceManager* _resources, EventManager* _events, SDL_Renderer* _context,
			std::vector<Entity*>* _entityList, std::vector<GameObject*>* _gameObjectList);
		// Destructor
		~Game();
	};

	class Menu : public Scene
	{
	// Hidden variables
	private:
		// Buttons for the menu
		Button* mButtonPlay{ nullptr };
		Button* mButtonExit{ nullptr };

		// Title for the game
		FontText* mTitle{ nullptr };
		// Instructions
		FontText* mIntKeyboard, * mIntMouse, * mIntGoal;

	// Public methods
	public:
		// Override update method
		void Update(double& _deltaTime) override;
		// Override load method
		void Load() override;
		// Override unload method
		void UnLoad() override;

		// Constructor
		Menu(CollisionManager* _collisions, ResourceManager* _resources, EventManager* _events, SDL_Renderer* _context,
			std::vector<Entity*>* _entityList, std::vector<GameObject*>* _gameObjectList);
		// Destructor
		~Menu();
	};
}

#endif