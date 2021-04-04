#include "Player.h"

void Player::Update(double& _deltaTime)
{
	mX += mEvents->GetDeltaX() * 0.2f;
	mY += mEvents->GetDeltaY() * 0.2f;

	float rad = atan2f(mY - mEvents->GetMouseY(), mX - mEvents->GetMouseX());

	mSpriteAngle = (rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f);
}

void Player::Render()
{
	RenderSprite();
}

Player::Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite, EventManager* _eventManager)
:
	Character(_ctx, _playerSprite, {0, 0, 64, 64}, 1, 0, 16),
	mEvents{ _eventManager }
{
	mSpriteSpeed = 20.f;
	mSpriteXOffset = -32;
	mSpriteYOffset = -32;
	mX = 64;
	mY = 64;
}

Player::~Player()
{

}