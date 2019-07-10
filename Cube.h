#pragma once
#include "GameObject.h"
class Cube :
	public GameObject
{
public:
	Cube();
	bool on_ground = false;

	void update() override;
	

};

