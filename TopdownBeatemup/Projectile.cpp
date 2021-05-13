#include "Projectile.h"

int Projectile::InflictDamage()
{
	return mDamage;
}

void Projectile::DestroyOnCollide()
{
	// Setting this to false removes it from the CollisionManager
	mCollidable = false;
	// Remove from EntityList in GameManager
	mDestroy = true;
}

Projectile::Projectile(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames, 
	float _objectSize, float _startingX, float _startingY, GameObject* _shooter)
	:
	GameObject(_ctx, _sprite, _spriteSize, _maxXFrames, _maxYFrames, _objectSize, _startingX, _startingY),
	mShooter{ _shooter }
{
	// Set the projectile to be collidable
	mCollidable = true;
	// Set the direction of the projectile
	mDirX = -_shooter->GetDirX();
	mDirY = -_shooter->GetDirY();
	// Set the sprite angle
	float rad = atan2f(mDirY, mDirX);
	mBaseSprite.SetSpriteAngle((rad >= 0 ? rad : (2 * 3.1415f) + rad)* (180 / 3.1415f));
}