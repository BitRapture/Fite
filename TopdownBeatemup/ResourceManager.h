#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include "GameObjects.h"

class ResourceManager
{
// Private variables
private:
	// Map of all sprites/assets/images
	// Sorted using the AllObjects enum
	std::map<int, SDL_Texture*> mTextures;

// ResourceManager flags
	// Check ResourceManager is initialised
	bool mInitialised{ false };

// Public methods
public:
	// Get a spritesheet for a related gameobject
	// Uses AllObjects enum
	SDL_Texture* GetSpriteSheet(int _tag);

	// Initialise all resources
	bool Init(SDL_Renderer* _ctx);

	// Default Constructor
	// Destructor
	~ResourceManager();
};

#endif