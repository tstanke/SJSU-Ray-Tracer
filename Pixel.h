/*
 * Pixel.h
 *
 *  Created on: Dec 16, 2008
 *      Author: tim
 */

#ifndef PIXEL_H_
#define PIXEL_H_

#include "Ray.h"

class Pixel {
public:
	vector<Ray*> rays;
	Pixel();
	float color [3];
	void calculate(Environment *env, int reflections);
	~Pixel();
};

#endif /* PIXEL_H_ */
