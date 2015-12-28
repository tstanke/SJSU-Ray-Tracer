/*
 * Light.cpp
 *
 *  Created on: Dec 15, 2008
 *      Author: tim
 */

#include "Light.h"
#include "Util.h"
#include <math.h>
#include "Ray.h"

#include <iostream>

Light::Light(float p[], Environment *env) {
	environment = env;
	for (int i = 0; i < 3; i++)
		position[i] = p[i];
}
void Light::setAmbient(float mat[]) {
	for (int i = 0; i < 4; i++)
		ambient[i] = mat[i];
}
void Light::setDiffuse(float mat[]) {
	for (int i = 0; i < 4; i++)
		diffuse[i] = mat[i];
}
void Light::setSpecular(float mat[]) {
	for (int i = 0; i < 4; i++)
		specular[i] = mat[i];
}

/**
 * c is the color array to add to
 * p is the location of the point to light
 * v is the viewpoint
 * n is the normal at the point
 * m is the material color
 */
void Light::apply(float c[], float p[], float v[], float n[],
		float mat_ambient_diffuse[], float mat_specular[], float coeff,
		int itemID) {

	bool occluded = 0;

	float direction[3];
	float distToP = 0;
	Util::difference(direction, p, position);

	for (int i = 0; i < 3; i++)
		distToP += Util::sq(direction[i]);
	distToP = sqrt(distToP);

	Util::normalize(direction);
	Ray *ray = new Ray(position, direction);
	for (int i = 0; i < environment->o; i++) {
		if (environment->objects[i]->uid != itemID) {
			float d = environment->objects[i]->intersects(ray);
			if (d > 0 && d < distToP) {
				occluded = 1;
				break;
			}
		}
	}
	delete ray;

	float contribution[] = { 0, 0, 0 };

	// ambient
	for (int i = 0; i < 3; i++)
		contribution[i] += mat_ambient_diffuse[i] * mat_ambient_diffuse[3]
				* ambient[i] * ambient[3];

	if (!occluded) {
		float pointToLight[3];
		for (int i = 0; i < 3; i++)
			pointToLight[i] = position[i] - p[i];
		Util::normalize(pointToLight);

		// diffuse
		float f = Util::dot(n, pointToLight);
		for (int i = 0; i < 3; i++)
			contribution[i] += mat_ambient_diffuse[i] * mat_ambient_diffuse[3]
					* diffuse[i] * f * diffuse[3];

		// specular
		float pointToView[3];
		float reflectedLight[3];
		for (int i = 0; i < 3; i++) {
			pointToView[i] = v[i] - p[i];
			reflectedLight[i] = pointToLight[i];
		}
		Util::doRotation(reflectedLight, Util::PI, n);
		Util::normalize(pointToView);
		float specularFactor = Util::dot(reflectedLight, pointToView);
		for (int i = 0; i < 3; i++)
			contribution[i] += mat_specular[i] * specular[i] * specularFactor
					* specular[3] * mat_specular[3];
	}

	for (int i = 0; i < 3; i++) {
//		c[i] *= 1 - coeff;
		c[i] += contribution[i] * coeff;
//		c[i] = Util::min(c[i], 1);
	}
}

Light::Light(Environment *e)
{
	environment = e;
}

void Light::writeTo(std::ostream &out)
{
	out << "light ";
	for(int i = 0; i < 3; i++)
		out << position[i] << " ";
	for(int i = 0; i < 4; i++)
		out << ambient[i] << " ";
	for(int i = 0; i < 4; i++)
		out << diffuse[i] << " ";
	for(int i = 0; i < 4; i++)
		out << specular[i] << " ";
}
void Light::readFrom(std::istream &in)
{
	for(int i = 0; i < 3; i++)
		in >> position[i];
	for(int i = 0; i < 4; i++)
		in >> ambient[i] ;
	for(int i = 0; i < 4; i++)
		in >> diffuse[i] ;
	for(int i = 0; i < 4; i++)
		in >> specular[i];
}

void Light::applyTransformation()
{
	Util::transform(position);
}
