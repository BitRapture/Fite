#include "Sprite.h"

void Sprite::RenderSegment(SDL_Renderer* _ctx, SDL_Rect& _segment, float& _camX, float& _camY)
{
	SDL_Rect dest{ (int)(_camX + mSpriteXOffset), (int)(_camY + mSpriteYOffset), _segment.w, _segment.h };
	SDL_RenderCopyEx(_ctx, mSheet, &_segment, &dest, mSpriteAngle, NULL, SDL_FLIP_NONE);
}

void Sprite::AnimateSprite(double& _deltaTime)
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

void Sprite::RenderSprite(SDL_Renderer* _ctx, float& _camX, float& _camY)
{
	SDL_Rect frame{ mSpriteSize.x + (mSpriteIX * mSpriteSize.w), mSpriteSize.y + (mSpriteIY * mSpriteSize.h),
		mSpriteSize.w, mSpriteSize.h
	};
	RenderSegment(_ctx, frame, _camX, _camY);
}

void Sprite::ResetSpriteTime()
{
	mSpriteTime = 0;
}

bool Sprite::SetSpriteXIndex(int _x)
{
	if (_x < 0 || _x >= mSpriteIXM) return false;
	mSpriteIX = _x;
	return true;
}

bool Sprite::SetSpriteYIndex(int _y)
{
	if (_y < 0 || _y >= mSpriteIYM) return false;
	mSpriteIY = _y;
	return true;
}

int Sprite::GetSpriteXIndex()
{
	return mSpriteIX;
}

int Sprite::GetSpriteYIndex()
{
	return mSpriteIY;
}

void Sprite::SetSpriteAngle(float _angle)
{
	mSpriteAngle = _angle;
}

float Sprite::GetSpriteAngle()
{
	return mSpriteAngle;
}

SDL_Rect Sprite::GetSpriteSize()
{
	return mSpriteSize;
}

Sprite::Sprite(SDL_Texture* _spriteSheet, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames)
:
	mSheet{ _spriteSheet }, mSpriteSize{ _spriteSize },
	mSpriteIXM{ _maxXFrames }, mSpriteIYM{ _maxYFrames }
{

}