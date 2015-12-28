/*
 * ClearSphere.cpp
 *
 *  Created on: Dec 28, 2008
 *      Author: tim
 */

#include "ClearSphere.h"
#include "Util.h"
#include <math.h>


void ClearSphere::in(Ray *ray, int reflections, float coeff)
{
	float d = intersects(ray);
	float p [3];
	for(int i = 0; i < 3; i++)
		p[i] = ray->position[i] + d * ray->direction[i];

	float normal [3];
	for(int i = 0; i < 3; i++)
		normal[i] = p[i] - position[i];
	Util::normalize(normal);

	// "invert the normal to face inward
	for(int i = 0; i < 3; i++)
		normal[i] = -normal[i];

	// cross holds a vector orthogonal to normal and to the ray direction.
	// we need to rotate the ray about cross.
	float cross[3];
	Util::cross(cross, ray->direction, normal);
	Util::normalize(cross);

	float oldPosition[3];
	float oldDirection[3];
	Util::copy(oldPosition, ray->position, 3);
	Util::copy(oldDirection, ray->direction, 3);

	float angleBetweenNormalAndRay = acos(Util::dot(normal, ray->direction));
	float newAngle = angleBetweenNormalAndRay / 1.1;
	float change = angleBetweenNormalAndRay - newAngle;
	Util::doRotation(ray->direction, change, cross);

	Util::copy(ray->position, p, 3);

	out(ray, reflections, coeff);

	Util::copy(ray->position, oldPosition, 3);
	Util::copy(ray->direction, oldDirection, 3);
}

void ClearSphere::out(Ray *ray, int reflections, float coeff)
{
	float c[3];
	for (int i = 0; i < 3; i++)
		c[i] = position[i] - ray->position[i];

	float lDotC = Util::dot(ray->direction, c);
	float toSqrt = Util::sq(lDotC) - Util::dot(c, c) + Util::sq(radius);

	float mysqrt = sqrt(toSqrt);
	float d1 = lDotC + mysqrt;
	float d2 = lDotC - mysqrt;

	float d = std::max(d1, d2);

	float p [3];
	for(int i = 0; i < 3; i++)
		p[i] = ray->position[i] + d * ray->direction[i];

	float normal [3];
	for(int i = 0; i < 3; i++)
		normal[i] = p[i] - position[i];
	Util::normalize(normal);

	// cross holds a vector orthogonal to normal and to the ray direction.
	// we need to rotate the ray about cross.
	float cross[3];
	Util::cross(cross, ray->direction, normal);
	Util::normalize(cross);

	float oldPosition[3];
	float oldDirection[3];
	Util::copy(oldPosition, ray->position, 3);
	Util::copy(oldDirection, ray->direction, 3);

	float angleBetweenNormalAndRay = acos(Util::dot(normal, ray->direction));
	float newAngle = angleBetweenNormalAndRay * 1.1;
	float change = newAngle - angleBetweenNormalAndRay;
	Util::doRotation(ray->direction, -change, cross);

	Util::copy(ray->position, p, 3);

	ray->cast(environment, reflections, uid, coeff);

	Util::copy(ray->position, oldPosition, 3);
	Util::copy(ray->direction, oldDirection, 3);
}



void ClearSphere::doCollision(Ray* ray, int reflections, float coeff) {
	in(ray, reflections - 1, coeff * (1 - mat_specular[3]));
	doReflectiveCollision(ray, reflections, coeff * mat_specular[3]);
}

ClearSphere::ClearSphere(float p[], float ambient_diffuse[], float specular [], float r, Environment *env) :Sphere(p, ambient_diffuse, specular, r, env){
}

ClearSphere::ClearSphere(Environment *e) :Sphere(e){
}
