#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Entity.h"

class GameObject : public Entity
{
// Let the collision manager view private variables
friend class CollisionManager;

// Shared variables
protected:
// Sprite class
	// Base object sprite
	Sprite mBaseSprite;

// Generic GameObject variables
	// GameObject size (circle radius)
	float mSize{ 0 };
	// GameObject direction (unit vector) 
	// (pointing right by default)
	float mDirX{ 1 }, mDirY{ 0 };

	// GameObject collision stack
	// Allows *this to handle other GameObject collisions
	std::vector<GameObject*> mCollisionStack;

// GameObject flags
	// Does this object collide with other objects
	bool mCollidable{ false };

// Shared methods
protected:
	// Set direction (radians)
	void SetDirection(float _angle);

// Public methods
public:
	// Predict Circle-Circle collision, used to precalculate movement, attacks, etc
	bool PredictCollision(GameObject* _object, float& _x, float& _y, float& _searchRadius);

	// Get direction X
	float GetDirX();
	// Get direction Y
	float GetDirY();

public:
	// Constructor
	GameObject(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect& _spriteSize, int& _maxXFrames, int& _maxYFrames, float& _objectSize, float& _startingX, float& _startingY);
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