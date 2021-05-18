#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Entity.h"
#include "ResourceManager.h"
#include "EventManager.h"

class Button : public Entity
{
// Private variables
private:
	// Pointer to resources
	ResourceManager* mResources{ nullptr };
	// Pointer to event system
	EventManager* mEvents{ nullptr };

	// Button dimensions
	float mWidth{ 0 }, mHeight{ 0 };

	// Text to be displayed
	FontText* mText{ nullptr };

	// Is mouse hovering over
	bool mMouseHover{ false };

// Public methods
public:
	// Override update method
	void Update(double& _deltaTime) override;
	// Override render method
	void Render() override;

	// Get button pressed result
	bool ButtonPressed();

	// Constructor
	Button(SDL_Renderer* _ctx, ResourceManager* _resources, EventManager* _events, float _x, float _y, float _width, float _height, std::string _text);
	// Default DTOR FontText has a DTOR which is called automatically
};

#endif