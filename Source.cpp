#include "GL/freeglut.h"
#include "GameObject.h"
#include <iostream>
#include "Cube.h"

float COLOR_GREEN[3] = {0, 1, 0};
float ground_size = 4;
float gravity_rate = 9.8;
float delta_time = 1000.0/60.0; // 60fps
Cube cube;
GameObject cam;  // camera

inline void initGL() {

	glClearColor(0, 0, 0, 0); // set background to black
	glClearDepth(1.0f); // set background depth to farthest
	glEnable(GL_DEPTH_TEST); // enable depth test for z-culling
	glDepthFunc(GL_LEQUAL); // set type of depth test
	glShadeModel(GL_SMOOTH); // enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // nice perspective corrections
}

inline void initGame() {

	cube = Cube();
	cube.pos = Vec3(0, 6, 0);

	cam = GameObject();
	cam.pos = Vec3(10, 10, 10);
}

inline void reshape(int width, int height) {

	if (height == 0) height = 1; // prevent divide by 0
	double aspect = (double)width / (double)height;

	// set view port
	glViewport(0, 0, width, height);

	// set aspect ratio of clipping volumne to match viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// enble perspective projection 
	gluPerspective(45.0, aspect, 0.1f, 100.f);

}

inline void apply_cam() {

	gluLookAt(
		cam.pos.x, cam.pos.y, cam.pos.z,
		0, 0, 0,  // center x,y,z
		0, 1, 0  // up vector
	);
}

inline void draw_axis() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	// --- draw 
	glLoadIdentity();
	apply_cam();
	glColor3fv(COLOR_GREEN);

	glBegin(GL_LINES);
		// x
		glVertex3f(0, 0, 0);
		glVertex3f(3, 0, 0);

		// y
		glVertex3f(0, 0, 0);
		glVertex3f(0, 3, 0);

		// z
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 3);
	glEnd();

	// --- /draw
	
	glPopMatrix();
}


inline void draw_ground() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// --- draw 
	glLoadIdentity();
	apply_cam();
	glColor3fv(COLOR_GREEN);

	glBegin(GL_QUADS);

		glVertex3f(ground_size, 0, -ground_size);
		glVertex3f(ground_size, 0, ground_size);
		glVertex3f(-ground_size, 0, ground_size);
		glVertex3f(-ground_size, 0, -ground_size);
	glEnd();

	// --- /draw

	glPopMatrix();
}

inline void draw_teapot() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	// --- draw 
	glLoadIdentity();
	apply_cam();
	
	glColor3f(0.8f, 0.2f, 0.1f);
	glutWireTeapot(1);
	// --- /draw

	glPopMatrix();
}

inline void draw_cube() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// --- draw 
	glLoadIdentity();
	apply_cam();

	glColor3f(0.8f, 0.2f, 0.1f);
	glTranslatef(cube.pos.x, cube.pos.y, cube.pos.z);
	glutWireCube(cube.size);
	// --- /draw

	glPopMatrix();
	
}

/*
 * update pos, vel of cube computationally
 * render later
 */
inline void update_cube() {

	double t = delta_time / 1000.0; // msec -> sec
	Vec3 accel = Vec3(0, -9.8, 0);

	// Euler ODEs
	Vec3 V = cube.vel + accel * t;
	Vec3 P = cube.pos + cube.vel * t;
	cube.vel = V;
	cube.pos = P;

	printf("pos %f\n", cube.pos.y);
}


void render_scene() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear color buffer (background)
	glMatrixMode(GL_MODELVIEW);

	// render 
	draw_axis();
	draw_ground();
	draw_cube();
	

	glutSwapBuffers();
}

/*
* @param value: to identify different call back functions
* may add more later
*/
void update(int value) {

	
	//update_cube();

	cube.update();
	render_scene();

	// schedule call backs, input:msec
	glutTimerFunc(delta_time, update, 1); 
}


int main(int argc, char ** argv) {

	// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);	// enable double bufferd mode
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// create window
	glutCreateWindow("Water Fountain");
	glutReshapeFunc(reshape);
	glutDisplayFunc(render_scene);
	glutTimerFunc(delta_time ,update, 1); // schedule call backs

	// init
	initGL();
	initGame();
	glutMainLoop();
	return 0;
}