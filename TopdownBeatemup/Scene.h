#ifndef _SCENE_H_
#define _SCENE_H_

#include "EventManager.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "Projectiles.h"
#include "Player.h"
#include "Enemy.h"

class Scene
{
// Shared variables
protected:
	// Pointer to the collision manager
	CollisionManager* mCollisions{ nullptr };
	// Pointer to the resource manager
	ResourceManager* mResources{ nullptr };
	// Pointer to the event manager
	EventManager* mEvents{ nullptr };
	// Pointer to the main renderer
	SDL_Renderer* mContext{ nullptr };
	// Pointer to entity vector
	std::vector<Entity*>* mEntityList{ nullptr };
	// Pointer to gameobject vector
	std::vector<GameObject*>* mGameObjects{ nullptr };

// Scene flags
	// check if scene is finished
	bool mFinished{ false };
	// Check if scene wants to close the program
	bool mQuit{ false };

// Internal methods
protected:
	// Create GameObject
	// Adds gameobject into the entity pipeline
	void CreateGameObject(GameObject* _object, bool _isSelfCollidable = false);

	// Create Entity
	// Adds entity into the entity pipeline
	void CreateEntity(Entity* _entity);

// Public methods
public:
	// Virtual update method
	virtual void Update(double& _deltaTime) = 0;
	
	// Virtual load method
	virtual void Load() = 0;

	// Virtual unload method
	virtual void UnLoad() = 0;

	// Check if scene is finished updating
	bool Finished();

	// Check if scene wants to end the application
	bool Quit();

	// Constructor
	Scene(CollisionManager* _collisions, ResourceManager* _resources, EventManager* _events, SDL_Renderer* _context, 
		std::vector<Entity*>* _entityList, std::vector<GameObject*>* _gameObjectList);
};

#endif