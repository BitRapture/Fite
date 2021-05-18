#include "Enemy.h"

void Enemy::Update(double& _deltaTime)
{
	// Check collision stack
	if (mCollisionStack.size() > 0 && mState != CharacterState::DEAD)
	{
		for (std::vector<GameObject*>::iterator it = mCollisionStack.begin(); it != mCollisionStack.end(); ++it)
		{
			switch (GameObjects::ID((*it)->GetID()))
			{
			case AllObjects::BULLET:
			{
				// Deduct health if hit with a projectile
				if (!((Projectile*)(*it))->CheckShooter(this) && PredictCollision((*it), mX, mY, mSize))
				{
					mHealth -= ((Projectile*)(*it))->InflictDamage();
					mX += ((Projectile*)(*it))->GetDirX() * (float)_deltaTime * (mSpeed + 5.f);
					mY += ((Projectile*)(*it))->GetDirY() * (float)_deltaTime * (mSpeed + 5.f);

					if (((Projectile*)(*it))->GetShooter() == AllObjects::PLAYER)
					{
						Player* player = (Player*)((Projectile*)(*it))->AccessShooter();
						player->AddScore(1);
					}
				}
				break;
			}
			case AllObjects::PLAYER:
			{
				mState = CharacterState::WALKING;

				// Look in the direction of the player
				mDirX = mX - ((Player*)(*it))->GetX();
				mDirY = mY - ((Player*)(*it))->GetY();

				float rad = atan2f(mDirY, mDirX);
				float normal = sqrtf(powf(mDirX, 2) + powf(mDirY, 2));

				mDirX /= normal;
				mDirY /= normal;

				mBaseSprite.SetSpriteAngle((rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f));

				// Check attack radius
				float attackRadius = 340;
				if (PredictCollision((*it), mX, mY, attackRadius))
				{
					mState = CharacterState::ATTACKING;
				}
				break;
			}
			case AllObjects::ENEMY:
			{
				if (PredictCollision((*it), mX, mY, mSize))
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
				break;
			}
			}
		}
	}

	CheckHealth();

	if (mAttackWait > 0)
	{
		mAttackWait -= (float)_deltaTime;
	}

	// State machine
	switch (mState)
	{
		case CharacterState::IDLE:
		{
			break;
		}
		case CharacterState::WALKING:
		{
			// Move towards tracking point
			mX += -mDirX * (float)_deltaTime * mSpeed;
			mY += -mDirY * (float)_deltaTime * mSpeed;
			break;
		}
		case CharacterState::ATTACKING:
		{
			if (mAttackWait <= 0)
			{
				// Shoot bullet in direction of tracking coords
				mAttackWait = mAttackRate;
				CreateObject(new Bullet(mContext, mResources, this, mX, mY)); 
			}
			mState = CharacterState::IDLE;
			break;
		}
		default:
		{
			if (mCollidable) 
			{
				// Countdown before removal
				mResources->PlaySoundEffect(SoundEffects::DESTROY);
				mBaseSprite.SetSpriteXIndex(1);
				mCollidable = false;
			}
			mDeathRemove -= (float)_deltaTime;
			if (mDeathRemove <= 0)
			{
				// Spawn death particles around enemy
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 0));
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 0.78539f));
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 1.5708f));
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 2.35619f));
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 3.14159f));
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 3.92699f));
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 4.71239f));
				CreateObject(new Particle(mContext, mResources, this, mX, mY, 5.49779f));
				// Set to be destroyed
				mDestroy = true;
			}
		}
	}
}

void Enemy::Render()
{
	mBaseSprite.RenderSprite(mContext, mX, mY);
}

Enemy::Enemy(SDL_Renderer* _ctx, ResourceManager* _resources,  float _startingX, float _startingY, float _goTowardsX, float _goTowardsY,
	int _startingHealth, float _startingSpeed)
:
	Character(_ctx, _resources, {0, 0, 64, 64}, GameObjects::Tag(AllObjects::ENEMY), 2, 1, 16, _startingX, _startingY)
{
	// Offset sprite variables
	mBaseSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = -32;
	// Change search size
	mSearchSize = 800;
	// Set customizable variables
	mHealth = _startingHealth;
	mSpeed = _startingSpeed;
	mAttackRate = ((mSpeed * 1000) < 950 ? 1000 - (mSpeed * 1000) : 50);
	// Set it to collidable
	mCollidable = true;
}