#include "GameObjects.h"

namespace GameObjects
{
	int Tag(AllObjects _tag)
	{
		return (int)_tag;
	}

	AllObjects ID(int _ID)
	{
		return (AllObjects)_ID;
	}
}