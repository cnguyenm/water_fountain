#include "Cube.h"
#include <stdio.h>

#include <math.h>
#include <GL/freeglut.h>

Cube::Cube()
{
}

/*
 * hardcode detect collision (for now)
 * update gravity, friction
 */ 
void Cube::update() {

	if (this->on_still) return;

	// --- if already on ground ---
	if (this->on_ground) {
		//printf("vel3=%f, %f, %f \n", this->vel.x, this->vel.y, this->vel.z);
		update_friction();

		// check stop
		if (this->vel.magn() < 0.5) {
			this->on_still = true;
		}

		return;
	}

	// --- else if on air, update gravity ---
	//printf("y=%f \n", this->pos.y);
	// if collide ground
	if (this->pos.y - 0.5 <= 0.0) {

		//printf("vel=%f \n", this->vel.magn());
		
		this->pos.y = 0.5;

		// stop
	
		if ( fabs(this->vel.y) <= 1.0) {
			//printf("on ground now!!\n");
			//this->vel = Vec3(0, 0, 0);
			this->vel.y = 0;
			this->pos.y = 0.5;
			this->on_ground = true;
			return;
		}
	
		// case: fall into plane_xz
		// v_out = -b * v_in
		double b = Config::ELASTIC_CONST;
		this->vel.y = -b * this->vel.y;

		//printf("vel=%f, %f, %f \n", this->vel.x, this->vel.y, this->vel.z);

		// otherwise: use formula in slides for bouncing
		// v' = -h + l 
	}
	
	this->update_gravity();

}

void Cube::draw(Camera cam)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// --- draw 
	glLoadIdentity();
	cam.apply();

	glColor3f(0.8f, 0.2f, 0.1f);
	glTranslatef(this->pos.x, this->pos.y, this->pos.z);
	glutWireCube(this->size);
	// --- /draw

	glPopMatrix();
}

/*
 * assume: plane xz
 * TODO: flexible plane
 */
void Cube::update_friction()
{
	// random friction_coefficent
	double mu = 0.5;
	double g = Config::GRAVITY_FORCE; 
	double t = Config::DELTA_TIME / 1000.0; // msec -> sec

	Vec3 friction_accel = -Vec3(vel.x, 0, vel.z) * (mu * g);

	Vec3 V = this->vel + friction_accel * t;
	Vec3 P = this->pos + this->vel * t;
	this->vel = V;
	this->pos = P;
}

// simple ODEs
// make it work for now
void Cube::update_gravity()
{
	// delta_time = time since last update
	double t = Config::DELTA_TIME / 1000.0; // msec -> sec

	Vec3 accel = Vec3(0, -Config::GRAVITY_FORCE, 0);

	// Euler ODEs
	// vel < 0 : means fall down
	Vec3 V = this->vel + accel * t;
	Vec3 P = this->pos + this->vel * t;
	this->vel = V;
	this->pos = P;
	//printf("vel2=%f, %f, %f \n", this->vel.x, this->vel.y, this->vel.z);
}
