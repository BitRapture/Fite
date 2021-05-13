#include "EventManager.h"

bool EventManager::PollWindowEv(SDL_Event& _ev)
{
	bool terminateProgram = false;
	switch (_ev.window.event)
	{
	case SDL_WINDOWEVENT_CLOSE: { terminateProgram = true; break; }
	}
	return terminateProgram;
}

void EventManager::PollInputDownEv(SDL_Event& _ev)
{
	switch (_ev.key.keysym.sym)
	{
	case SDLK_d:
	case SDLK_RIGHT: { mDeltaX = 1; break; }
	case SDLK_a:
	case SDLK_LEFT: { mDeltaX = -1; break; }
	case SDLK_w:
	case SDLK_UP: { mDeltaY = -1; break; }
	case SDLK_s:
	case SDLK_DOWN: { mDeltaY = 1; break; }
	}
}

void EventManager::PollInputUpEv(SDL_Event& _ev)
{
	switch (_ev.key.keysym.sym)
	{
	case SDLK_d:
	case SDLK_RIGHT: { if (mDeltaX > 0) mDeltaX = 0; break; }
	case SDLK_a:
	case SDLK_LEFT: { if (mDeltaX < 0) mDeltaX = 0; break; }
	case SDLK_w:
	case SDLK_UP: { if (mDeltaY < 0) mDeltaY = 0; break; }
	case SDLK_s:
	case SDLK_DOWN: { if (mDeltaY > 0) mDeltaY = 0; break; }
	}
}

void EventManager::PollMouseMotionEv(SDL_Event& _ev)
{
	mMouseX = _ev.motion.x;
	mMouseY = _ev.motion.y;
}

void EventManager::PollMouseButtonDownEv(SDL_Event& _ev)
{
	switch (_ev.button.button)
	{
	case SDL_BUTTON_LEFT: { mMouseL = true; break;  }
	case SDL_BUTTON_RIGHT: { mMouseR = true; break;  }
	}
}

void EventManager::PollMouseButtonUpEv(SDL_Event& _ev)
{
	switch (_ev.button.button)
	{
	case SDL_BUTTON_LEFT: { mMouseL = false; break; }
	case SDL_BUTTON_RIGHT: { mMouseR = false; break; }
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
		case SDL_MOUSEMOTION: { PollMouseMotionEv(event); break; }
		case SDL_MOUSEBUTTONDOWN: { PollMouseButtonDownEv(event); break; }
		case SDL_MOUSEBUTTONUP: { PollMouseButtonUpEv(event); break; }
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

int EventManager::GetMouseX()
{
	return mMouseX;
}

int EventManager::GetMouseY()
{
	return mMouseY;
}

bool EventManager::GetMouseL()
{
	return mMouseL;
}

bool EventManager::GetMouseR()
{
	return mMouseR;
}


// To-do
// Add keybind support
//	-> Maybe after assignment