#include "Player.h"

void Player::UpdateGun(double& _deltaTime)
{
	// Get mouse button click
	bool mouseL = mEvents->GetMouseL();

	if (mGunWait > 0)
	{
		mGunWait -= (float)_deltaTime;
		if (mGunWait < 0) { mGunWait = 0; }
	}

	float t = fabsf(mGunWait) / mGunFireRate;
	mGunOffset = 35 - (t * 15);

	// Fire new bullet
	if (mouseL && mGunWait <= 0)
	{
		mGunWait = mGunFireRate;
		CreateObject(new Bullet(mContext, mResources, this, mX + (mDirX * -mGunOffset), mY + (mDirY * -mGunOffset)));
		mResources->PlaySoundEffect(SoundEffects::BULLET_SHOOT);
	}

	// Just for the looks
	if (mScore > 100 && mGunSprite.GetSpriteXIndex() == 0)
	{
		mGunSprite.SetSpriteXIndex(1);
		mResources->PlaySoundEffect(SoundEffects::POWERUP);
	}
	else if (mScore > 200 && mGunSprite.GetSpriteXIndex() == 1)
	{
		mGunSprite.SetSpriteXIndex(2);
		mResources->PlaySoundEffect(SoundEffects::POWERUP);
	}
}

void Player::UpdateMovement(double& _deltaTime)
{
	// Get keyboard input for movement
	int dX = mEvents->GetDeltaX(), dY = mEvents->GetDeltaY();
	bool mouseR = mEvents->GetMouseR();

	// Player speed
	float speed = 0.4f;
	if (mouseR && mSprintWait >= 0 && !mSprintCoolDown)
	{
		mSprintWait -= (float)_deltaTime;
		speed = 0.9f;
		if (mSprintWait <= 0) { mSprintCoolDown = true; }
	}
	if (mSprintWait <= mSprintAmount && mSprintCoolDown)
	{
		mSprintWait += (float)_deltaTime;
		if (mSprintWait >= mSprintAmount)
		{
			mSprintWait = mSprintAmount;
			mSprintCoolDown = false;
			mResources->PlaySoundEffect(SoundEffects::POWERUP);
		}
	}

	// Animate the legs if theres movement
	if (dX != 0 || dY != 0)
	{
		mLegsSprite.AnimateSprite(_deltaTime);
	}
	else
	{
		mLegsSprite.ResetSpriteTime();
		mLegsSprite.SetSpriteXIndex(0);
	}

	// Move player
	float pmX = mX + (dX * speed * (float)_deltaTime);
	float pmY = mY + (dY * speed * (float)_deltaTime);
	if (pmX >= 0 && pmX <= 1280) mX = pmX;
	if (pmY >= 0 && pmY <= 720) mY = pmY;


	// Get the difference between the player coords and mouse cursor
	mDirX = mX - mEvents->GetMouseX();
	mDirY = mY - mEvents->GetMouseY();

	// Get the angle from player to cursor
	float rad = atan2f(mDirY, mDirX);
	// Clamp angle to 0 to 360
	rad = (rad >= 0 ? rad : (2 * 3.1415f) + rad) * (180 / 3.1415f);
	// Get the normal of the direction vector
	float normal = sqrtf(powf(mDirX, 2) + powf(mDirY, 2));

	// Turn direction back into unit vector
	mDirX /= normal;
	mDirY /= normal;

	// Set sprite angles to the new angle, 
	mBaseSprite.SetSpriteAngle(rad);
	mLegsSprite.SetSpriteAngle(rad);
	mGunSprite.SetSpriteAngle(rad);
}

void Player::Update(double& _deltaTime)
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
					if (!((Projectile*)(*it))->CheckShooter(this))
					{
						mHealth--;
						mResources->PlaySoundEffect(SoundEffects::PLAYER_HURT);
					}
					break;
				}
			}
		}
	}

	// Update movement
	UpdateMovement(_deltaTime);

	// Update gun mechanics
	UpdateGun(_deltaTime);

	// Add to score every second
	mScoreWait -= (float)_deltaTime;
	if (mScoreWait <= 0)
	{
		mScoreWait = 1000;
		mScore++;
	}
}


void Player::Render()
{
	// Render sprites
	mLegsSprite.RenderSprite(mContext, mX, mY);
	mBaseSprite.RenderSprite(mContext, mX, mY);
	float gunOffsetX = mX + (mDirX * -mGunOffset), gunOffsetY = mY + (mDirY * -mGunOffset);
	mGunSprite.RenderSprite(mContext, gunOffsetX, gunOffsetY);

	// Render additional UI
	FontText* tScore = mResources->StringToFont("Score: " + std::to_string(mScore), Fonts::ARCADE_32, mContext);
	SDL_RenderCopy(mContext, tScore->mFont, NULL, &(tScore->mSize));
	delete tScore;

	FontText* tHealth = mResources->StringToFont("Health: " + std::to_string(mHealth), Fonts::ARCADE_32, mContext);
	tHealth->mSize.y = 32;
	SDL_RenderCopy(mContext, tHealth->mFont, NULL, &(tHealth->mSize));
	delete tHealth;

	FontText* tSprint = mResources->StringToFont("Sprint: " + std::to_string((int)((mSprintWait / mSprintAmount) * 100)), Fonts::ARCADE_32, mContext);
	tSprint->mSize.y = 64;
	SDL_RenderCopy(mContext, tSprint->mFont, NULL, &(tSprint->mSize));
	delete tSprint;
}

int Player::GetScore()
{
	return mScore;
}

void Player::AddScore(int _add)
{
	mScore += _add;
}

Player::Player(SDL_Renderer* _ctx, ResourceManager* _resources, EventManager* _eventManager)
	:
	Character(_ctx, _resources, { 0, 0, 64, 64 }, GameObjects::Tag(AllObjects::PLAYER), 1, 1, 16, 320, 240),
	mLegsSprite(_resources->GetSpriteSheet(mID), { 0, 0, 64, 64 }, 17, 2),
	mGunSprite(_resources->GetSpriteSheet(mID), { 0, 0, 64, 64 }, 3, 3),
	mEvents{ _eventManager }
{
	// Set the sprite speed of animated sprites
	mLegsSprite.mSpriteSpeed = 50.f;
	// Set the offset of all sprites to the center
	mBaseSprite.mSpriteXOffset = mGunSprite.mSpriteXOffset = mLegsSprite.mSpriteXOffset = -32;
	mBaseSprite.mSpriteYOffset = mGunSprite.mSpriteYOffset = mLegsSprite.mSpriteYOffset = -32;
	// Set the y-index to 1 so the legs animation can be used
	mLegsSprite.SetSpriteYIndex(1);
	// Set the y-index to 2 so the gun sprite can be used
	mGunSprite.SetSpriteYIndex(2);
	// Set health
	mHealth = 100;

	mX = 640;
	mY = 360;
	// Set collidable
	mCollidable = true;
}

Player::~Player()
{

}