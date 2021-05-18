#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include <vector>
#include "GameObject.h"

struct TaggedObject
{
	GameObject* mObject{ nullptr };
	int mTag{ 0 };
};

class CollisionManager
{
// Hidden variables
private:
	// References to instantiated gameobjects
	std::vector<TaggedObject> mObjects;

// Public methods
public:
	// Add a GameObject to the system
	void AddObject(GameObject* _object, bool _selfCollidable = false);

	// Update method (check for collisions)
	void UpdateCollisions();

	// Update method (remove destroyed objects)
	void UpdateCollisionList();

	// Remove all collisions
	void RemoveCollisions();

};

#endif