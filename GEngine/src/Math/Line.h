#pragma once
#include "Vector3f.h"

class Line
{
public:
	Vector3f P;
	Vector3f L;

	Line(const Vector3f& A, const Vector3f& B);
};

inline Line::Line(const Vector3f& A, const Vector3f& B)
{
	P = A;
	L = B - A;
}
