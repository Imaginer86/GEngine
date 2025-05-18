#pragma once
#include "GMath.h"

#include <iostream>

struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f():x(0.0f), y(0.0f), z(0.0f)	{}
	Vector3f(float x_, float y_, float z_):x(x_) ,y(y_) ,z(z_)	{}

	// Explicitly define the copy constructor
	Vector3f(const Vector3f& other) : x(other.x), y(other.y), z(other.z) {}

	// Explicitly define the copy assignment operator
	Vector3f& operator=(const Vector3f& other)
	{
		if (this != &other) // Prevent self-assignment
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}
		return *this;
	}
	~Vector3f()	{}

	bool operator !=(const  Vector3f& v);
	bool operator ==(const  Vector3f& v);
	//Vector3f operator+ (const Vector3f& v);	// operator+ is used to add two Vector3's. operator+ returns a new Vector3
	Vector3f operator+ (const Vector3f& v) const;
	//Vector3f operator- (const Vector3f& v);	// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
	Vector3f operator- (const Vector3f& v) const;
	//Vector3f operator* (float value);	// operator* is used to scale a Vector3 by a value. This value multiplies the Vector3's x, y and z.
	Vector3f operator* (float value) const;
	//Vector3f operator/ (float value);	// operator/ is used to scale a Vector3 by a value. This value divides the Vector3's x, y and z.
	Vector3f operator/ (float value) const;

	Vector3f& operator+= (const Vector3f& v);	// operator+= is used to add another Vector3 to this Vector3.
	Vector3f& operator-= (const Vector3f& v);	// operator-= is used to subtract another Vector3 from this Vector3.
	Vector3f& operator*= (float value);	// operator*= is used to scale this Vector3 by a value.
	Vector3f& operator/= (float value);	// operator/= is used to scale this Vector3 by a value.

	Vector3f operator- () const;	// operator- is used to set this Vector3's x, y, and z to the negative of them.	

	Vector3f operator*(const Vector3f& v);	// cross product (vector product)
	float dotProduct(const Vector3f& v);

	float length() const;	// length() returns the length of this Vector3
	float lenght2() const;
	float unitize();	// unitize() normalizes this Vector3 that its direction remains the same but its length is 1.
	Vector3f unit() const;	// unit() returns a new Vector3. The returned value is a unitized version of this Vector3.

	//std::istream& operator>> (std::istream& is);

	//std::ostream& operator<< (std::ostream& os);
};

const Vector3f VETOR3f_ZERO = Vector3f(0.0f, 0.0f, 0.0f);


inline std::istream& operator>> (std::istream& is, Vector3f& v)
{
	is >> v.x >> v.y >> v.z;
	return is;
}



inline std::ostream& operator<< (std::ostream& os, const Vector3f& v)
{
	os << v.x << " " << v.y << " " << v.z << " ";
	return os;
}

inline bool Vector3f::operator!=(const Vector3f& v)
{
	return x != v.x || y != v.y || z != v.z;
}

inline bool Vector3f::operator==(const Vector3f& v)
{
	x == v.x && y == v.y && z == v.z;
	return false;
}

/*
inline Vector3f Vector3f::operator+ (const Vector3f& v)				// operator+ is used to add two Vector3's. operator+ returns a new Vector3
{
	return Vector3f(x + v.x, y + v.y, z + v.z);
}

inline Vector3f Vector3f::operator- (const Vector3f& v)				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
{
	return Vector3f(x - v.x, y - v.y, z - v.z);
}

inline Vector3f Vector3f::operator* (float value)			// operator* is used to scale a Vector3 by a value. This value multiplies the Vector3's x, y and z.
{
	return Vector3f(x * value, y * value, z * value);
}
*/

inline Vector3f Vector3f::operator* (float value) const
{
	return Vector3f(x * value, y * value, z * value);
}

//inline Vector3f Vector3f::operator/ (float value)			// operator/ is used to scale a Vector3 by a value. This value divides the Vector3's x, y and z.
//{
	//return Vector3f(x / value, y / value, z / value);
//}

inline Vector3f Vector3f::operator/ (float value) const
{
	return Vector3f(x / value, y / value, z / value);
}

inline Vector3f& Vector3f::operator+= (const Vector3f& v)			// operator+= is used to add another Vector3 to this Vector3.
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline Vector3f& Vector3f::operator-= (const Vector3f& v)			// operator-= is used to subtract another Vector3 from this Vector3.
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline Vector3f& Vector3f::operator*= (float value)			// operator*= is used to scale this Vector3 by a value.
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

inline Vector3f& Vector3f::operator/= (float value)			// operator/= is used to scale this Vector3 by a value.
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

inline Vector3f Vector3f::operator- () const						// operator- is used to set this Vector3's x, y, and z to the negative of them.
{
	return Vector3f(-x, -y, -z);
}

// cross product (vector product)
inline Vector3f Vector3f::operator*(const Vector3f& v)
{
	Vector3f res;
	res.x = this->y*v.z - this->z*v.y;
	res.y = this->z*v.x - this->x*v.z;
	res.z = this->x*v.y - this->y*v.x;
	return res;
}

inline float Vector3f::dotProduct(const Vector3f& v)
{
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

inline float Vector3f::length()	const							// length() returns the length of this Vector3
{
	return sqrtf(x*x + y*y + z*z);
};

inline float Vector3f::lenght2() const
{
	return x*x + y*y + z*z;
}

inline float Vector3f::unitize()								// unitize() normalizes this Vector3 that its direction remains the same but its length is 1.
{
	float l = length();

	if (isZero(l))
		return 0.0f;

	x /= l;
	y /= l;
	z /= l;
	return l;
}

inline Vector3f Vector3f::unit() const								// unit() returns a new Vector3. The returned value is a unitized version of this Vector3.
{
	float l = length();

	if (isZero(l))
		return *this;

	return Vector3f(x / l, y / l, z / l);
}

inline Vector3f Vector3f::operator+ (const Vector3f& rv) const				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
{
	return Vector3f(x + rv.x, y + rv.y, z + rv.z);
}

inline Vector3f Vector3f::operator- (const Vector3f& rv) const				// operator- is used to take difference of two Vector3's. operator- returns a new Vector3
{
	return Vector3f(x - rv.x, y - rv.y, z - rv.z);
}
