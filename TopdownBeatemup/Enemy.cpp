#include "Enemy.h"

void Enemy::Update(double& _deltaTime)
{
	if (!mFocus->CheckCollision(*this)) mY += 0.5f * _deltaTime;
	if (mY > 784) mY = -64;

	float rad = atan2f(mY - mFocus->GetY(), mX - mFocus->GetX());
	mBaseSprite.SetSpriteAngle((rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f));
}

void Enemy::Render()
{
	mBaseSprite.RenderSprite(mContext, mX, mY);
}

Enemy::Enemy(SDL_Renderer* _ctx, SDL_Texture* _enemySprite, Player* _player)
:
	Character(_ctx, _enemySprite, {0, 0, 64, 64}, 1, 1, 20),
	mFocus{ _player }
{
	mBaseSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = -32;
	mX = 400;
	mY = 400;
}