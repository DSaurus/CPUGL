#pragma once

struct Point {
	double x, y, z;
	Point() {
		x = y = z = 0;
	}
	Point(double _x, double _y, double _z) :x(_x), y(_y), z(_z) {

	}
	Point(Point &B) {
		x = B.x; y = B.y; z = B.z;
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
