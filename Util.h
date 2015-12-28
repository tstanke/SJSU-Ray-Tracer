/*
 * Util.h
 *
 *  Created on: Dec 15, 2008
 *      Author: tim
 */

#ifndef UTIL_H_
#define UTIL_H_

class Util {
public:

	static const float inf = 1e10;
	static const float PI = 3.14159265;
	static float dot(float a[], float b[]);
	static void normalize(float a[]);
	static inline float sq(float f){ return f * f;}
	static void doRotation(float point [], float angleRadians, float vector []);
	static void cross(float result [], float a[], float b[]);
	static float determinant(float a[], float b[]);
	static void difference(float result [], float a[], float b[]);
	static inline float min(float f1, float f2) { return (f1 < f2) ? f1 : f2; }
	static float dist(float p1 [], float p2 []);
	static float mag(float v[]);
	static void transform(float p[]);
	static void copy(float dest[], float src[], int sz);
	static void writeToFile(int w, int h, float mat[]);

};

#endif /* UTIL_H_ */
