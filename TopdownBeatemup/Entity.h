#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SDL.h>

class Entity
{
// Shared variables
protected:
	// Entity coordinates
	float mX{ 0 }, mY{ 0 };

	// Pointer to the renderer
	SDL_Renderer* mContext{ nullptr };

// Pure virtual methods
public:
	// Update method
	void virtual Update(double& _deltaTime) = 0;
	// Render method
	void virtual Render() = 0;

	// Get x & y positions
	float GetX();
	float GetY();

	// Constructor
	Entity(SDL_Renderer* _ctx, float& _startingX, float& _startingY);
};

#endif