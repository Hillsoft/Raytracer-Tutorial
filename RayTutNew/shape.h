#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "vectormath.h"
#include "ray.h"

class Shape
{
public:
	virtual ~Shape() { }

	virtual bool intersect(Intersection& intersection) = 0;
	virtual bool doesIntersect(const Ray& ray) = 0;
};

class ShapeSet : public Shape
{
protected:
	std::vector<Shape*> shapes;

public:
	ShapeSet();

	virtual ~ShapeSet();

	void addShape(Shape* shape);

	virtual bool intersect(Intersection& intersection);
	virtual bool doesIntersect(const Ray& ray);
};

class Plane : public Shape
{
protected:
	Point position;
	Vector normal;

public:
	Plane(const Point& position, const Vector& normal);

	virtual ~Plane();

	virtual bool intersect(Intersection& intersection);
	virtual bool doesIntersect(const Ray& ray);
};

class Sphere : public Shape
{
protected:
	Point centre;
	float radius;

public:
	Sphere(const Point& centre, float radius);

	virtual ~Sphere();

	virtual bool intersect(Intersection& intersection);
	virtual bool doesIntersect(const Ray& ray);
};

#endif // SHAPE_H
