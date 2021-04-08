#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "Entity.h"
#include "GameObjectManager.h"

class GameObject : public Entity
{
// Share private variables with the object manager
friend class GameObjectManager;

// Hidden variables
private:
	// Pointer to the object managing system
	GameObjectManager* mObjectManager{ nullptr };
	// GameObjectManager grid indices 
	std::vector<int> mOMIndices;

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
	std::vector<GameObject*> mCollisions;

// Shared methods
protected:
	// Set direction (radians)
	void SetDirection(float _angle);
	// Set cardinal direction (0 to 7) (clockwise)
	// Precalculated unit vector directions
	void SetCardinalDir(int _dir);

// Public methods
public:
	// Circle-Circle collision (main form of object collision)
	bool CheckCollision(GameObject* _object);
	// AABB collision, based off sprite size
	bool CheckAABBCollision(GameObject* _object);

public:
	// Constructors
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
// Move mContext to Entity.h
//		-> All entities should have a pointer to the renderer
//		-> overide the default entity ctor

#endif