#include "Player.h"

void Player::Update(double& _deltaTime)
{
	AnimateSprite(_deltaTime);
}

void Player::Render()
{
	RenderSprite();
}

Player::Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite)
:
	Character(_ctx, _playerSprite, {0, 0, 64, 64}, 3, 0, 32)
{
	mSpriteSpeed = 50.f;
	mSpriteAngle = 90.f;
	mSpriteXOffset = 100;
	mSpriteYOffset = 70;
}

Player::~Player()
{

}