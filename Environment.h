/*
 * Environment.h
 *
 *  Created on: Dec 15, 2008
 *      Author: tim
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include "VisibleObj.h"
#include "Light.h"
#include <vector>

//class Light;
//class VisibleObj;

class Environment {
public:
	int o, l;
	VisibleObj *objects[100];
	Light *lights[100];
	void add(VisibleObj *obj);
	void add(Light *light);
	void load();
	void save();
	~Environment();
};

#endif /* ENVIRONMENT_H_ */
