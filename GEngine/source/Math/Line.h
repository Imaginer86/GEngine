#pragma once
#include "Vector3f.h"

struct Line
{
	Vector3f P;
	Vector3f L;
	Line() {}
	Line(const Vector3f& A, const Vector3f& B);

	Vector3f Lymbda(float l) const;
};

inline Line::Line(const Vector3f& A, const Vector3f& B)
{
	P = A;
	L = B - A;
}

inline Vector3f Line::Lymbda(float l) const
{
	return P + L * l;
}
