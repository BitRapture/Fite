#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <SDL.h>

class EventManager
{
// Private variables
private:
	// Change in x and y movement
	int mDeltaX{ 0 }, mDeltaY{ 0 };
	// Mouse x and y position
	int mMouseX{ 0 }, mMouseY{ 0 };
	// Mouse left and right buttons
	bool mMouseL{ false }, mMouseR{ false };

// Private methods
private:
	// Poll window events
	bool PollWindowEv(SDL_Event& _ev);
	// Poll input down events
	void PollInputDownEv(SDL_Event& _ev);
	// Poll input up events
	void PollInputUpEv(SDL_Event& _ev);
	// Poll mouse motion event
	void PollMouseMotionEv(SDL_Event& _ev);
	// Poll mouse button down events
	void PollMouseButtonDownEv(SDL_Event& _ev);
	// Poll mouse button up events
	void PollMouseButtonUpEv(SDL_Event& _ev);

// Public methods
public:
	// Poll all events
	bool Poll();

	// Get delta movements
	int GetDeltaX();
	int GetDeltaY();
	// Get mouse positions
	int GetMouseX();
	int GetMouseY();
	// Get mouse buttons
	bool GetMouseL();
	bool GetMouseR();

	// Default CTOR & DTOR
};

#endif