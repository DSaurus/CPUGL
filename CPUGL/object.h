#pragma once
#include "math_basic.h"

enum {
	SPHERE_OBJECT,
	MESH_OBJECT
};

struct Object {
	int object_type;
	virtual Intersection get_intersection(Line ray) {
		Intersection t;
		return t;
	}
};

struct MeshObject : Object {
	Intersection get_intersection(Line ray) {}
};

struct SphereObject : Object {
	Point o;
	double r;
	Color col;
	Intersection get_intersection(Line ray);
};
