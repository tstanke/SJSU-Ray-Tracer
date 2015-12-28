#include "glut.h"
#include "Pixel.h"
#include "Sphere.h"
#include "Util.h"
#include "Light.h"
#include "Environment.h"
#include "Polygon.h"
#include <math.h>
#include <fstream>
#include <string>

const int w = 700, h = 700;
//int w = 2560, h = 1600;
//int w = 200, h = 200;
int VisibleObj::nextUID = 0;
vector<Pixel*> pixels;
Environment environment;

void keyboard(unsigned char key, int x, int y);

void constructViewableObjects() {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//	gluLookAt(-275, 375, -550, 0, 0, -1000, 0, 0, 1);
	//	gluLookAt(0, 0, -750, 0, 0, -750, 0, 0, 1);
	gluLookAt(600, 700, -425, 0, 0, -850, 0, 0, 1);
	environment.load();
	glPopMatrix();

//	int n = 50;
//	int r = 1000;
//	for(int i = 0; i < n; i++)
//	{
//		float theta = Util::PI * 2 / n * i;
//		float x = r * cos(theta);
//		float y = r * sin(theta);
//		float p [] = {x, y, -925};
//		float silver [] = {1,1,1,.753};
//		environment.add(new Sphere(p, silver, silver, 75, &environment));
//	}
//
//	environment.save();
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, 0, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// naive way
	for (int i = 0; i < w; i++) {
		glBegin(GL_POINTS);
		for (int j = 0; j < h; j++) {
			int idx = i * h + j;
			pixels[idx]->calculate(&environment, 16);
			glColor3fv(pixels[idx]->color);
			glVertex2f(i, j);
		}
		glEnd();
		glutSwapBuffers();
	}

	keyboard('s', 0, 0);
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);

	constructViewableObjects();
}

void reshape(int width, int height) {
//	w = width;
//	h = height;

	glViewport(0, 0, w, h);

	while (pixels.size() > 0)
		pixels.pop_back();

	int raysPerPixel = 4;
	int n = (int) sqrt(raysPerPixel);
	float eyeDirection[] = { 0, 0, -1 };
	float eyePosition[] = { 0, 0, 0 };
	int w2 = w * n / 2;
	int h2 = h * n / 2;
	float maxMag = sqrt(Util::sq(w2) + Util::sq(h2));
	float maxAngle = Util::PI / 4;

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++) {
			Pixel *p = new Pixel();
			pixels.push_back(p);
			for (int i = x * n; i < (x + 1) * n; i++)
				for (int j = y * n; j < (y + 1) * n; j++) {
					float dir[3];
					Util::copy(dir, eyeDirection, 3);
					float displacement[] = { i - w2, j - h2, 0 };
					float distFromCenter = sqrt(displacement[0]
							* displacement[0] + displacement[1]
							* displacement[1]);
					float proportion = distFromCenter / maxMag;
					float axis[3];
					Util::cross(axis, eyeDirection, displacement);
					Util::normalize(axis);
					Util::doRotation(dir, proportion * maxAngle, axis);
					p->rays.push_back(new Ray(eyePosition, dir));
				}
		}
}

std::string toHex(float f)
{
	char dig [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int r = f * 255.;
	if(r < 0)
		r = 0;
	else if(r > 255)
		r = 255;
	std::string res = "";
	res+=  dig[(r & 0xF0) >> 4];
	res+=  dig[r & 0xF];
	return res;
}


void keyboard(unsigned char key, int x, int y) {
	if(key == 's')
	{
		std::ofstream file;
		file.open("screen.raw");

		file<<w<<" "<<h<<" ";

		int b = w * h;
		for(int i = 0; i < b; i++)
		{
			file << toHex(pixels[i]->color[0]) << toHex(pixels[i]->color[1]) << toHex(pixels[i]->color[2]);
		}

		file<<"\n";
		file.close();
	}
}

int main(int argc, char ** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(w, h);
	glutCreateWindow(*argv);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	init();

	glutMainLoop();

	return 0;
}

