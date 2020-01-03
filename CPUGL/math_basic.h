#pragma once

#include <assert.h>
#include <cmath>
#include <iostream>
#include <cstring>

struct Point {
	double x, y, z;
	Point() {
		x = y = z = 0;
	}
	Point(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {

	}
	Point(const Point &B) {
		x = B.x; y = B.y; z = B.z;
	}
	friend Point operator *(double c, Point B) {
		return B * c;
	}
	Point operator *(double c) {
		return Point(c*x, c*y, c*z);
	}
	double operator *(Point B) {
		return x * B.x + y * B.y + z * B.z;
	}

	Point operator /(double c) {
		return Point(x / c, y / c, z / c);
	}

	Point operator +(Point B) {
		return Point(x + B.x, y + B.y, z + B.z);
	}
	Point operator -(Point B) {
		return Point(x - B.x, y - B.y, z - B.z);
	}
	std::string str() {
		char res[100];
		sprintf_s(res, "x:%.4f y:%.4f z:%.4f", x, y, z);
		return res;
	}
};


typedef Point Vector;

struct Line {
	// line = o + tv
	Point o;
	Vector v;
	Line() {
		o = Point(0, 0, 0);
		v = Vector(0, 0, 1);
	}
	Line(Point _o, Vector _v) {
		o = _o;
		assert(_v*_v != 0);
		v = _v / sqrt(_v*_v);
	}
	std::string str() {
		char res[100];
		sprintf_s(res, "o x:%.4f y:%.4f z:%.4f\nv x:%.4f y:%.4f z:%.4f", o.x, o.y, o.z, v.x, v.y, v.z);
		return res;
	}
};

struct Triangle {
	Point o;
	Vector v1, v2;
};

struct Color {
	double r, g, b;
	Color() {
		r = g = b = 0;
	}
	Color(double _r, double _g, double _b) :r(_r), g(_g), b(_b) {

	}
	Color(const Color &B) {
		r = B.r; g = B.g; b = B.b;
	}
	Color operator +(Color B) {
		return Color(r + B.r, g + B.g, b + B.b);
	}
	Color operator *(double t) {
		return Color(r*t, g*t, b*t);
	}
};

struct Intersection {
	Point o;
	Color col;
	Vector n;
	double ray_depth;
	Intersection() {
		ray_depth = 1e9;
		n = Vector(0, 0, 1);
	}
	Intersection(const Intersection &B) {
		o = B.o;
		col = B.col;
		n = B.n;
		ray_depth = B.ray_depth;
	}
};
