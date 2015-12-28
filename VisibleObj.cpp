/*
 * VisibleObj.cpp
 *
 *  Created on: Dec 22, 2008
 *      Author: tim
 */

#include "VisibleObj.h"
#include "Sphere.h"
#include "Polygon.h"
#include "ClearSphere.h"

void VisibleObj::writeTo(std::ostream &out) {
	out << "visibleobj ";
	out << getName() << " ";
	for(int i = 0; i < 4; i++)
		out << mat_ambient_diffuse[i] << " ";
	for(int i = 0; i < 4; i++)
		out << mat_specular[i] << " ";
	appendAdditional(out);
	out<<"\n";
}

void VisibleObj::readGeneralData(std::istream &in)
{
	for(int i = 0; i < 4; i++)
		in >> mat_ambient_diffuse[i];
	for(int i = 0; i < 4; i++)
		in >> mat_specular[i];
}


void VisibleObj::readFrom(std::istream &in, Environment *e){
	std::string type;
	in >> type;
	if(type == "sphere")
	{
		Sphere *sphere = new Sphere(e);
		sphere->readGeneralData(in);
		sphere->readAdditional(in);
		e->add(sphere);
	}
	else if(type == "polygon")
	{
		Polygon *polygon = new Polygon(e);
		polygon->readGeneralData(in);
		polygon->readAdditional(in);
		e->add(polygon);
	}
	else if(type == "clearsphere")
	{
		ClearSphere *cs = new ClearSphere(e);
		cs->readGeneralData(in);
		cs->readAdditional(in);
		e->add(cs);
	}
}
