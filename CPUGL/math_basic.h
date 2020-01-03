#pragma once

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
	Point operator +(Point B) {
		return Point(x + B.x, y + B.y, z + B.z);
	}
	Point operator -(Point B) {
		return Point(x - B.x, y - B.y, z - B.z);
	}
};


typedef Point Vector;

struct Line {
	// line = o + tv
	Point o;
	Vector v;
	Line() {
		o = Point(0, 0, 0);
		v = Vector(0, 0, 0);
	}
	Line(Point _o, Vector _v) {
		o = _o;
		v = _v;
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
};

struct Intersection {
	Point o;
	Color col;
	Vector n;
	double ray_depth;
};
