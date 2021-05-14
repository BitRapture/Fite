#include "Projectiles.h"

void Bullet::Update(double& _deltaTime)
{
	CalculateFallOff(_deltaTime);
	// Check collision stack
	if (mCollisionStack.size() > 0)
	{
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

Bullet::Bullet(SDL_Renderer* _ctx, ResourceManager* _resources, GameObject* _shooter, float _startingX, float _startingY)
:
	Projectile(_ctx, _resources, {0, 0, 64, 64}, GameObjects::Tag(AllObjects::PROJECTILE), 1, 1, 8, _startingX, _startingY, _shooter)
{
	// Center the sprite
	mBaseSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = -32;
	// Set the damage
	mDamage = 1;
	// Set the speed
	mSpeed = 1.5f;
	// Set the bullet fall-off
	mFallOff = 500;
}