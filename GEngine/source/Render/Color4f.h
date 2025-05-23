#pragma once
#ifdef _DEBUG
#include <iostream>
#else
#include <fstream>
#endif // _DEBUG

struct Color4f
{
	Color4f():r(0.05f), g(0.5f), b(0.5f), a(1.0f) {}
	Color4f(float r_, float g_, float b_, float a_) :r(r_), g(g_), b(b_), a(a_) {}
	float r, g, b, a;
};


#ifdef _DEBUG
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
#else
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
#endif // _DEBUG
