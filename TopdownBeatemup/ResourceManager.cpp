#include "ResourceManager.h"

SDL_Texture* ResourceManager::GetSpriteSheet(int _tag)
{
	return mTextures[_tag];
}

FontText* ResourceManager::StringToFont(std::string _string, Fonts _font, SDL_Renderer* _ctx)
{
	FontText* text = new FontText;
	SDL_Surface* sFont = TTF_RenderText_Solid(mFonts[_font], _string.c_str(), { 255, 255, 255, 255 });
	text->mFont = SDL_CreateTextureFromSurface(_ctx, sFont);
	text->mSize.w = sFont->w;
	text->mSize.h = sFont->h;
	SDL_FreeSurface(sFont);
	return text;
}

void ResourceManager::PlaySoundEffect(SoundEffects _sound)
{
	for (size_t it = 0; it < mUsableChannels.size(); ++it)
	{
		mUsableChannels[it] = !(Mix_Playing(it) == 1);
		if (mUsableChannels[it])
		{
			Mix_PlayChannel(it, mSoundEffects[_sound], 0);
			mUsableChannels[it] = false;
			break;
		}
	}
}

void ResourceManager::PlayMusic(Music _music)
{
	Mix_VolumeMusic(5);
	Mix_PlayMusic(mMusic[_music], -1);
}

bool ResourceManager::Init(SDL_Renderer* _ctx)
{
	// Initialise all resources

	// Load images into surfaces
	SDL_Surface* sPlayer = IMG_Load("Media/FiteCharacterSheet.png"),
		* sEnemy = IMG_Load("Media/FiteEnemySheet.png"),
		* sBullet = IMG_Load("Media/ProjectileBullet.png"),
		* sParticle = IMG_Load("Media/ProjectileParticle.png");

	// Save textures to a map
	mTextures[GameObjects::Tag(AllObjects::PLAYER)] = SDL_CreateTextureFromSurface(_ctx, sPlayer);
	mTextures[GameObjects::Tag(AllObjects::ENEMY)] = SDL_CreateTextureFromSurface(_ctx, sEnemy);
	mTextures[GameObjects::Tag(AllObjects::BULLET)] = SDL_CreateTextureFromSurface(_ctx, sBullet);
	mTextures[GameObjects::Tag(AllObjects::PARTICLE)] = SDL_CreateTextureFromSurface(_ctx, sParticle);

	// Free up surfaces used
	SDL_FreeSurface(sPlayer);
	SDL_FreeSurface(sEnemy);
	SDL_FreeSurface(sBullet);
	SDL_FreeSurface(sParticle);

	// Initialise audio channels
	Mix_AllocateChannels(mChannels);
	mUsableChannels.resize(mChannels, true);

	// Load sound effects into map
	mSoundEffects[SoundEffects::BULLET_HIT] = Mix_LoadWAV("Media/BulletHitSound.wav");
	mSoundEffects[SoundEffects::BULLET_SHOOT] = Mix_LoadWAV("Media/BulletShootSound.wav");
	mSoundEffects[SoundEffects::DESTROY] = Mix_LoadWAV("Media/DestroySound.wav");
	mSoundEffects[SoundEffects::PLAYER_HURT] = Mix_LoadWAV("Media/PlayerHurtSound.wav");
	mSoundEffects[SoundEffects::POWERUP] = Mix_LoadWAV("Media/PowerupSound.wav");

	// Load music into map
	mMusic[Music::BACKGROUND_MUSIC] = Mix_LoadMUS("Media/BackgroundMusic.wav");

	// Load fonts into map
	mFonts[Fonts::ARCADE_32] = TTF_OpenFont("Media/GameFont.ttf", 32);
	mFonts[Fonts::ARCADE_16] = TTF_OpenFont("Media/GameFont.ttf", 16);
	mFonts[Fonts::ARCADE_8] = TTF_OpenFont("Media/GameFont.ttf", 8);

	// Check everything has been initialised correctly
	for (std::map<int, SDL_Texture*>::iterator it = mTextures.begin();
		it != mTextures.end(); ++it)
	{
		mInitialised |= ((*it).second == nullptr);
	}
	for (std::map<Fonts, TTF_Font*>::iterator it = mFonts.begin();
		it != mFonts.end(); ++it)
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
	// Free all sound effects
	for (std::map<SoundEffects, Mix_Chunk*>::iterator it = mSoundEffects.begin();
		it != mSoundEffects.end(); ++it)
	{
		Mix_FreeChunk((*it).second);
	}
	// Free all music
	for (std::map<Music, Mix_Music*>::iterator it = mMusic.begin();
		it != mMusic.end(); ++it)
	{
		Mix_FreeMusic((*it).second);
	}
	// Free all fonts
	for (std::map<Fonts, TTF_Font*>::iterator it = mFonts.begin();
		it != mFonts.end(); ++it)
	{
		TTF_CloseFont((*it).second);
	}

	Mix_Quit();
	IMG_Quit();
	TTF_Quit();
}