#pragma once

#include "Vec3.h"
#include "Config.h"

class GameObject
{
public:
	
	Vec3 pos;	// position
	Vec3 vel;	// velocity
	Vec3 color; // color rgb
	double size = 1;

	GameObject();
	virtual void update() {};
	virtual void draw() {};
};

