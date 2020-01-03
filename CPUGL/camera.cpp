#include "pch.h"
#include "camera.h"

void Camera::getRays(std::vector<Line> &rays) {
	double interval = 0.01;
	for (double a = 0; a <= 1; a += interval) {
		for (double b = 0; b <= 1; b += interval) {
			Point p = a * tri.v1 + b * tri.v2 + tri.o;
			rays.push_back(Line(o, p - o));
		}
	}
}