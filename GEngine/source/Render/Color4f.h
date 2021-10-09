#pragma once

class Color4f
{
public:
	Color4f():r(0.05f), g(0.5f), b(0.5f), a(1.0f) {}
	Color4f(float r_, float g_, float b_, float a_) :r(r_), g(g_), b(b_), a(a_) {}
	float r, g, b, a;
};
