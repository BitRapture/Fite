#include "CollisionManager.h"

void CollisionManager::AddObject(GameObject* _object, bool _selfCollidable)
{
	// Check if GameObject is collidable
	if (_object->mCollidable)
	{
		// Get the identifiable tag so other objects know what this is
		int tag = _object->GetID();
		// Add the object to the collidable objects stack
		mObjects.push_back(TaggedObject{ _object, (_selfCollidable ? -1 : tag) });
	}
}

void CollisionManager::UpdateCollisions()
{
	if (mObjects.size() < 2) return;

	// Very basic collision checking using nested for loops
	// Performance gets bad the more objects added
	// todo: Add spatial partitioning or some other collision algo
	for (std::vector<TaggedObject>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		// Clear the collision stack
		(*it).mObject->mCollisionStack.clear();
		for (std::vector<TaggedObject>::iterator it2 = mObjects.begin(); it2 != mObjects.end(); ++it2)
		{
			// Skip if GameObject is checking itself
			// Skip if GameObject tag is the same
			if ((*it).mObject != (*it2).mObject && (*it).mTag != (*it2).mObject->mID)
			{
				// Check for a circle-circle collision
				if ((*it).mObject->PredictCollision((*it2).mObject, (*it).mObject->mX, (*it).mObject->mY, (*it).mObject->mSearchSize))
				{
					// Add the collision to the GameObjects collision stack
					(*it).mObject->mCollisionStack.push_back((*it2).mObject);
				}
			}
		}
	}
}

void CollisionManager::UpdateCollisionList()
{
	// Remove any noncollidable objects
	for (std::vector<TaggedObject>::iterator it = mObjects.begin(); it != mObjects.end(); ++it)
	{
		if ((*it).mObject == nullptr || !(*it).mObject->mCollidable || (*it).mObject->CheckDestruction())
		{
			it = mObjects.erase(it);
			if (it == mObjects.end()) { break; }
		}
	}
}

// TODO make an ID system
// -> A class that takes a GameObject* and an int
//		-> Allows for specific collisions so objects of similar type dont collide