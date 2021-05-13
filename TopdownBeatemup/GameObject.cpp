#include "GameObject.h"

void GameObject::SetDirection(float _angle)
{
	float cos = cosf(_angle), sin = sinf(_angle), tempX = mDirX;
	mDirX = (mDirX * cos) - (mDirY * sin);
	mDirY = (tempX * sin) + (mDirY * cos);
}

bool GameObject::PredictCollision(GameObject* _object, float& _x, float& _y, float& _searchRadius)
{
	return ((powf(_x - _object->mX, 2) + powf(_y - _object->mY, 2)) <= powf(_searchRadius + _object->mSize, 2));
}

float GameObject::GetDirX()
{
	return mDirX;
}

float GameObject::GetDirY()
{
	return mDirY;
}

GameObject::GameObject(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect& _spriteSize, int& _maxXFrames, int& _maxYFrames, float& _objectSize, float& _startingX, float& _startingY)
	:
	Entity(_ctx, _startingX, _startingY),
	mBaseSprite(_sprite, _spriteSize, _maxXFrames, _maxYFrames),
	mSize{ _objectSize }
{

}

GameObject::~GameObject()
{

}