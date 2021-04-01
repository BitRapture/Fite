#include "GameObject.h"

void GameObject::RenderSegment(SDL_Rect& _segment)
{
	SDL_Rect dest{ mX, mY, _segment.w, _segment.h };
	SDL_RenderCopyEx(mContext, mSprite, &_segment, &dest, mSpriteAngle, NULL, SDL_FLIP_NONE);
}

void GameObject::AnimateSprite(double& _deltaTime)
{
	mSpriteTime += _deltaTime;
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

bool GameObject::SetSpriteIndex(int _x, int _y)
{
	if (_x < 0 || _x >= mSpriteIXM || _y < 0 || _y >= mSpriteIYM) return false;
	mSpriteIX = _x;
	mSpriteIY = _y;
	return true;
}

int GameObject::GetSpriteXIndex()
{
	return mSpriteIX;
}

int GameObject::GetSpriteYIndex()
{
	return mSpriteIY;
}

GameObject::GameObject(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames)
:
	mContext{ _ctx }, mSprite{ _sprite }, mSpriteSize{ _spriteSize },
	mSpriteIXM{ _maxXFrames }, mSpriteIYM{ _maxYFrames }
{

}

GameObject::~GameObject()
{

}