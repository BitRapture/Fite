#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Entity.h"
#include "GameObjects.h"
#include "ResourceManager.h"

class GameObject : public Entity
{
// Let the collision manager view private variables
friend class CollisionManager;

// Hidden variables
private:
	// Related to object creation
	std::vector<GameObject*> mCreationQueue;
	// Array of bools to check if new object at index is collidable with itself
	std::vector<bool> mCreationCollidable;

// Shared variables
protected:
// Sprite class
	// Base object sprite
	Sprite mBaseSprite;

// Generic GameObject variables
	// GameObject size (circle radius)
	float mSize{ 0 };
	// GameObject collision search size (circle radius)
	float mSearchSize{ 0 };
	// GameObject direction (unit vector) 
	// (pointing right by default)
	float mDirX{ 1 }, mDirY{ 0 };
	// GameObject generic ID, used for other GameObjects to identify its
	// specific extended class
	int mID{ 0 };

	// GameObject collision stack
	// Allows *this to handle other GameObject collisions
	std::vector<GameObject*> mCollisionStack;

	// Link to resource manager for media access
	ResourceManager* mResources;

// GameObject flags
	// Does this object collide with other objects
	bool mCollidable{ false };

// Shared methods
protected:
	// Set direction (radians)
	void SetDirection(float _angle);

	// Debug draw hitboxes
	void DrawHitboxes();

// Public methods
public:
	// Predict Circle-Circle collision, used to precalculate movement, attacks, etc
	bool PredictCollision(GameObject* _object, float& _x, float& _y, float& _searchRadius);

	// Get direction X
	float GetDirX();
	// Get direction Y
	float GetDirY();

	// Get ID
	int GetID();

	// Access creation queue
	GameObject* AccessCreationQueue(size_t _index);
	// Access creation collisions
	bool AccessCreationQueueCollisions(size_t index);
	// Check size of creation queue
	size_t GetCreationQueueSize();
	// Add new object to creation queue
	void CreateObject(GameObject* _object, bool _selfCollidable = false);
	// Clear creation queue
	void ClearCreationQueue();

public:
	// Constructor
	GameObject(SDL_Renderer* _ctx, ResourceManager* _resources, SDL_Rect& _spriteSize, int& _ID, int& _maxXFrames, int& _maxYFrames, float& _objectSize, float& _startingX, float& _startingY);
	// Destructor
	~GameObject();

};


// todo:
// Add camera pointer
//		-> Create camera class
// Let mX mY get offset by camera pos
// Add mCollided pointer
//		-> Lets objects sort out collisions with one another

#endif