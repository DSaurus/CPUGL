#pragma once
#include "math_basic.h"
#include <vector>

enum {
	SPHERE_OBJECT,
	MESH_OBJECT
};

struct Object {
	int object_type;
	int transparent;
	Object() {
		transparent = 0;
	}
	virtual Intersection get_intersection(Line ray) {
		Intersection t;
		return t;
	}
};

struct MeshObject : Object {
	std::vector<Point> verts;
	std::vector<Vector> normals;
	std::vector<Color> colors;
	std::vector<std::vector<int> > triangles;
	Intersection get_intersection(Line ray);
};

struct SphereObject : Object {
	Point o;
	double r;
	Color col;
	Intersection get_intersection(Line ray);
};
