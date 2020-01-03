#include "pch.h"
#include "camera.h"

void Camera::getRays(std::vector<Line> &rays, int width, int height) {
	/*
		0 -- 1
		|
		2
	*/
	double w_i = 1.0 / width, h_i = 1.0 / height;
	for (double a = 0; a < 1; a += w_i) {
		for (double b = 0; b < 1; b += h_i) {
			Point p = a * tri.v1 + b * tri.v2 + tri.o;
			rays.push_back(Line(o, p - o));
		}
	}
}