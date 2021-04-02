#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Character.h"

class Player : public Character
{

// Public methods
public:
	// Entity method overrides
	void Update(double& _deltaTime) override;
	void Render() override;

public:
	// Constructors
	Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite);
	// Destructor
	~Player();
};

#endif