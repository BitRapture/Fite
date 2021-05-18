#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "GameObject.h"
#include "Projectiles.h"

class Character : public GameObject
{
// Shared variables
protected:
// Character variables
	// Health (0 <= death)
	int mHealth{ 0 };
	// Basic states
	enum class CharacterState { IDLE, WALKING, ATTACKING, DEAD } mState;


// Shared methods
protected:
	// Check on health, sets state to DEAD if <= 0
	void CheckHealth();

public:
	// Get health of character
	int GetHealth();

	// Constructor
	Character(SDL_Renderer* _ctx, ResourceManager* _resources, SDL_Rect _spriteSize, int _ID, int _maxXFrames, int _maxYFrames, float _objectSize, float _startingX, float _startingY);
	// Destructor
	~Character();
};

#endif