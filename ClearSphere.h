/*
 * ClearSphere.h
 *
 *  Created on: Dec 28, 2008
 *      Author: tim
 */

#ifndef CLEARSPHERE_H_
#define CLEARSPHERE_H_

#include "Ray.h"
#include "Sphere.h"
#include <string>

class ClearSphere : public Sphere{
public:

	inline std::string getName() {return "clearsphere";};
	void doCollision(Ray* ray, int reflections, float coeff);
	ClearSphere(float p[], float ambient_diffuse[], float specular [], float r, Environment *env);
	ClearSphere(Environment *e);

private:
	void in(Ray *ray, int reflections, float coeff);
	void out(Ray *ray, int reflections, float coeff);
};


#endif /* CLEARSPHERE_H_ */
