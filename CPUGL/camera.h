#pragma once

#include "math_basic.h"
#include <vector>

struct Camera {
	Point o;
	Triangle tri;
	void getRays(std::vector<Line> &rays);
};