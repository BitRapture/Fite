#include "GameManager.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) return 400;
	if (IMG_Init(IMG_INIT_PNG) == 0) return 401;

	GameManager Game;

	Game.Run();

	SDL_Quit();
	return 200;
}