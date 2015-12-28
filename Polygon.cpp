/*
 * Polygon.cpp
 *
 *  Created on: Dec 16, 2008
 *      Author: tim
 */

#include "Polygon.h"
#include "Util.h"
#include "Ray.h"
#include <math.h>

Polygon::Polygon(float x[], float y[], float z[], int numVertices,
		float ambient_diffuse[], float specular[], float checkersz,
		Environment *env) {
	n = numVertices;
	for (int i = 0; i < n; i++) {
		pos[i][0] = x[i];
		pos[i][1] = y[i];
		pos[i][2] = z[i];
	}

	for (int i = 0; i < 4; i++) {
		mat_ambient_diffuse[i] = ambient_diffuse[i];
		mat_specular[i] = specular[i];
	}

	environment = env;
	checkerSize = checkersz;

	recalculateNormal();

	uid = VisibleObj::nextUID++;
}

void Polygon::recalculateNormal() {

	float v1[3];
	float v2[3];
	Util::difference(v1, pos[1], pos[0]);
	Util::difference(v2, pos[2], pos[1]);
	Util::cross(normal, v1, v2);
	Util::normalize(normal);
}

Polygon::Polygon(Environment * e) {
	environment = e;
	uid = VisibleObj::nextUID++;
}

float Polygon::intersects(Ray* ray) {
	float d = Util::dot(pos[0], normal);
	float iaDotN = Util::dot(ray->position, normal);
	float dirDotN = Util::dot(ray->direction, normal);

	if (dirDotN == 0)
		return -1;

	float dist = (d - iaDotN) / dirDotN;

	float p[3];
	for (int i = 0; i < 3; i++)
		p[i] = ray->position[i] + dist * ray->direction[i];

	for (int i = 1; i <= n; i++) {
		float v1[3];
		float v2[3];
		Util::difference(v1, pos[i % n], pos[i - 1]);
		Util::difference(v2, p, pos[i % n]);
		float cross[3];
		Util::cross(cross, v1, v2);
		Util::normalize(cross);
		float cosAngle = Util::dot(cross, normal);
		if (cosAngle < 0)
			return -1;
	}

	return dist;
}

void Polygon::doCollision(Ray* ray, int reflections, float coeff) {
	float d = intersects(ray);
	//	std::cout<<"Distance: "<<d<<"\n";
	float p[3];
	for (int i = 0; i < 3; i++)
		p[i] = ray->position[i] + d * ray->direction[i];

	//	float normal [3];
	//	for(int i = 0; i < 3; i++)
	//		normal[i] = p[i] - position[i];
	//	Util::normalize(normal);
	float pointDiffuse[4];
	float pointSpecular[4];
	Util::copy(pointDiffuse, mat_ambient_diffuse, 4);
	Util::copy(pointSpecular, mat_specular, 4);

	if (checkerSize) {

		float vp[3];
		float vx[3];
		float vy[3];
		Util::difference(vp, p, pos[0]);
		Util::difference(vx, pos[1], pos[0]);
		Util::difference(vy, pos[2], pos[1]);
		float x = Util::dot(vp, vx) / Util::mag(vx);
		float y = Util::dot(vp, vy) / Util::mag(vy);

		float white[] = { 1, 1, 1, 1 };
		float black[] = { 0, 0, 0, mat_specular[3] };
		if (((int) round(x) % 100 < 50) ^ ((int) round(y) % 100 < 50)) {
			Util::copy(pointDiffuse, white, 4);
			Util::copy(pointSpecular, black, 4);
		}
	}

	for (int i = 0; i < environment->l; i++) {
		environment->lights[i]->apply(ray->color, p, ray->position, normal,
				pointDiffuse, pointSpecular, coeff, uid);
	}

	float heading[3];
	float oldDirection[3];
	float oldPosition[3];
	for (int i = 0; i < 3; i++) {
		heading[i] = oldDirection[i] = ray->direction[i];
		oldPosition[i] = ray->position[i];
	}
	Util::doRotation(heading, Util::PI, normal);
	for (int i = 0; i < 3; i++) {
		ray->direction[i] = -heading[i];
		ray->position[i] = p[i];
	}
	ray->cast(environment, reflections - 1, uid, coeff * mat_specular[3]);

	for (int i = 0; i < 3; i++) {
		ray->position[i] = oldPosition[i];
		ray->direction[i] = oldDirection[i];
	}

}

void Polygon::readAdditional(std::istream &in) {
	in >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
			in >> pos[i][j];
	for (int i = 0; i < 3; i++)
		in >> normal[i];
	in >> checkerSize;
}

void Polygon::appendAdditional(std::ostream &out) {
	out << n << " ";
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 3; j++)
			out << pos[i][j] << " ";
	for (int i = 0; i < 3; i++)
		out << normal[i] << " ";
	out << checkerSize << " ";
}

void Polygon::applyTransformation() {
	for (int i = 0; i < n; i++)
		Util::transform(pos[i]);
	recalculateNormal();
}
