#pragma once
#include "GMath.h"
#include "Vector3f.h"

#ifdef _DEBUG
#include <iostream>
#else
#include <fstream>
#endif // _DEBUG

struct Quaternion
{
	float w, x, y, z;

	Quaternion():w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
	Quaternion(float w_, float x_, float y_, float z_) : w(w_), x(x_), y(y_), z(z_) {}
	Quaternion(float angle, const Vector3f& axis)
	{
		Vector3f naxis = axis;
		naxis.unitize();
		float halfTheta = angle / 2.0f;
		halfTheta = degToRad(halfTheta);
		float s = sinf(halfTheta);
		w = cosf(halfTheta), x = axis.x * s, y = axis.y * s, z = axis.z * s;
	}
	// Explicitly define the copy constructor
	Quaternion(const Quaternion& other) : w(other.w), x(other.x), y(other.y), z(other.z) {}

	// Explicitly define the copy assignment operator
	Quaternion& operator=(const Quaternion& other)
	{
		if (this != &other)
		{
			w = other.w;
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}
	~Quaternion() {}

	bool operator==(const Quaternion& rhs) const;
	bool operator!=(const Quaternion& rhs) const;

	Quaternion &operator+=(const Quaternion& rhs);
	Quaternion &operator-=(const Quaternion& rhs);
	Quaternion &operator*=(const Quaternion& rhs);
	Quaternion &operator*=(const Vector3f& vec);
	Quaternion &operator*=(float scalar);
	Quaternion &operator/=(float scalar);

	Quaternion operator+(const Quaternion& rhs) const;
	Quaternion operator-(const Quaternion& rhs) const;
	Quaternion operator*(const Quaternion& rhs) const;
	Quaternion operator*(const Vector3f& vec) const;
	Quaternion operator*(float scalar) const;
	Quaternion operator/(float scalar) const;

	bool isReal() const;
	bool isZero() const;

	Quaternion conjugate() const;

	void normalize();

	Vector3f Normal(const Vector3f& p) const;

	
	void fromAngleXYZ(const Vector3f& angle);
	void identity();
	Quaternion inverse() const;
	float magnitude() const;
	
	void fromAngleAxis(float angle, const Vector3f& axis);
	void toAngleAxis(float &angle, Vector3f& axis) const;
	Vector3f GetAxis() const;
	float GetAngle() const;

	Vector3f rotate(const Vector3f& v) const;

	//void toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const;
	//atrix4 toMatrix4() const;
	
	//void rotate(Vector3 &v) const;
	//void fromMatrix(const Matrix4 &m);
	//void fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees);
};

//const Quaternion QIDENTITY(1.0f, 0.0f, 0.0f, 0.0f);

#ifdef _DEBUG
inline std::istream& operator>> (std::istream& is, Quaternion& q)
{
	float angle;
	Vector3f axic;
	is >> angle >> axic;
	q.fromAngleAxis(angle, axic);
	return is;
}

inline std::ostream& operator<< (std::ostream& os, const Quaternion& q)
{
	float angle;
	Vector3f axic;
	q.toAngleAxis(angle, axic);
	os << angle << ": " << axic;
	return os;
}
#else
inline std::istream& operator>> (std::istream& is, Quaternion& q)
{
	float angle;
	Vector3f axic;
	is >> angle >> axic;
	q.fromAngleAxis(angle, axic);
	return is;
}

inline std::ostream& operator<< (std::ostream& os, const Quaternion& q)
{
	float angle;
	Vector3f axic;
	q.toAngleAxis(angle, axic);
	os << angle << ": " << axic;
	return os;
}
#endif // _DEBUG


inline Quaternion operator*(float lhs, const Quaternion &rhs)
{
	return rhs * lhs;
}

inline Quaternion operator*(Quaternion &q1, const Quaternion &q2)
{
	return q1.operator*(q2);
}

inline bool Quaternion::operator==(const Quaternion &rhs) const
{
	return ::isEqual(w, rhs.w) && ::isEqual(x, rhs.x)
		&& ::isEqual(y, rhs.y) && ::isEqual(z, rhs.z);
}

inline bool Quaternion::operator!=(const Quaternion &rhs) const
{
	return !(*this == rhs);
}

inline Quaternion &Quaternion::operator+=(const Quaternion &rhs)
{
	w += rhs.w, x += rhs.x, y += rhs.y, z += rhs.z;
	return *this;
}

inline Quaternion &Quaternion::operator-=(const Quaternion &rhs)
{
	w -= rhs.w, x -= rhs.x, y -= rhs.y, z -= rhs.z;
	return *this;
}

inline Quaternion &Quaternion::operator*=(const Quaternion &rhs)
{
	// Multiply so that rotations are applied in a left to right order.
	Quaternion tmp(
		(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
		(w * rhs.x) + (x * rhs.w) - (y * rhs.z) + (z * rhs.y),
		(w * rhs.y) + (x * rhs.z) + (y * rhs.w) - (z * rhs.x),
		(w * rhs.z) - (x * rhs.y) + (y * rhs.x) + (z * rhs.w));

	/*
	// Multiply so that rotations are applied in a right to left order.
	Quaternion tmp(
	(w * rhs.w) - (x * rhs.x) - (y * rhs.y) - (z * rhs.z),
	(w * rhs.x) + (x * rhs.w) + (y * rhs.z) - (z * rhs.y),
	(w * rhs.y) - (x * rhs.z) + (y * rhs.w) + (z * rhs.x),
	(w * rhs.z) + (x * rhs.y) - (y * rhs.x) + (z * rhs.w));
	*/

	*this = tmp;
	return *this;
}

inline Quaternion &Quaternion::operator*=(const Vector3f &v)
{
	Quaternion tmp(
		-(x * v.x) - (y * v.y) - (z * v.z),
		(w * v.x) + (y * v.z) - (z * v.y),
		(w * v.y) + (z * v.x) - (x * v.z),
		(w * v.z) + (x * v.y) - (y * v.x));	
	*this = tmp;
	return *this;
}

inline Quaternion &Quaternion::operator*=(float scalar)
{
	w *= scalar, x *= scalar, y *= scalar, z *= scalar;
	return *this;
}

inline Quaternion &Quaternion::operator/=(float scalar)
{
	w /= scalar, x /= scalar, y /= scalar, z /= scalar;
	return *this;
}

inline Quaternion Quaternion::operator+(const Quaternion &rhs) const
{
	Quaternion tmp(*this);
	tmp += rhs;
	return tmp;
}

inline Quaternion Quaternion::operator-(const Quaternion &rhs) const
{
	Quaternion tmp(*this);
	tmp -= rhs;
	return tmp;
}

inline Quaternion Quaternion::operator*(const Quaternion &rhs) const
{
	Quaternion tmp(*this);
	tmp *= rhs;
	return tmp;
}

inline Quaternion Quaternion::operator*(const Vector3f &vec) const
{
	Quaternion tmp(*this);
	tmp *= vec;
	return tmp;
}

inline Quaternion Quaternion::operator*(float scalar) const
{
	Quaternion tmp(*this);
	tmp *= scalar;
	return tmp;
}

inline Quaternion Quaternion::operator/(float scalar) const
{
	Quaternion tmp(*this);
	tmp /= scalar;
	return tmp;
}

inline bool Quaternion::isReal() const
{
	return ::isZero(x) && ::isZero(y) && ::isZero(z);
}

inline bool Quaternion::isZero() const
{
	return ::isZero(w);
}

inline Quaternion Quaternion::conjugate() const
{
	Quaternion tmp(w, -x, -y, -z);
	return tmp;
}

inline void Quaternion::fromAngleXYZ(const Vector3f &angle)
{
	Vector3f vx(1, 0, 0), vy(0, 1, 0), vz(0, 0, 1);
	Quaternion qx, qy, qz, qt;

	qx.fromAngleAxis(angle.x, vx);
	qy.fromAngleAxis(angle.y, vy);
	qz.fromAngleAxis(angle.z, vz);
	qt = qx*qy*qz;
	w = qt.w;
	x = qt.x;
	y = qt.y;
	z = qt.z;
	this->normalize();
}


inline void Quaternion::identity()
{
	w = 1.0f, x = y = z = 0.0f;
}

inline Quaternion Quaternion::inverse() const
{
	float invMag = 1.0f / magnitude();
	return conjugate() * invMag;
}

inline float Quaternion::magnitude() const
{
	return sqrt(w * w + x * x + y * y + z * z);
}

inline void Quaternion::normalize()
{
	float invMag = 1.0f / magnitude();
	w *= invMag, x *= invMag, y *= invMag, z *= invMag;
}


inline void Quaternion::toAngleAxis(float &angle, Vector3f &axis) const
{
	// Converts this quaternion to an axis and an angle.

	float sinHalfThetaSq = 1.0f - w * w;

	// Guard against numerical imprecision and identity quaternions.

	float invSinHalfTheta = 1.0f / sqrt(sinHalfThetaSq);
	axis.x = x * invSinHalfTheta;
	axis.y = y * invSinHalfTheta;
	axis.z = z * invSinHalfTheta;
	angle = 2.0f * atan2f(sqrt(sinHalfThetaSq), w);
	angle = radToDeg(angle);
}

inline Vector3f Quaternion::GetAxis() const
{
	float sinHalfThetaSq = 1.0f - w * w;
	float invSinHalfTheta = sqrtf(sinHalfThetaSq);
	Vector3f axis(x * invSinHalfTheta, y * invSinHalfTheta, z * invSinHalfTheta);
	return axis;
}

inline float Quaternion::GetAngle() const
{
	float sinHalfThetaSq = 1.0f - w * w;
	float angle = 2.0f * atan2f(sqrt(sinHalfThetaSq), w);
	return angle;
}


inline Vector3f Quaternion::rotate(const Vector3f &v) const
{
	Vector3f p(x, y, z);
	Vector3f t = (p * v) * 2.0f;
	return v + t * w + p * t;
	//Quaternion t;
	//t = *this * v;
	//t *= inverse();

	//Quaternion u = *this;

	//Quaternion t(0.0f, v.x, v.y, v.z);
	//t = u * t;
	//t *= u.inverse();

	//v.x = t.x; v.y = t.y; v.z = t.z;
	
	//Vector3f u(x, y, z);
	//float sinHalfAlpha = u.unitize();
	//v = v*(w*w) + (u*v - v*u)*sinHalfAlpha*w - u*v*u*(sinHalfAlpha*sinHalfAlpha);
}

inline void Quaternion::fromAngleAxis(float angle, const Vector3f &axis)
{
	float halfTheta = angle / 2.0f;
	halfTheta = degToRad(halfTheta);
	float s = sin(halfTheta);
	w = cos(halfTheta), x = axis.x * s, y = axis.y * s, z = axis.z * s;
}

inline Vector3f Quaternion::Normal(const Vector3f &p) const
{
	//Vector3f v(x, y, z);
	//v.unitize();
	//Vector3f v2(p);
	//v2.unitize();
	//v = v * v2;
	

	//Vector3f v(x, y, z);
	//v = v*Vector3f(0.0f, 0.0f, 1.0f);
	//v.unitize();
	//if (Math::closeEnough(w, 1.0f))
		//return v;

	Quaternion t = *this * p;//!!!
	t = t * inverse();
	Vector3f a;
	float angle;
	t.toAngleAxis(angle, a);
	Vector3f res(a.x, a.y, a.z);

	res.unitize();
	return res;
}

/*
inline Matrix4 Quaternion::toMatrix4() const
{
	// Converts this quaternion to a rotation matrix.
	//
	//  | 1 - 2(y^2 + z^2)	2(xy + wz)			2(xz - wy)			0  |
	//  | 2(xy - wz)		1 - 2(x^2 + z^2)	2(yz + wx)			0  |
	//  | 2(xz + wy)		2(yz - wx)			1 - 2(x^2 + y^2)	0  |
	//  | 0					0					0					1  |

	float x2 = x + x;
	float y2 = y + y;
	float z2 = z + z;
	float xx = x * x2;
	float xy = x * y2;
	float xz = x * z2;
	float yy = y * y2;
	float yz = y * z2;
	float zz = z * z2;
	float wx = w * x2;
	float wy = w * y2;
	float wz = w * z2;

	Matrix4 m;

	m[0][0] = 1.0f - (yy + zz);
	m[0][1] = xy + wz;
	m[0][2] = xz - wy;
	m[0][3] = 0.0f;

	m[1][0] = xy - wz;
	m[1][1] = 1.0f - (xx + zz);
	m[1][2] = yz + wx;
	m[1][3] = 0.0f;

	m[2][0] = xz + wy;
	m[2][1] = yz - wx;
	m[2][2] = 1.0f - (xx + yy);
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return m;
}



inline Vector3f Quaternion::rotate(const Vector3f &p)
{

	Matrix3 RotateM;
	RotateM[0][0] = 1 - 2 * y*y - 2 * z*z;
	RotateM[0][1] = 2 * x*y - 2 * z*w;
	RotateM[0][2] = 2 * x*z + 2 * y*w;
	RotateM[1][0] = 2 * x*y + 2 * z*w;
	RotateM[1][1] = 1 - 2 * x*x - 2 * z*z;
	RotateM[1][2] = 2 * y*z - 2 * x*w;
	RotateM[2][0] = 2 * x*z - 2 * y*w;
	RotateM[2][1] = 2 * y*z + 2 * x*w;
	RotateM[2][2] = 1 - 2 * x*x - 2 * y*y;


	Vector3f p1 = RotateM * p;
	return p1;
}

inline void Quaternion::toHeadPitchRoll(float &headDegrees, float &pitchDegrees, float &rollDegrees) const
{
    Matrix4 m;
    m.toHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees)
	m = this->toMatrix4();
}


inline void Quaternion::fromMatrix(const Matrix4 &m)
{
// Creates a quaternion from a rotation matrix.
// The algorithm used is from Allan and Mark Watt's "Advanced
// Animation and Rendering Techniques" (ACM Press 1992).

float s = 0.0f;
float q[4] = {0.0f};
float trace = m[0][0] + m[1][1] + m[2][2];

if (trace > 0.0f)
{
s = sqrtf(trace + 1.0f);
q[3] = s * 0.5f;
s = 0.5f / s;
q[0] = (m[1][2] - m[2][1]) * s;
q[1] = (m[2][0] - m[0][2]) * s;
q[2] = (m[0][1] - m[1][0]) * s;
}
else
{
int nxt[3] = {1, 2, 0};
int i = 0, j = 0, k = 0;

if (m[1][1] > m[0][0])
i = 1;

if (m[2][2] > m[i][i])
i = 2;

j = nxt[i];
k = nxt[j];
s = sqrtf((m[i][i] - (m[j][j] + m[k][k])) + 1.0f);

q[i] = s * 0.5f;
s = 0.5f / s;
q[3] = (m[j][k] - m[k][j]) * s;
q[j] = (m[i][j] + m[j][i]) * s;
q[k] = (m[i][k] + m[k][i]) * s;
}

x = q[0], y = q[1], z = q[2], w = q[3];
}

inline void Quaternion::fromHeadPitchRoll(float headDegrees, float pitchDegrees, float rollDegrees)
{
	Matrix4 m;
	m.fromHeadPitchRoll(headDegrees, pitchDegrees, rollDegrees);
	fromMatrix(m);
}
*/