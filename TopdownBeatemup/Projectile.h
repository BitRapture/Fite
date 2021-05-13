#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "GameObject.h"

class Projectile : public GameObject
{
// Protected variables
protected:
	// Damage to apply
	int mDamage{ 0 };
	// Speed of the projectile
	float mSpeed{ 0 };

	// The original shooter
	GameObject* mShooter{ nullptr };

// Protected methods
protected:
	// Destroy on collide
	void DestroyOnCollide();

// Public methods
public:
	// Inflict damage (get damage)
	int InflictDamage();

	// Constructor
	Projectile(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames, 
		float _objectSize, float _startingX, float _startingY, GameObject* _shooter);

};

#endif 
