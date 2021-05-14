#include "Enemy.h"

void Enemy::Update(double& _deltaTime)
{
	// Check collision stack
	if (mCollisionStack.size() > 0)
	{
		for (std::vector<GameObject*>::iterator it = mCollisionStack.begin(); it != mCollisionStack.end(); ++it)
		{
			switch (GameObjects::ID((*it)->GetID()))
			{
			case AllObjects::PROJECTILE:
			{
				// Deduct health if hit with a projectile
				if (PredictCollision((*it), mX, mY, mSize))
				{
					mHealth -= ((Projectile*)(*it))->InflictDamage();
					mX += ((Projectile*)(*it))->GetDirX() * (float)_deltaTime * 0.5f;
					mY += ((Projectile*)(*it))->GetDirY() * (float)_deltaTime * 0.5f;
				}
				break;
			}
			case AllObjects::PLAYER:
			{
				mCollidable = false;
				mDestroy = true;
				break;
			}
			case AllObjects::ENEMY:
			{
				// Make sure that enemies move themselves so they dont group into one being
				mX += ((Enemy*)(*it))->GetDirX() * (float)_deltaTime * 0.15f;
				mY += ((Enemy*)(*it))->GetDirY() * (float)_deltaTime * 0.15f;
				((Enemy*)(*it))->mX += mDirX * -(float)_deltaTime * 0.15f;
				((Enemy*)(*it))->mY += mDirY * -(float)_deltaTime * 0.15f;
				// Remove this collision from the other enemy so these instructions arent repeated
				for (std::vector<GameObject*>::iterator it2 = ((Enemy*)(*it))->mCollisionStack.begin();
					it2 != ((Enemy*)(*it))->mCollisionStack.end(); ++it2)
				{
					if ((*it2) == this)
					{
						((Enemy*)(*it))->mCollisionStack.erase(it2);
						break;
					}
				}
			}
			}
		}
	}

	if (mHealth <= 0)
	{
		mCollidable = false;
		mDestroy = true;
	}

	mDirX = mX - mFocus->GetX();
	mDirY = mY - mFocus->GetY();

	float rad = atan2f(mDirY, mDirX);
	float normal = sqrtf(powf(mDirX, 2) + powf(mDirY, 2));
	mBaseSprite.SetSpriteAngle((rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f));

	mDirX /= normal;
	mDirY /= normal;

	mX += -mDirX * (float)_deltaTime * 0.1f;
	mY += -mDirY * (float)_deltaTime * 0.1f;
}

void Enemy::Render()
{
	mBaseSprite.RenderSprite(mContext, mX, mY);
}

Enemy::Enemy(SDL_Renderer* _ctx, ResourceManager* _resources, Player* _player, float _startingX, float _startingY)
:
	Character(_ctx, _resources, {0, 0, 64, 64}, GameObjects::Tag(AllObjects::ENEMY), 1, 1, 16, _startingX, _startingY),
	mFocus{ _player }
{
	mBaseSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = -32;
	mX = _startingX;
	mY = _startingY;
	mCollidable = true;
	mHealth = 10;
	mSearchSize = mSize * 2;
}