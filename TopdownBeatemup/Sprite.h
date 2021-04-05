#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>

class Sprite
{
// Private variables
private:
	// Pointer to spritesheet 
	SDL_Texture* mSheet{ nullptr };
	// Current sprite time
	float mSpriteTime{ 0 };
	// Size of the sprite
	SDL_Rect mSpriteSize{ 0, 0, 0, 0 };
	// Current frame of the sprite (x & y)
	int mSpriteIX{ 0 }, mSpriteIY{ 0 };
	// Max frames of the sprite (x & y)
	int mSpriteIXM{ 0 }, mSpriteIYM{ 0 };
	// Sprite angle (degrees)
	float mSpriteAngle{ 0 };

// Public variables
public:
// These variables can be set to anything
// so they don't need getters or setters
	// Sprite speed (miliseconds)
	float mSpriteSpeed{ 0 };
	// Sprite image offset from _camX & _camY (entity mX & mY)
	float mSpriteXOffset{ 0 }, mSpriteYOffset{ 0 };

// Public methods
public:
	// Render segment of the spritesheet
	void RenderSegment(SDL_Renderer* _ctx, SDL_Rect& _segment, float& _camX, float& _camY);
	// Basic animation of sprite
	void AnimateSprite(double& _deltaTime);
	// Basic rendering of sprite
	void RenderSprite(SDL_Renderer* _ctx, float& _camX, float& _camY);
	// Reset the sprite time
	void ResetSpriteTime();
	// Set sprite frame x & y index
	bool SetSpriteXIndex(int _x);
	bool SetSpriteYIndex(int _y);
	// Get sprite frame x & y index
	int GetSpriteXIndex();
	int GetSpriteYIndex();
	// Set sprite angle (degrees)
	void SetSpriteAngle(float _angle);
	// Get sprite angle (degrees)
	float GetSpriteAngle();
	// Get sprite size
	SDL_Rect GetSpriteSize();

	// Constructor
	Sprite(SDL_Texture* _spriteSheet, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames);
};

#endif