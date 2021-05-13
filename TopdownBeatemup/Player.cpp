#include "Player.h"

void Player::Update(double& _deltaTime)
{
	int dX = mEvents->GetDeltaX(), dY = mEvents->GetDeltaY();
	
	if (dX != 0 || dY != 0)
	{
		mLegsSprite.AnimateSprite(_deltaTime);
	}
	else
	{
		mLegsSprite.ResetSpriteTime();
		mLegsSprite.SetSpriteXIndex(0);
	}

	mX += dX * 0.2f * (float)_deltaTime;
	mY += dY * 0.2f * (float)_deltaTime;

	mDirX = mX - mEvents->GetMouseX();
	mDirY = mY - mEvents->GetMouseY();

	float rad = atan2f(mDirY, mDirX);
	float normal = sqrtf(powf(mDirX, 2) + powf(mDirY, 2));

	mDirX /= normal;
	mDirY /= normal;

	mBaseSprite.SetSpriteAngle((rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f));
	mLegsSprite.SetSpriteAngle(mBaseSprite.GetSpriteAngle());
}


void Player::Render()
{
	mLegsSprite.RenderSprite(mContext, mX, mY);
	mBaseSprite.RenderSprite(mContext, mX, mY);
}

Player::Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite, EventManager* _eventManager)
	:
	Character(_ctx, _playerSprite, { 0, 0, 64, 64 }, 1, 1, 16, 320, 240),
	mLegsSprite(_playerSprite, { 0, 0, 64, 64 }, 17, 2),
	mEvents{ _eventManager }
{
	// Set the sprite speed of all sprite objects
	mBaseSprite.mSpriteSpeed = mLegsSprite.mSpriteSpeed = 50.f;
	// Set the offset of all objects to the center
	mBaseSprite.mSpriteXOffset = mLegsSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = mLegsSprite.mSpriteYOffset = -32;
	// Set the y-index to 1 so the legs animation can be used
	mLegsSprite.SetSpriteYIndex(1);
	mX = 320;
	mY = 240;
	mCollidable = false;
}

Player::~Player()
{

}