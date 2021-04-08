#include "GameObjectManager.h"

void GameObjectManager::CheckCollisions(GameObject* _object)
{
	std::vector<int>::iterator i = _object->mOMIndices.begin(),
		e = _object->mOMIndices.end();

	for (; i != e; ++i)
	{
		int index = *i;
		if (mGrid[index].size() <= 1) continue;
		std::vector<GameObject*>::iterator gridI = mGrid[index].begin(),
			gridE = mGrid[index].end();
		for (; gridI != gridE; ++gridI)
		{
			if ((*gridI) == _object) continue;
			if (_object->CheckCollision((*gridI)))
			{
				_object->mCollisions.push_back((*gridI));
			}
		}
	}
}

void GameObjectManager::AddObject(GameObject* _object, int _index)
{
	mGrid[_index].push_back(_object);
}

void GameObjectManager::RemoveObject(GameObject* _object, int _index)
{
	std::vector<GameObject*>::iterator i = mGrid[_index].begin(),
		e = mGrid[_index].end();

	while (i != e)
	{
		if ((*i) == _object)
		{
			mGrid[_index].erase(i);
			break;
		}
		else
		{
			++i;
		}
	}
}

float GameObjectManager::GetCellWidth()
{
	return mCellWidth;
}
float GameObjectManager::GetCellHeight()
{
	return mCellHeight;
}

void GameObjectManager::Delete()
{
	if (mGrid == nullptr) return;
	for (int i = 0; i < mGridSize; ++i)
	{
		mGrid[i].clear();
	}
	delete[] mGrid;
	mGridInitialised = false;
}

bool GameObjectManager::IsInit()
{
	return mGridInitialised;
}

GameObjectManager::GameObjectManager(int _gameSpaceW, int _gameSpaceH, int _cellAmount)
:
	mGridSize{ _cellAmount }
{
	mCellWidth = _gameSpaceW / _cellAmount;
	mCellHeight = _gameSpaceH / _cellAmount;
	mGrid = new std::vector<GameObject*>[_cellAmount];
	mGridInitialised = (mGrid != nullptr);
}

GameObjectManager::~GameObjectManager()
{
	Delete();
}