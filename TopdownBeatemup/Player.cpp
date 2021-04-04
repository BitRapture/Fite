#include "Player.h"

void Player::Update(double& _deltaTime)
{
	AnimateSprite(_deltaTime);
	mX += mEvents->GetDeltaX() * 0.2f;
	mY += mEvents->GetDeltaY() * 0.2f;
}

void Player::Render()
{
	RenderSprite();
}

Player::Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite, EventManager* _eventManager)
:
	Character(_ctx, _playerSprite, {0, 0, 64, 64}, 3, 0, 32),
	mEvents{ _eventManager }
{
	mSpriteSpeed = 20.f;
	mSpriteAngle = 135.f;
	mSpriteXOffset = 100;
	mSpriteYOffset = 70;
}

Player::~Player()
{

}