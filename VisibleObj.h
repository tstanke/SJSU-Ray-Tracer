/*
 * VisibleObj.h
 *
 *  Created on: Dec 16, 2008
 *      Author: tim
 */

#ifndef VISIBLEOBJ_H_
#define VISIBLEOBJ_H_

#include <iostream>
#include <string>

class Ray;
class Environment;

class VisibleObj {
public:

	Environment *environment;
	float mat_ambient_diffuse[4];
	float mat_specular[4];
	int uid;
	static int nextUID;

	void writeTo(std::ostream &out);
	void readGeneralData(std::istream &in);
	virtual std::string getName() = 0;
	static void readFrom(std::istream &in, Environment *e);
	virtual void readAdditional(std::istream &in) = 0;
	virtual void appendAdditional(std::ostream &out) = 0;
	virtual float intersects(Ray* ray) = 0;
	virtual void doCollision(Ray* ray, int reflections, float coeff) = 0;
	virtual void applyTransformation() = 0;
};


#endif /* VISIBLEOBJ_H_ */
