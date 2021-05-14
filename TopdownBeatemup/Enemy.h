#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Character.h"
#include "Player.h"

class Enemy : public Character
{
// Hidden variables
private:
	// Pointer to player
	Player* mFocus{ nullptr };


// Shared methods
public:
	// Entity method overrides
	void Update(double& _deltaTime) override;
	void Render() override;

	// Constructor
	Enemy(SDL_Renderer* _ctx, ResourceManager* _resources, Player* _player, float _startingX, float _startingY);
};

#endif