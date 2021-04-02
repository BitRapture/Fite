#include "Player.h"

void Player::Update(double& _deltaTime)
{
	mSpriteAngle++;
	mX = 128;
	mY = 128;
}

void Player::Render()
{
	RenderSprite();
}

Player::Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite)
:
	Character(_ctx, _playerSprite, {0, 0, 64, 64}, 1, 0, 32)
{

}

Player::~Player()
{

}