#include "Projectiles.h"

void Bullet::Update(double& _deltaTime)
{
	// Check collision stack
	if (mCollisionStack.size() > 0)
	{
		SDL_Log("%i", mCollisionStack.size());
		for (std::vector<GameObject*>::iterator it = mCollisionStack.begin(); it != mCollisionStack.end(); ++it)
		{
			// Skip if the collision is from the shooter
			if ((*it) != mShooter)
			{
				// Destroy self
				DestroyOnCollide();
				break;
			}
		}
	}
	// Update position
	mX += mSpeed * mDirX * (float)_deltaTime;
	mY += mSpeed * mDirY * (float)_deltaTime;
}

void Bullet::Render()
{
	mBaseSprite.RenderSprite(mContext, mX, mY);
}

Bullet::Bullet(SDL_Renderer* _ctx, SDL_Texture* _sprite, GameObject* _shooter)
:
	Projectile(_ctx, _sprite, {0, 0, 64, 64}, 1, 1, 3, _shooter->GetX(), _shooter->GetY(), _shooter)
{
	// Center the sprite
	mBaseSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = -32;
	// Set the damage
	mDamage = 10;
	// Set the speed
	mSpeed = 0.3f;
}