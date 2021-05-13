#include "Entity.h"

float Entity::GetX()
{
	return mX;
}

float Entity::GetY()
{
	return mY;
}

bool Entity::CheckDestruction()
{
	return mDestroy;
}

Entity::Entity(SDL_Renderer* _ctx, float& _startingX, float& _startingY)
:
	mContext{ _ctx },
	mX{ _startingX }, mY{ _startingY }
{

}