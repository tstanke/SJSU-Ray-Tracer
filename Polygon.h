/*
 * Polygon.h
 *
 *  Created on: Dec 16, 2008
 *      Author: tim
 */

#ifndef POLYGON_H_
#define POLYGON_H_

#include "VisibleObj.h"
#include <iostream>
#include <string>

class Ray;
class Environment;

class Polygon : public VisibleObj{
public:

	float pos [32][3];
	float normal[3];
	float checkerSize;
	int n;

	Polygon(float x [], float y[], float z[], int n, float ambient_diffuse[], float specular [], float checkersz, Environment *env);
	Polygon(Environment *e);
	float intersects(Ray* ray);
	inline std::string getName() { return "polygon";};
	void appendAdditional(std::ostream &out);
	void readAdditional(std::istream &in);
	void doCollision(Ray* ray, int reflections, float coeff);
	void recalculateNormal();
	void applyTransformation();
};

#endif /* POLYGON_H_ */
