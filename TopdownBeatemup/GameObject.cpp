#include "GameObject.h"

void GameObject::SetDirection(float _angle)
{
	float cos = cosf(_angle), sin = sinf(_angle), tempX = mDirX;
	mDirX = (mDirX * cos) - (mDirY * sin);
	mDirY = (tempX * sin) + (mDirY * cos);
}

void GameObject::SetCardinalDir(int _dir)
{
	switch (_dir)
	{
	// Facing up
	case 0: { mDirX = 0; mDirY = -1; break; }
	// Facing up-right
	case 1: { mDirX = 0.7071067811865476f; mDirY = -0.707106781186547f; break; }
	// Facing right
	case 2: { mDirX = 1; mDirY = 0; break; }
	// Facing down-right
	case 3: { mDirX = 0.7071067811865475f; mDirY = 0.707106781186547f; break; }
	// Facing down
	case 4: { mDirX = 0; mDirY = 1; break; }
	// Facing down-left
	case 5: { mDirX = -0.7071067811865477f; mDirY = 0.7071067811865475f; break; }
	// Facing left
	case 6: { mDirX = -1; mDirY = 0; break; }
	// Facing up-left
	case 7: { mDirX = -0.7071067811865474f; mDirY = -0.7071067811865477f; break; }
	}
}

bool GameObject::CheckCollision(GameObject& _object)
{
	return ((powf(mX - _object.mX, 2) + powf(mY - _object.mY, 2)) <= powf(mSize + _object.mSize, 2));
}

bool GameObject::CheckAABBCollision(GameObject& _object)
{
	SDL_Rect aSize = this->mBaseSprite.GetSpriteSize(), bSize = _object.mBaseSprite.GetSpriteSize();
	float aX = mX + mBaseSprite.mSpriteXOffset, aY = mY + mBaseSprite.mSpriteYOffset,
		bX = _object.mX + _object.mBaseSprite.mSpriteXOffset, bY = _object.mX + _object.mBaseSprite.mSpriteXOffset;
	return (
		aX < bX + (bSize.w + _object.mBaseSprite.mSpriteXOffset) &&
		aY < bY + (bSize.h + _object.mBaseSprite.mSpriteYOffset) &&
		aX + (aSize.w + mBaseSprite.mSpriteXOffset) > bX &&
		aY + (aSize.h + mBaseSprite.mSpriteYOffset) > bY
		);
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