#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include <vector>
#include "GameObject.h"

class CollisionManager
{
// Hidden variables
private:
	// References to instantiated gameobjects
	std::vector<GameObject*> mObjects;

// Public methods
public:
	// Add a GameObject to the system
	void AddObject(GameObject* _object);

	// Update method (check for collisions)
	void Update();

};

#endif