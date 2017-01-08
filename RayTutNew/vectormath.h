#ifndef MATHS_H
#define MATHS_H

#ifndef NULL
#define NULL 0
#endif

#ifndef PI
#define PI 3.1415926f
#endif

inline float sqr(float n)
{
	return n * n;
}

struct Vector
{
	float x, y, z;

	Vector();
	Vector(const Vector& v);
	Vector(float x, float y, float z);
	Vector(float f);

	virtual ~Vector();

	inline float length2();
	inline float length();

	float normalize();
	Vector normalized();

	Vector& operator =(const Vector& v);
	Vector& operator +=(const Vector& v);
	Vector& operator -=(const Vector& v);
	Vector& operator *=(float f);
	Vector& operator /=(float f);
	Vector operator -() const;
};

float dot(Vector v1, Vector v2);
Vector cross(Vector v1, Vector v2);

inline Vector operator +(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}

inline Vector operator -(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z);
}

inline Vector operator *(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z);
}

inline Vector operator *(const Vector& v, float f)
{
	return Vector(v.x * f,
		v.y * f,
		v.z * f);
}

inline Vector operator *(float f, const Vector& v)
{
	return Vector(f * v.x,
		f * v.y,
		f * v.z);
}

inline Vector operator /(const Vector& v1, const Vector& v2)
{
	return Vector(v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z);
}

inline Vector operator /(const Vector& v, float f)
{
	return Vector(v.x / f,
		v.y / f,
		v.z / f);
}

inline Vector operator /(float f, const Vector& v)
{
	return Vector(f / v.x,
		f / v.y,
		f / v.z);
}

typedef Vector Point;

struct Vector2
{
	float u, v;

	Vector2();
	Vector2(const Vector2& v);
	Vector2(float u, float v);
	Vector2(float f);

	virtual ~Vector2();

	Vector2& operator =(const Vector2& v);
};

#endif // MATHS_H
