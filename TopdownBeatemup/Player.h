#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Character.h"
#include "EventManager.h"

class Player : public Character
{
// Private variables
private:
// Additional sprites
	// Player legs
	Sprite mLegsSprite;

// External systems
	// Pointer to event system
	EventManager* mEvents;

// Public methods
public:
	// Entity method overrides
	void Update(double& _deltaTime) override;
	void Render() override;

	// Constructor
	Player(SDL_Renderer* _ctx, SDL_Texture* _playerSprite, EventManager* _eventManager);
	// Destructor
	~Player();
};

#endif