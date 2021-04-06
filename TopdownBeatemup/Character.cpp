#include "Character.h"

Character::Character(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames, float _objectSize, float _startingX, float _startingY)
:
	GameObject(_ctx, _sprite, _spriteSize, _maxXFrames, _maxYFrames, _objectSize, _startingX, _startingY),
	mState{ CharacterState::IDLE }
{

}

Character::~Character()
{

}