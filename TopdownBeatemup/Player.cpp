#include "Player.h"

void Player::Update(double& _deltaTime)
{
	mX += mEvents->GetDeltaX() * 0.2f * (float)_deltaTime;
	mY += mEvents->GetDeltaY() * 0.2f * (float)_deltaTime;

	float rad = atan2f(mY - mEvents->GetMouseY(), mX - mEvents->GetMouseX());

	mBaseSprite.SetSpriteAngle((rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f));
}


void Player::Render()
{
	mBaseSprite.RenderSprite(mContext, mX, mY);
}

Player::Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite, EventManager* _eventManager)
:
	Character(_ctx, _playerSprite, {0, 0, 64, 64}, 1, 0, 16),
	mEvents{ _eventManager }
{
	mBaseSprite.mSpriteSpeed = 20.f;
	mBaseSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = -32;
	mX = 32;
	mY = 32;
}

Player::~Player()
{

}