#include "Character.h"

void Character::CheckHealth()
{
	if (mHealth <= 0)
	{
		mState = CharacterState::DEAD;
	}
}

Character::Character(SDL_Renderer* _ctx, ResourceManager* _resources, SDL_Rect _spriteSize, int _ID, int _maxXFrames, int _maxYFrames, float _objectSize, float _startingX, float _startingY)
:
	GameObject(_ctx, _resources, _spriteSize, _ID, _maxXFrames, _maxYFrames, _objectSize, _startingX, _startingY),
	mState{ CharacterState::IDLE }
{

}

Character::~Character()
{

}