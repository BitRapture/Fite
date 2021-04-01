#include "GameManager.h"

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0 ) return 400;

	GameManager Game;

	Game.Run();

	SDL_Quit();
	return 200;
}