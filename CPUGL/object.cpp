#include "pch.h"
#include "object.h"
#include "math_basic.h"

Intersection SphereObject::get_intersection(Line ray) {
	Point c = o;
	Point o = ray.o;
	Vector v = ray.v;

	Intersection res;

	// t*t + 2*t*(v*(o-c)) + (o-c)*(o-c)-r*r = 0
	double B = v * (o - c);
	double C = (o - c)*(o - c) - r * r;
	if (B*B - C < 0) {
		return res;
	}
	double t;
	double t1 = -B - sqrt(B*B - C);
	double t2 = -B + sqrt(B*B - C);
	
	if (t1 < 0) t = t2;
	else t = t1;

	Point inter = o + t * v;
	Vector normal = inter - c;
	assert(normal*normal > 0);
	normal = normal / sqrt(normal*normal);

	res.col = col;
	res.o = inter;
	res.n = normal;
	res.ray_depth = t;
	return res;
}