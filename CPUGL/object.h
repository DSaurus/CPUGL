#pragma once

enum {
	SPHERE_OBJECT,
	MESH_OBJECT
};

struct Object {
	int object_type;
	virtual Intersection get_intersection(Line ray) {}
};

struct MeshObject : Object {
	Intersection get_intersection(Line ray) {

	}
};
