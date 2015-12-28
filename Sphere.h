/*
 * Sphere.h
 *
 *  Created on: Dec 15, 2008
 *      Author: tim
 */

//#include "Ray.h"

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Ray.h"
#include <string>

class Sphere : public VisibleObj{
public:
	float position[3];
	float radius;

	inline std::string getName() {return "sphere";};
	void appendAdditional(std::ostream &out);
	void readAdditional(std::istream &in);
	float intersects(Ray* ray);
	void doCollision(Ray* ray, int reflections, float coeff);
	void doReflectiveCollision(Ray *ray, int reflections, float coeff);
	Sphere(float p[], float ambient_diffuse[], float specular [], float r, Environment *env);
	Sphere(Environment *e);
	void applyTransformation();
};


#endif /* SPHERE_H_ */
