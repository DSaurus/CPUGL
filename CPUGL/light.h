#pragma once
#include "math_basic.h"

void reflect_light(Line ray, Line normal);

struct Light {
	Point o;
	Color phone_shading(Intersection inter, Line ray, double diffuse, double specular, double phone);
};