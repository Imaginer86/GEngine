#pragma once
#include <iostream>

class Color4f
{
public:
	Color4f():r(0.05f), g(0.5f), b(0.5f), a(1.0f) {}
	Color4f(float r_, float g_, float b_, float a_) :r(r_), g(g_), b(b_), a(a_) {}
	float r, g, b, a;
};

inline std::istream& operator>> (std::istream& is, Color4f& c)
{
	is >> c.r >> c.g >> c.b >> c.a;
	return is;
}



inline std::ostream& operator<< (std::ostream& os, const Color4f& c)
{
	os << c.r << " " << c.g << " " << c.b << " " << c.a << std::endl;
	return os;
}
