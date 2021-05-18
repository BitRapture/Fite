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
	// Gun sprite
	Sprite mGunSprite;

// Gun attributes
	// Offset of the gun from the player
	float mGunOffset{ 35 };
	// Gun level
	int mGunLevel{ 0 };
	// Gun firerate
	float mGunFireRate{ 100.f }, mGunWait{ 0 };

// Sprint attributes
	// Sprint cooldown and amount
	float mSprintAmount{ 3000.f };
	float mSprintWait{ mSprintAmount };
	bool mSprintCoolDown{ false };

// Score attributes
	int mScore{ 0 };
	float mScoreWait{ 1000 };

// External systems
	// Pointer to event system
	EventManager* mEvents;

// Internal methods
protected:
	// Update the gun mechanics
	void UpdateGun(double& _deltaTime);

	// Update player movement and direction
	void UpdateMovement(double& _deltaTime);

// Public methods
public:
	// Entity method overrides
	void Update(double& _deltaTime) override;
	void Render() override;

	// Let GameManager deal with scoring
	// Get score
	int GetScore();
	void AddScore(int _add);

	// Constructor
	Player(SDL_Renderer* _ctx, ResourceManager* _resources, EventManager* _eventManager);
	// Destructor
	~Player();
};

#endif