/*
 * Light.h
 *
 *  Created on: Dec 15, 2008
 *      Author: tim
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include <iostream>

class Environment;

class Light {
public:
	float position[3];
	float ambient[4];
	float diffuse[4];
	float specular[4];
	Environment *environment;
	Light(float p [], Environment *env);
	Light(Environment *env);
	void setAmbient(float mat[]);
	void setDiffuse(float mat[]);
	void setSpecular(float mat[]);
	void apply(float c [], float p [], float v [], float n [], float mat_ambient_diffuse [], float mat_specular[], float coeff, int itemID);
	void writeTo(std::ostream &out);
	void readFrom(std::istream &in);
	void applyTransformation();
};

#endif /* LIGHT_H_ */
