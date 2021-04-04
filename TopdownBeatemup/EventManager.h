#ifndef _EVENTMANAGER_H_
#define _EVENTMANAGER_H_

#include <SDL.h>

class EventManager
{
// Private variables
private:
	// Change in x and y movement
	int mDeltaX{ 0 }, mDeltaY{ 0 };

// Private methods
private:
	// Poll window events
	bool PollWindowEv(SDL_Event& _ev);
	// Poll input down events
	void PollInputDownEv(SDL_Event& _ev);
	// Poll input up events
	void PollInputUpEv(SDL_Event& _ev);

// Public methods
public:
	// Poll all events
	bool Poll();

	// Get delta movement
	int GetDeltaX();
	int GetDeltaY();

	// Default CTOR & DTOR
};

#endif