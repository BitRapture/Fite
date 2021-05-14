#ifndef _PROJECTILES_H_
#define _PROJECTILES_H_

#include "Projectile.h"

class Bullet : public Projectile
{

// Public methods
public:
	// Update entity override
	void Update(double& _deltaTime) override;

	// Render entity override
	void Render() override;

	// Constructor
	Bullet(SDL_Renderer* _ctx, ResourceManager* _resources, GameObject* _shooter, float _startingX, float _startingY);
};

#endif