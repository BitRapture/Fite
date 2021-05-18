#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
// Hidden variables
private:
	// Speed
	float mSpeed{ 0.2f };

	// Death remove
	float mDeathRemove{ 250.f };

// Attack attributes
	float mAttackRate{ 100.f }, mAttackWait{ 0 };


// Shared methods
public:
	// Entity method overrides
	void Update(double& _deltaTime) override;
	void Render() override;

	// Constructor
	Enemy(SDL_Renderer* _ctx, ResourceManager* _resources, float _startingX, float _startingY, float _goTowardsX, float _goTowardsY,
	int _startingHealth, float _startingSpeed);
};

#endif