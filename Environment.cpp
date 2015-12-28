/*
 * Environment.cpp
 *
 *  Created on: Dec 15, 2008
 *      Author: tim
 */

#include "Environment.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>
#include <sstream>
#include <time.h>
#include <string>

void Environment::load() {
	std::ifstream file;
	file.open("objects.sav");

	if (file.is_open()) {
		while (true) {
			std::string type;
			file >> type;

			if (type == "visibleobj")
				VisibleObj::readFrom(file, this);
			else if (type == "light") {
				Light *light = new Light(this);
				light->readFrom(file);
				add(light);
			} else {
				std::cout<<"no valid type found, terminating load.\n";
				break;
			}
		}

		file.close();
	}
}

void Environment::save() {
	std::ofstream file;
	file.open("objects.sav");
	for (int i = 0; i < o; i++) {
		objects[i]->writeTo(file);
	}
	for (int i = 0; i < l; i++) {
		lights[i]->writeTo(file);
	}
	file.close();
}

void Environment::add(VisibleObj *obj) {
	objects[o++] = obj;
	objects[o - 1]->applyTransformation();
}
void Environment::add(Light *light) {
	lights[l++] = light;
	lights[l - 1]->applyTransformation();
}

Environment::~Environment() {
	for (int i = 0; i < l; i++)
		delete lights[i];
	for (int i = 0; i < o; i++)
		delete objects[i];
}
