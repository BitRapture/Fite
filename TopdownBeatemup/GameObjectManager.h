#ifndef _GAMEOBJECT_MANAGER_H_
#define _GAMEOBJECT_MANAGER_H_

#include <vector>
#include "GameObject.h"

class GameObjectManager
{
// Hidden variables
private:
	// List of all objects 
	std::vector<GameObject*> mObjects;

// Public methods
public:
	// Add object to the system
	bool AddObject(GameObject* _object);

};

#endif