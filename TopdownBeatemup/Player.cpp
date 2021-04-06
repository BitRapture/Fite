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

	float rad = atan2f(mY - mEvents->GetMouseY(), mX - mEvents->GetMouseX());

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
	Character(_ctx, _playerSprite, { 0, 0, 64, 64 }, 1, 1, 16),
	mLegsSprite(_playerSprite, { 0, 0, 64, 64 }, 17, 2),
	mEvents{ _eventManager }
{
	mBaseSprite.mSpriteSpeed = mLegsSprite.mSpriteSpeed = 50.f;
	mBaseSprite.mSpriteXOffset = mLegsSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = mLegsSprite.mSpriteYOffset = -32;
	mLegsSprite.SetSpriteYIndex(1);
	mX = 320;
	mY = 240;
}

Player::~Player()
{

}