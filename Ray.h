#ifndef RAY_H_
#define RAY_H_

#include <vector.h>
#include "Light.h"
#include "VisibleObj.h"
#include "Environment.h"

//class Environment;

class Ray {
public:
	float position [3];
	float direction[3];
	float color[3];

	void resetColor();
	void cast(Environment *env, int reflections, int sourceId, float coeff);
	Ray(float p [], float d []);

	static float fogFactor(float distance);
	static const float fogNear = 0;
	static const float fogFar = 100000;
};

#endif /* RAY_H_ */
