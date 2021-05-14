#include "GameManager.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ) return 400;
	if (IMG_Init(IMG_INIT_PNG) == 0) return 401;
	if (Mix_Init(MIX_INIT_MP3) == 0) return 402;
	if (TTF_Init() == -1) return 403;

	GameManager Game;

	Game.Run();

	SDL_Quit();
	return 200;
}