#pragma once
#include "Vector3f.h"
#include "Line.h"
#include "gmath.h"

class Plane
{
public:
	float A, B, C, D;

	Plane(float a, float b, float c, float d) :A(a), B(b), C(c), D(d) {}
	Plane(const Vector3f& N, float D);
	Plane(const Vector3f&, const Vector3f&, const Vector3f&);
	Vector3f unit();
	float distance(const Vector3f& p);

	Line operator* (const Plane& P);
	Vector3f operator* (const Line& L);

};

inline Vector3f Plane::unit()
{
	float length = sqrt(A*A + B*B + C*C);

	if (length == 0)
		return Vector3f();

	return Vector3f(A / length, B / length, C / length);
}

inline float Plane::distance(const Vector3f& p)
{
	float length = sqrt(A*A + B*B + C*C);
	if (length)
		return (A*p.x + B*p.y + C*p.z + D) / length;
	else
		return 0.0f;
}

inline Line Plane::operator*(const Plane& P)
{
	float d = A * P.B - B * P.A;
	float lambda = 2;//!!!
	float dx = (-D - C * lambda)*P.B - B * (-P.D - P.C*lambda);
	float dy = A * (-P.D - P.C * lambda) - (-D - C * lambda) * P.A;
	float x = dx / d;
	float y = dy / d;
	float z = lambda;
	Vector3f PL(x, y, z);
	Vector3f N = Vector3f(A, B, C) * Vector3f(P.A, P.B, P.C);
	Vector3f P1 = PL + N;
	Line L(PL, P1);
	return L;
}

inline Vector3f Plane::operator*(const Line& L)
{
	Vector3f N = unit();
	float d = -distance(L.P);
	float e = N.dotProduct(L.L);
	if (e)
		return L.P + L.L * (d / e);
	else
		return Vector3f(); //!!!
}

inline Plane::Plane(const Vector3f& N, float D)
	:A(N.x)
	,B(N.y)
	,C(N.z)
	,D(D)
{}

inline Plane::Plane(const Vector3f& p1, const Vector3f& p2, const Vector3f&p3)
{
	A = p1.y*(p2.z - p3.z) + p2.y*(p3.z - p1.z) + p3.y*(p1.z - p2.z);
	B = p1.z*(p2.x - p3.x) + p2.z*(p3.x - p1.x) + p3.z*(p1.x - p2.x);
	C = p1.x*(p2.y - p3.y) + p2.x*(p3.y - p1.y) + p3.x*(p1.y - p2.y);
	D = -p1.x*(p2.y*p3.z - p3.y*p2.z) - p2.x*(p3.y*p1.z - p1.y*p3.z) - p3.x*(p1.y*p2.z - p2.y*p1.z);
}