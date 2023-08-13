#include "Entity.h"
#include "../Math/Vector3f.h"
//#include "../Math/Plane.h"


class Rectangle : public Entity
{
public:
	//Plane plane;
	float w;
	float h;
	virtual bool isRectangle() { return true; }
};