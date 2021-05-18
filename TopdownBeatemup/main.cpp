#include "GameManager.h"

int main(int argc, char** argv)
{
	// Initialise all SDL extensions
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 ) return 400;
	if (IMG_Init(IMG_INIT_PNG) == 0) return 401;
	if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1) return 402;
	if (TTF_Init() == -1) return 403;

	// Creating this dynamically enables us specifiy when exactly to destroy it
	GameManager* Game = new GameManager;

	// Run the game
	Game->Run();

	// Delete the game, must be done this way as SDL extensions need to quit before SDL_Quit
	delete Game;

	SDL_Quit();
	return 200;
}