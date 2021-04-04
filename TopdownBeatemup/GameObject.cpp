#include "GameObject.h"

void GameObject::RenderSegment(SDL_Rect& _segment)
{
	SDL_Rect dest{ (int)(mX + mSpriteXOffset), (int)(mY + mSpriteYOffset), _segment.w, _segment.h };
	SDL_RenderCopyEx(mContext, mSprite, &_segment, &dest, mSpriteAngle, NULL, SDL_FLIP_NONE);
}

void GameObject::AnimateSprite(double& _deltaTime)
{
	mSpriteTime += (float)_deltaTime;
	if (mSpriteTime >= mSpriteSpeed)
	{
		mSpriteTime -= mSpriteSpeed;
		if (++mSpriteIX >= mSpriteIXM)
		{
			mSpriteIX = 0;
		}
	}
}

void GameObject::RenderSprite()
{
	SDL_Rect frame{ mSpriteSize.x + (mSpriteIX * mSpriteSize.w), mSpriteSize.y + (mSpriteIY * mSpriteSize.h),
		mSpriteSize.w, mSpriteSize.h
	};
	RenderSegment(frame);
}

void GameObject::ResetSpriteTime()
{
	mSpriteTime = 0;
}

bool GameObject::SetSpriteIndex(int _x, int _y)
{
	if (_x < 0 || _x >= mSpriteIXM || _y < 0 || _y >= mSpriteIYM) return false;
	mSpriteIX = _x;
	mSpriteIY = _y;
	return true;
}

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

int GameObject::GetSpriteXIndex()
{
	return mSpriteIX;
}

int GameObject::GetSpriteYIndex()
{
	return mSpriteIY;
}

SDL_Rect GameObject::GetSpriteSize()
{
	return mSpriteSize;
}

bool GameObject::CheckCollision(GameObject& _object)
{
	return ((powf(mX - _object.mX, 2) + powf(mY - _object.mY, 2)) <= powf(mSize + _object.mSize, 2));
}

bool GameObject::CheckAABBCollision(GameObject& _object)
{
	SDL_Rect aSize = this->GetSpriteSize(), bSize = _object.GetSpriteSize();
	float aX = mX + mSpriteXOffset, aY = mY + mSpriteYOffset,
		bX = _object.mX + _object.mSpriteXOffset, bY = _object.mX + _object.mSpriteXOffset;
	return (
		aX < bX + (bSize.w + _object.mSpriteXOffset) &&
		aY < bY + (bSize.h + _object.mSpriteYOffset) &&
		aX + (aSize.w + mSpriteXOffset) > bX &&
		aY + (aSize.h + mSpriteYOffset) > bY
		);
}

GameObject::GameObject(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect& _spriteSize, int& _maxXFrames, int& _maxYFrames, float& _objectSize)
:
	mContext{ _ctx }, mSprite{ _sprite }, mSpriteSize{ _spriteSize },
	mSpriteIXM{ _maxXFrames }, mSpriteIYM{ _maxYFrames },
	mSize{ _objectSize }
{

}

GameObject::~GameObject()
{

}