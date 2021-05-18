#include "Scene.h"

void Scene::CreateGameObject(GameObject* _object, bool _isSelfCollidable)
{
	mGameObjects->push_back(_object);
	mEntityList->push_back(_object);
	mCollisions->AddObject(_object, _isSelfCollidable);
}

void Scene::CreateEntity(Entity* _entity)
{
	mEntityList->push_back(_entity);
}

bool Scene::Finished()
{
	return mFinished;
}

bool Scene::Quit()
{
	return mQuit;
}

Scene::Scene(CollisionManager* _collisions, ResourceManager* _resources, EventManager* _events, SDL_Renderer* _context,
	std::vector<Entity*>* _entityList, std::vector<GameObject*>* _gameObjectList)
:
	mCollisions{ _collisions }, mResources{ _resources }, mEvents{ _events }, mContext{ _context },
	mEntityList{ _entityList }, mGameObjects{ _gameObjectList }
{

}