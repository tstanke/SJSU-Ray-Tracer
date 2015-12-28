/*
 * Sphere.cpp
 *
 *  Created on: Dec 15, 2008
 *      Author: tim
 */

#include <math.h>
#include <iostream.h>
#include "Sphere.h"
#include "Util.h"
#include "VisibleObj.h"

/**
 * Returns the distance of the nearest intersection
 * of this Sphere and the Ray if there is one, -1 otherwise.
 */
float Sphere::intersects(Ray* ray) {

	float c [3];
	for(int i = 0; i <3; i++)
		c[i] = position[i] - ray->position[i];

	float lDotC = Util::dot(ray->direction, c);
	float toSqrt = Util::sq(lDotC) - Util::dot(c, c) + Util::sq(radius);
	if(toSqrt < 0)
		return -1;

	float mysqrt = sqrt(toSqrt);
	float d = lDotC + mysqrt;
	float d2 = lDotC - mysqrt;
	if(d2 >= 0 && d2 < d)
		d = d2;

	return d;

}

void Sphere::doCollision(Ray *ray, int reflections, float coeff)
{
	doReflectiveCollision(ray, reflections, coeff);
}


/**
 * Reflects the ray and factors the color of this
 * sphere into its color.
 */
void Sphere::doReflectiveCollision(Ray* ray, int reflections, float coeff) {
	float d = intersects(ray);
//	std::cout<<"Distance: "<<d<<"\n";
	float p [3];
	for(int i = 0; i < 3; i++)
		p[i] = ray->position[i] + d * ray->direction[i];

	float normal [3];
	for(int i = 0; i < 3; i++)
		normal[i] = p[i] - position[i];
	Util::normalize(normal);

	for(int i = 0; i < environment->l; i++)
	{
		environment->lights[i]->apply(ray->color, p, ray->position, normal, mat_ambient_diffuse, mat_specular, coeff, uid);
	}

	float heading[3];
	float oldDirection[3];
	float oldPosition[3];
	for(int i = 0; i < 3; i++)
	{
		heading[i] = oldDirection[i]= ray->direction[i];
		oldPosition[i] = ray->position[i];
	}
	Util::doRotation(heading, Util::PI, normal);
	for(int i = 0; i < 3; i++)
	{
		ray->direction[i] = -heading[i];
		ray->position[i] = p[i];
	}
	ray->cast(environment, reflections - 1, uid, coeff * mat_specular[3]);

	for(int i = 0; i < 3; i++)
	{
		ray->position[i] = oldPosition[i];
		ray->direction[i] = oldDirection[i];
	}
}

Sphere::Sphere(float p[], float ambient_diffuse[], float specular [], float r, Environment *env) {
	for (int i = 0; i < 3; i++) {
		position[i] = p[i];
	}
	for(int i = 0; i < 4; i++)
	{
		mat_ambient_diffuse[i] = ambient_diffuse[i];
		mat_specular[i] = specular[i];
	}
	radius = r;
	environment = env;
	uid = VisibleObj::nextUID++;
}

Sphere::Sphere(Environment *e){
	environment = e;
	uid = VisibleObj::nextUID++;
}


void Sphere::readAdditional(std::istream &in)
{
	for(int i = 0; i < 3; i++)
		in >> position[i];
	in >> radius;
}

void Sphere::appendAdditional(std::ostream &out)
{
	for(int i = 0; i < 3; i++)
		out << position[i] << " ";
	out << radius << " ";
}

void Sphere::applyTransformation()
{
	Util::transform(position);
}
