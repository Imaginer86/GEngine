#pragma once
#include "Vector3f.h"
#include "Line.h"
#include "GMath.h"

struct Plane
{
	float A, B, C, D;

	Plane();
	Plane(float a, float b, float c, float d);
	Plane(const Vector3f& N, float d);
	Plane(const Vector3f&, const Vector3f&, const Vector3f&);
	Vector3f unit();
	float distance(const Vector3f& p);

	Vector3f proj(const Vector3f& a)
	{
		Line L;
		L.P = a;
		L.L = unit();
		return *this * L;
	}
	

	Line operator* (const Plane& P);
	Vector3f operator* (const Line& L);
	Vector3f operator*(const Vector3f& v);

};

inline Plane::Plane() :A(0.0f), B(0.0f), C(0.0f), D(0.0f) {}
inline Plane::Plane(float a, float b, float c, float d) :D(d)
{
	Vector3f N(a, b, c);
	N.unitize();
	A = N.x;
	B = N.y;
	C = N.z;
}

inline Plane::Plane(const Vector3f& N, float d) :D(d)
{
	Vector3f NP(N.x, N.y, N.z);
	NP.unitize();
	A = NP.x;
	B = NP.y;
	C = NP.z;
}

inline Plane::Plane(const Vector3f& p1, const Vector3f& p2, const Vector3f& p3)
{
	A = p1.y * (p2.z - p3.z) + p2.y * (p3.z - p1.z) + p3.y * (p1.z - p2.z);
	B = p1.z * (p2.x - p3.x) + p2.z * (p3.x - p1.x) + p3.z * (p1.x - p2.x);
	C = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
	D = -p1.x * (p2.y * p3.z - p3.y * p2.z) - p2.x * (p3.y * p1.z - p1.y * p3.z) - p3.x * (p1.y * p2.z - p2.y * p1.z);
}

inline Vector3f Plane::unit()
{
	float length = sqrt(A*A + B*B + C*C);

	if (isNotZero(length))
		return Vector3f(A / length, B / length, C / length);
	else
		return Vector3f();	
}

inline float Plane::distance(const Vector3f& p)
{
	float length = sqrt(A*A + B*B + C*C);
	if (isNotZero(length))
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
	if (isNotZero(e))
		return L.P + L.L * (d / e);
	else
		return Vector3f(); //!!!
}

inline Vector3f Plane::operator*(const Vector3f& v)
{
	Vector3f n = unit();
	Line l(v, v + n);
	return *this * l;
}