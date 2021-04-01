#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity
{
// Shared variables
protected:
	// Entity coordinates
	float mX{ 0 }, mY{ 0 };

// Pure virtual methods
public:
	// Update method
	void virtual Update(double& _deltaTime) = 0;
	// Render method
	void virtual Render() = 0;

	// Default CTOR & DTOR
};

#endif