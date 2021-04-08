#ifndef _GAMEOBJECT_MANAGER_H_
#define _GAMEOBJECT_MANAGER_H_

#include <vector>
#include "GameObject.h"

class GameObjectManager
{
// Hidden variables
private:
	// Cell dimensions
	float mCellWidth{ 0 }, mCellHeight{ 0 };
	// Spatial partitioning grid
	std::vector<GameObject*>* mGrid{ nullptr };
	// Grid size
	int mGridSize{ 0 };

// GameObjectManager flags
	// Grid initialised
	bool mGridInitialised{ false };

// Public methods
public:
	// Check collisions for GameObject
	void CheckCollisions(GameObject* _object);

	// Add GameObject ref to grid
	void AddObject(GameObject* _object, int _index);
	// Remove GameObject ref from grid
	void RemoveObject(GameObject* _object, int _index);

	// Get cell dimensions
	float GetCellWidth();
	float GetCellHeight();

	// Delete and clean up manager
	void Delete();

	// Check manager is initialised
	bool IsInit();

	// Constructor
	GameObjectManager(int _gameSpaceW, int _gameSpaceH, int _cellAmount);
	// Destructor
	~GameObjectManager();
};

#endif