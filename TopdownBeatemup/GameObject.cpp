#include "GameObject.h"

void GameObject::SetDirection(float _angle)
{
	float cos = cosf(_angle), sin = sinf(_angle), tempX = mDirX;
	mDirX = (mDirX * cos) - (mDirY * sin);
	mDirY = (tempX * sin) + (mDirY * cos);
}

void GameObject::DrawHitboxes()
{
	// Set color to yellow
	SDL_SetRenderDrawColor(mContext, 255, 255, 0, 255);
	// Draw a box (actually the circle radius, easier to display as a rect though)
	SDL_Rect test{ (int)(mX - mSize), (int)(mY - mSize), (int)(mSize * 2), (int)(mSize * 2) };
	// Render hitbox around object
	SDL_RenderDrawRect(mContext, &test);
}

bool GameObject::PredictCollision(GameObject* _object, float& _x, float& _y, float& _searchRadius)
{
	return ((powf(_x - _object->mX, 2) + powf(_y - _object->mY, 2)) <= powf(_searchRadius + _object->mSize, 2));
}

float GameObject::GetDirX()
{
	return mDirX;
}

float GameObject::GetDirY()
{
	return mDirY;
}

int GameObject::GetID()
{
	return mID;
}

GameObject* GameObject::AccessCreationQueue(size_t _index)
{
	if (_index >= mCreationQueue.size()) return nullptr;
	return mCreationQueue[_index];
}

bool GameObject::AccessCreationQueueCollisions(size_t _index)
{
	if (_index >= mCreationQueue.size()) return false;
	return mCreationCollidable[_index];
}

size_t GameObject::GetCreationQueueSize()
{
	return mCreationQueue.size();
}

void GameObject::CreateObject(GameObject* _object, bool _selfCollidable)
{
	mCreationQueue.push_back(_object);
	mCreationCollidable.push_back(_selfCollidable);
}

void GameObject::ClearCreationQueue()
{
	mCreationQueue.clear();
	mCreationCollidable.clear();
}

GameObject::GameObject(SDL_Renderer* _ctx, ResourceManager* _resources, SDL_Rect& _spriteSize, int& _ID, int& _maxXFrames, int& _maxYFrames, float& _objectSize, float& _startingX, float& _startingY)
	:
	Entity(_ctx, _startingX, _startingY),
	mResources{ _resources },
	mBaseSprite(_resources->GetSpriteSheet(_ID), _spriteSize, _maxXFrames, _maxYFrames),
	mSize{ _objectSize }, mSearchSize{ _objectSize }, mID{ _ID }
{

}

GameObject::~GameObject()
{
	// Destroy any objects in creation queue
	for (std::vector<GameObject*>::iterator it = mCreationQueue.begin();
		it != mCreationQueue.end(); ++it)
	{
		// Delete object on heap
		delete (*it);
		// remove dangling pointers
		(*it) = nullptr;
	}
	mCollisionStack.clear();
}