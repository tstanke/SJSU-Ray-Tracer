/*
 * Pixel.cpp
 *
 *  Created on: Dec 16, 2008
 *      Author: tim
 */

#include "Pixel.h"
#include "Util.h"
#include <math.h>

Pixel::Pixel() {
}

void Pixel::calculate(Environment *env, int reflections) {
	for (int i = 0; i < 3; i++)
		color[i] = 0;
	for (unsigned int i = 0; i < rays.size(); i++) {
		rays[i]->resetColor();
		rays[i]->cast(env, reflections, -1, 1);
		for (int j = 0; j < 3; j++)
			color[j] += rays[i]->color[j];
	}
	for (int i = 0; i < 3; i++)
		color[i] /= rays.size();
}

Pixel::~Pixel() {
	while (rays.size() > 0) {
		delete rays[rays.size() - 1];
		rays.pop_back();
	}
}
