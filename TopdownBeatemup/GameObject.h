#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <SDL.h>
#include "Sprite.h"
#include "Entity.h"

class GameObject : public Entity
{
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

// SDL variables
	// Pointer to main renderer
	SDL_Renderer* mContext{ nullptr };

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
	bool CheckCollision(GameObject& _object);
	// AABB collision, based off sprite size
	bool CheckAABBCollision(GameObject& _object);

public:
	// Constructors
	GameObject(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect& _spriteSize, int& _maxXFrames, int& _maxYFrames, float& _objectSize);
	// Destructor
	~GameObject();

};


// todo:
// Add camera pointer
//		-> Create camera class
// Let mX mY get offset by camera pos
// Separate sprite methods/members to a sprite class
//		-> Allows for additional sprites to be used

#endif