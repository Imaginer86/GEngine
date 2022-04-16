#pragma once
#include <iostream>
struct Vector4f
{
	float v[4];
	Vector4f() {v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 0.0f; }
	Vector4f(float x_, float y_, float z_, float w_)		 {v[0] = x_; v[1] = y_; v[2] = z_; v[3] = w_; }
	~Vector4f(){}
};

inline std::istream& operator>> (std::istream& is, Vector4f& v)
{
	is >> v.v[0] >> v.v[1] >> v.v[2] >> v.v[3];
	return is;
}



inline std::ostream& operator<< (std::ostream& os, const Vector4f& v)
{
	os << v.v[0] << " " << v.v[1] << " " << v.v[2] << " " << v.v[3] << std::endl;
	return os;
}