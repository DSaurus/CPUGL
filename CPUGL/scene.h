#pragma once

#include <vector>
#include "camera.h"
#include "object.h"
#include "light.h"

struct Scene {
	Camera camera;
	std::vector<Light> lights;
	std::vector<Object> objects;
	void rend();
};
