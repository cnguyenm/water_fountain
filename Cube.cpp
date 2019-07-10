#include "Cube.h"
#include <stdio.h>


Cube::Cube()
{
}

// hardcode detect collision (for now)
void Cube::update() {

	// if already on ground
	// add_more later: when more action
	if (this->on_ground) return;

	// if collide ground
	// printf("y=%f \n", this->pos.y);
	if (this->pos.y - 0.5 <= 0.0) {

		//printf("vel=%f \n", this->vel.magn());
		this->pos.y = 0.5;

		// stop
		if (this->vel.magn() <= 1.0) {
			printf("stop!!\n");
			this->vel = Vec3(0, 0, 0);
			this->pos.y = 0.5;
			this->on_ground = true;
			return;
		}
	
		// case: vertical fall
		// v_out = -b * v_in
		double b = Config::ELASTIC_CONST;
		this->vel.y = -b * this->vel.y;
	}
	
	
	// -- update gravity --
	
	// delta_time = time since last update
	double t = Config::DELTA_TIME / 1000.0; // msec -> sec
		
	Vec3 accel = Vec3(0, -Config::GRAVITY_FORCE, 0);

	// Euler ODEs
	// vel < 0 : means fall down
	Vec3 V = this->vel + accel * t;
	Vec3 P = this->pos + this->vel * t;
	this->vel = V;
	this->pos = P;
	
}