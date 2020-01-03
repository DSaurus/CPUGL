#include "pch.h"
#include "object.h"
#include "math_basic.h"

Intersection MeshObject::get_intersection(Line ray) {
	Intersection res;
	for (auto tri : triangles) {
		Point p[3];
		p[0] = verts[tri[0]];
		p[1] = verts[tri[1]];
		p[2] = verts[tri[2]];
		Vector n = get_normal(p[0], p[1], p[2]);
		double D = -1*n * p[0];
		double ray_depth = -(D + n * ray.o) / (n*ray.v);
		if (ray_depth < 0) continue;
		if (ray_depth > res.ray_depth) continue;

		Point inter = ray.o + ray.v*ray_depth;
		double a, b;
		get_interpolation(p[1] - p[0], p[2] - p[0], inter - p[0], a, b);
		if (a < 0 || b < 0 || a+b > 1) continue;

		/*std::cout << "#" << ray.o.str().c_str() << std::endl;
		std::cout << "@" << (ray.v*ray_depth).str().c_str() << std::endl;
		std::cout << a << " " << b << std::endl;
		std::cout << inter.str().c_str() << std::endl;*/

		res.ray_depth = ray_depth;
		res.o = inter;
		res.n = n;
		res.col = (colors[tri[1]] - colors[tri[0]])*a + (colors[tri[2]] - colors[tri[0]])*b + colors[tri[0]];
	}
	return res;
}

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