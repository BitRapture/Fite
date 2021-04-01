#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <SDL_image.h>
#include "Entity.h"

class GameObject : public Entity
{
// Hideen variables
private:
	// Current sprite time
	float mSpriteTime{ 0 };
	// Size of the sprite
	SDL_Rect mSpriteSize{ 0, 0, 0, 0 };
	// Current frame of the sprite (x & y)
	int mSpriteIX{ 0 }, mSpriteIY{ 0 };
	// Max frames of the sprite (x & y)
	int mSpriteIXM{ 0 }, mSpriteIYM{ 0 };

// Shared variables
protected:
// Sprite variables
	// GameObject spritesheet 
	SDL_Texture* mSprite{ nullptr };
	// Sprite angle (degrees)
	float mSpriteAngle{ 0 };
	// Sprite speed (miliseconds)
	float mSpriteSpeed{ 0 };

// Generic GameObject variables
	// GameObject size (circle radius)
	float mSize{ 0 };
	// GameObject direction (degrees)
	float mDirection{ 0 };

// SDL variables
	// Pointer to the main renderer
	SDL_Renderer* mContext{ nullptr };

// Shared methods
protected:
	// Render segment of the spritesheet
	void RenderSegment(SDL_Rect& _segment);
	// Basic animation of sprite
	void AnimateSprite(double& _deltaTime);
	// Basic rendering of sprite
	void RenderSprite();
	// Set sprite frame index
	bool SetSpriteIndex(int _x, int _y = 0);

// Public methods
public:
	// Get sprite frame x-index
	int GetSpriteXIndex();
	// Get sprite frame y-index
	int GetSpriteYIndex();

public:
	// Constructor
	GameObject(SDL_Renderer* _ctx, SDL_Texture* _sprite, SDL_Rect _spriteSize, int _maxXFrames, int _maxYFrames);
	// Destructor
	~GameObject();

};

#endif