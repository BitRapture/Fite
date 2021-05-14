#include "ResourceManager.h"


SDL_Texture* ResourceManager::GetSpriteSheet(int _tag)
{
	return mTextures[_tag];
}

bool ResourceManager::Init(SDL_Renderer* _ctx)
{
	// Initialise all resources

	// Load images into surfaces
	SDL_Surface* sPlayer = IMG_Load("Media/FiteCharacterSheet.png"),
		* sEnemy = IMG_Load("Media/FiteEnemy.png"),
		* sProjectile = IMG_Load("Media/ProjectileBullet.png");

	// Save textures to a map
	mTextures[GameObjects::Tag(AllObjects::PLAYER)] = SDL_CreateTextureFromSurface(_ctx, sPlayer);
	mTextures[GameObjects::Tag(AllObjects::ENEMY)] = SDL_CreateTextureFromSurface(_ctx, sEnemy);
	mTextures[GameObjects::Tag(AllObjects::PROJECTILE)] = SDL_CreateTextureFromSurface(_ctx, sProjectile);

	// Free up surfaces used
	SDL_FreeSurface(sPlayer);
	SDL_FreeSurface(sEnemy);
	SDL_FreeSurface(sProjectile);

	// Check everything has been initialised correctly
	for (std::map<int, SDL_Texture*>::iterator it = mTextures.begin();
		it != mTextures.end(); ++it)
	{
		mInitialised |= ((*it).second == nullptr);
	}
	mInitialised = !mInitialised;

	return mInitialised;
}

ResourceManager::~ResourceManager()
{
	// Free all textures
	for (std::map<int, SDL_Texture*>::iterator it = mTextures.begin();
		it != mTextures.end(); ++it)
	{
		SDL_DestroyTexture((*it).second);
	}
}