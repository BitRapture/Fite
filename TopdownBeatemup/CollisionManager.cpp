#include "CollisionManager.h"

void CollisionManager::AddObject(GameObject* _object)
{
	// Check if GameObject is collidable
	if (_object->mCollidable)
	{
		// Add the object to the collidable objects stack
		mObjects.push_back(_object);
	}
}

void CollisionManager::Update()
{
	// Remove any noncollidable objects
	for (std::vector<GameObject*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		if (!(*it)->mCollidable)
		{
			it = mObjects.erase(it);
			if (it == mObjects.end()) { break; }
		}
	}

	// Very basic collision checking using nested for loops
	// Performance gets bad the more objects added
	// todo: Add spatial partitioning or some other collision algo
	for (std::vector<GameObject*>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		// Clear the collision stack
		(*it)->mCollisionStack.clear();
		for (std::vector<GameObject*>::iterator it2 = mObjects.begin(); it2 != mObjects.end(); ++it2)
		{
			// Skip if GameObject is checking itself
			if (it != it2)
			{
				// Check for a circle-circle collision
				if ((*it)->PredictCollision((*it2), (*it)->mX, (*it)->mY, (*it)->mSize))
				{
					// Add the collision to the GameObjects collision stack
					(*it)->mCollisionStack.push_back((*it2));
				}
			}
		}
	}
}


// TODO make an ID system
// -> A class that takes a GameObject* and an int
//		-> Allows for specific collisions so objects of similar type dont collide