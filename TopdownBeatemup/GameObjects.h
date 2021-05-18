#ifndef _GAMEOBJECTS_H_
#define _GAMEOBJECTS_H_

// An Enum that shows an overview of all
// instantiable game objects in the game
enum class AllObjects
{
	PLAYER,
	ENEMY,
	BULLET,
	PARTICLE
};

namespace GameObjects
{
	// Convert enum to integer for GameObject IDs (used in collision manager
	int Tag(AllObjects _tag);
	// Convert integer to enum for GameObject IDs
	AllObjects ID(int _ID);
}

#endif