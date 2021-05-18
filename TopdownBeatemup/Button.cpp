#include "Button.h"

void Button::Update(double& _deltaTime)
{
	// Get mouse coords
	float mouseX = (float)mEvents->GetMouseX(),
		mouseY = (float)mEvents->GetMouseY();

	// Check if mouse cursor is inside of button
	mMouseHover = false;
	if (mouseX >= mX &&
		mouseX <= mX + mWidth &&
		mouseY >= mY &&
		mouseY <= mY + mHeight)
	{
		mMouseHover = true;
	}
}

void Button::Render()
{
	SDL_Rect box{ (int)mX, (int)mY, (int)mWidth, (int)mHeight };
	// Set draw color depending if mouse is hovering over it
	SDL_SetRenderDrawColor(mContext, mMouseHover * 60, 20, mMouseHover * 60, 255);
	// Fill the button box in
	SDL_RenderFillRect(mContext, &box);
	// Render the text on top of the button
	SDL_RenderCopy(mContext, mText->mFont, NULL, &(mText->mSize));
}

bool Button::ButtonPressed()
{
	return (mMouseHover && mEvents->GetMouseL());
}

Button::Button(SDL_Renderer* _ctx, ResourceManager* _resources, EventManager* _events, float _x, float _y, float _width, float _height, std::string _text)
	:
	Entity(_ctx, _x, _y),
	mResources{ _resources }, mEvents{ _events },
	mWidth{ _width }, mHeight{ _height }
{
	// Convert string to a font texture
	mText = mResources->StringToFont(_text, Fonts::ARCADE_32, _ctx);
	// Offset the font texture when being displayed
	mText->mSize.x = (int)(_x + 4);
	mText->mSize.y = (int)(_y + 4);
}