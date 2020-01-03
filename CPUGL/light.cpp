#include "pch.h"
#include "light.h"

Vector reflect_light(Vector ray, Vector normal) {
	assert(normal*normal > 0);
	normal = normal / sqrt(normal*normal);
	return ray - 2 * (ray*normal)*normal;
}

Color Light::phone_shading(Intersection inter, Line ray, double diffuse, double specular, double phone) {
	Color col;
	Vector l_v = o - inter.o;
	if (l_v*inter.n < 0) return col;
	col = inter.col*(diffuse * l_v*inter.n / sqrt(l_v*l_v) / sqrt(inter.n*inter.n));
	Vector r_l_v = reflect_light(l_v, inter.n);
	if (r_l_v*ray.v < 0) return col;
	col =  col + inter.col*(specular* pow(r_l_v*ray.v, phone) / (l_v*inter.n));
	return col;
}