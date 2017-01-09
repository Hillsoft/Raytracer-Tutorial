#ifndef RAY_H
#define RAY_H

#include "vectormath.h"
#include "color.h"

// In order to prevent bouncing rays self-intersecting
#define RAY_T_MIN 0.0001f

// 'Infinite' distance, used as a default value
#define RAY_T_MAX 1.0e30f

struct Ray
{
	Point origin; // start
	Vector direction;
	float tMax;

	Ray();
	Ray(const Ray& r);
	Ray(const Point& origin, const Vector& direction,
		float tMax = RAY_T_MAX);

	virtual ~Ray();

	Ray& operator =(const Ray& r);

	Point calculate(float t) const;
};

class Shape;

struct Intersection
{
	Ray ray;
	float t;
	Shape *pShape;
	Color color;

	Intersection();
	Intersection(const Intersection& i);
	Intersection(const Ray& ray);

	virtual ~Intersection();

	Intersection& operator =(const Intersection& i);

	bool intersected() const;
	Point position() const;
};

#endif // RAY_H
