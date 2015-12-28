#include "Ray.h"
#include "Util.h"
#include <math.h>

void Ray::resetColor() {
	for (int i = 0; i < 3; ++i)
		color[i] = 0;
}

void Ray::cast(Environment *env, int reflections, int sourceId, float coeff) {
	if (reflections < 0 || coeff == 0)
		return;

	float depth = Util::inf;
	VisibleObj *nearest = 0;
	for (int i = 0; i < env->o; i++) {
		VisibleObj *obj = env->objects[i];
		if (sourceId != obj->uid) {
			float d = obj->intersects(this);
			if (d > 0 && d < depth) {
				nearest = obj;
				depth = d;
			}
		}
	}
	if (nearest)
	{
//		for(int i = 0; i < 3; i++)
//			color[i] *= (1 - coeff);
		nearest->doCollision(this, reflections, coeff * fogFactor(depth));
	}
}

Ray::Ray(float p[], float d[]) {
	for (int i = 0; i < 3; ++i) {
		position[i] = p[i];
		direction[i] = d[i];
	}
}

float Ray::fogFactor(float distance)
{
	float res = distance - fogNear;
	res /= fogFar - fogNear;
	if(res < 0)
		res = 0;
	else if(res > 1)
		res = 1;

	return 1 - res;
}
