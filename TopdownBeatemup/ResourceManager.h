#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <map>
#include "GameObjects.h"

enum class SoundEffects
{
	BULLET_SHOOT,
	BULLET_HIT,
	DESTROY,
	PLAYER_HURT,
	POWERUP
};

enum class Music
{
	BACKGROUND_MUSIC
};

enum class Fonts
{
	ARCADE_32,
	ARCADE_16,
	ARCADE_8
};

// Small structure to get any generated text
struct FontText
{
	SDL_Texture* mFont{ nullptr };
	SDL_Rect mSize{ 0, 0, 0, 0 };

	~FontText()
	{
		// Destroy mFont when FontText gets deleted
		SDL_DestroyTexture(mFont);
	}
};

class ResourceManager
{
// Private variables
private:
	// Map of all sprites/assets/images
	// Sorted using the AllObjects enum
	std::map<int, SDL_Texture*> mTextures;

	// Map of all sound effects
	std::map<SoundEffects, Mix_Chunk*> mSoundEffects;
	// Map of all music
	std::map<Music, Mix_Music*> mMusic;
	// Map of all fonts
	std::map<Fonts, TTF_Font*> mFonts;

	// Audio channels
	int mChannels{ 64 };
	std::vector<bool> mUsableChannels;

// ResourceManager flags
	// Check ResourceManager is initialised
	bool mInitialised{ false };

// Internal methods
protected:

// Public methods
public:
	// Get a spritesheet for a related gameobject
	// Uses AllObjects enum
	SDL_Texture* GetSpriteSheet(int _tag);

	// Get a string transformed to font as a texture
	FontText* StringToFont(std::string _string, Fonts _font, SDL_Renderer* _ctx);

	// Play sound effect
	void PlaySoundEffect(SoundEffects _sound);

	// Play music
	void PlayMusic(Music _music);

	// Initialise all resources
	bool Init(SDL_Renderer* _ctx);

	// Default Constructor
	// Destructor
	~ResourceManager();
};

#endif