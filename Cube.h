#pragma once
#include "GameObject.h"
class Cube :
	public GameObject
{
public:
	Cube();
	bool on_ground = false;
	bool on_still = false;
	void update() override;
	
private:
	
	void update_friction();
	void update_gravity();
};

