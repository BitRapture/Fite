#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "GameObject.h"

class Character : public GameObject
{
// Hidden variables
private:
// Character variables
	// Health (0 <= death)
	int mHealth{ 0 };
	// Basic states
	enum class CharacterState { IDLE, WALKING, ATTACKING, DYING, DEAD } mState;


// Shared methods
protected:


public:
	// Constructor
	Character(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames, float _objectSize);
	// Destructor
	~Character();
};

#endif