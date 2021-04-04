#include "EventManager.h"

bool EventManager::PollWindowEv(SDL_Event& _ev)
{
	bool terminateProgram = false;
	switch (_ev.window.event)
	{
	case SDL_WINDOWEVENT_CLOSE: { terminateProgram = true; }
	}
	return terminateProgram;
}

void EventManager::PollInputDownEv(SDL_Event& _ev)
{
	switch (_ev.key.keysym.sym)
	{
	case SDLK_RIGHT: { mDeltaX = 1; break; }
	case SDLK_LEFT: { mDeltaX = -1; break; }
	case SDLK_UP: { mDeltaY = -1; break; }
	case SDLK_DOWN: { mDeltaY = 1; break; }
	}
}

void EventManager::PollInputUpEv(SDL_Event& _ev)
{
	switch (_ev.key.keysym.sym)
	{
	case SDLK_RIGHT: { if (mDeltaX > 0) mDeltaX = 0; break; }
	case SDLK_LEFT: { if (mDeltaX < 0) mDeltaX = 0; break; }
	case SDLK_UP: { if (mDeltaY < 0) mDeltaY = 0; break; }
	case SDLK_DOWN: { if (mDeltaY > 0) mDeltaY = 0; break; }
	}
}

bool EventManager::Poll()
{
	SDL_Event event;
	bool terminateProgram = false;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT: { terminateProgram = PollWindowEv(event); break; }
		case SDL_QUIT: { terminateProgram = true; break; }
		case SDL_KEYDOWN: { PollInputDownEv(event); break; }
		case SDL_KEYUP: { PollInputUpEv(event); break; }
		}
	}
	return terminateProgram;
}

int EventManager::GetDeltaX()
{
	return mDeltaX;
}

int EventManager::GetDeltaY()
{
	return mDeltaY;
}

// To-do
// Add keybind support
//	-> Maybe after assignment