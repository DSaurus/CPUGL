#include "pch.h"
#include "math_basic.h"

Vector get_normal(Point p1, Point p2, Point p3) {
	Vector normal = Vector((p2.y - p1.y)*(p3.z - p1.z) - (p3.y - p1.y)*(p2.z - p1.z),
		(p2.z - p1.z)*(p3.x - p1.x) - (p3.z - p1.z)*(p2.x - p1.x),
		(p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y));
	assert(normal*normal > 0);
	return normal / sqrt(normal*normal);
}

void get_interpolation(Vector v1, Vector v2, Vector v, double &a, double &b) {
	b = (v.x*v1.y - v1.x*v.y) / (v2.x*v1.y - v1.x*v2.y);
	a = (v.x*v2.y - v2.x*v.y) / (v1.x*v2.y - v2.x*v1.y);
}