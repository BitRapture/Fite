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
	}
}

void Player::UpdateMovement(double& _deltaTime)
{
	// Get keyboard input for movement
	int dX = mEvents->GetDeltaX(), dY = mEvents->GetDeltaY();
	bool mouseR = mEvents->GetMouseR();

	// Player speed
	float speed = 0.2f;
	if (mouseR && mSprintWait >= 0 && !mSprintCoolDown)
	{
		mSprintWait -= (float)_deltaTime;
		speed = 0.5f;
		if (mSprintWait <= 0) { mSprintCoolDown = true; }
	}
	if (mSprintWait <= mSprintAmount && mSprintCoolDown)
	{
		mSprintWait += (float)_deltaTime;
		if (mSprintWait >= mSprintAmount)
		{
			mSprintWait = mSprintAmount;
			mSprintCoolDown = false;
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
	mX += dX * speed * (float)_deltaTime;
	mY += dY * speed * (float)_deltaTime;

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
	// Update movement
	UpdateMovement(_deltaTime);

	// Update gun mechanics
	UpdateGun(_deltaTime);
}


void Player::Render()
{
	mLegsSprite.RenderSprite(mContext, mX, mY);
	mBaseSprite.RenderSprite(mContext, mX, mY);
	float gunOffsetX = mX + (mDirX * -mGunOffset), gunOffsetY = mY + (mDirY * -mGunOffset);
	mGunSprite.RenderSprite(mContext, gunOffsetX, gunOffsetY);
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

	mX = 700;
	mY = 240;
	mCollidable = true;
}

Player::~Player()
{

}