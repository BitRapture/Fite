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
	// Fall-off of the projectile
	float mFallOff{ 0 };

	// The original shooter
	GameObject* mShooter{ nullptr };

// Protected methods
protected:
	// Destroy on collide
	void DestroyOnCollide();
	
	// Calculatr fall-off
	void CalculateFallOff(double& _deltaTime);

// Public methods
public:
	// Inflict damage (get damage)
	int InflictDamage();

	// Check if the game object is the original shooter
	bool CheckShooter(GameObject* _self);

	// Get shooter object tag
	AllObjects GetShooter();

	// Access a read only shooter
	const GameObject* AccessShooter();

	// Constructor
	Projectile(SDL_Renderer* _ctx, ResourceManager* _resources, SDL_Rect _spriteSize, int _ID, int _maxXFrames, int _maxYFrames,
		float _objectSize, float _startingX, float _startingY, GameObject* _shooter);

};

#endif 
