#include "shape.h"

ShapeSet::ShapeSet()
{
}

ShapeSet::~ShapeSet()
{
}

void ShapeSet::addShape(Shape* shape)
{
	shapes.push_back(shape);
}

bool ShapeSet::intersect(Intersection& intersection)
{
	bool doesIntersect = false;

	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape *curShape = *iter;
		if (curShape->intersect(intersection))
			doesIntersect = true;
	}

	return doesIntersect;
}

bool ShapeSet::doesIntersect(const Ray& ray)
{
	for (std::vector<Shape*>::iterator iter = shapes.begin();
		iter != shapes.end();
		++iter)
	{
		Shape *curShape = *iter;
		if (curShape->doesIntersect(ray))
			return true;
	}

	return false;
}


Plane::Plane(const Point& position, const Vector& normal,
	const Color& color)
	: position(position),
	normal(normal),
	color(color)
{
}

Plane::~Plane()
{
}

bool Plane::intersect(Intersection& intersection)
{
	// First, check if we intersect
	float dDotN = dot(intersection.ray.direction, normal);

	if (dDotN == 0.0f)
	{
		// We just assume the ray is not embedded in the plane
		return false;
	}

	// Find point of intersection
	float t = dot(position - intersection.ray.origin, normal)
		/ dDotN;

	if (t <= RAY_T_MIN || t >= intersection.t)
	{
		// Outside relevant range
		return false;
	}

	intersection.t = t;
	intersection.pShape = this;
	intersection.color = color;

	return true;
}

bool Plane::doesIntersect(const Ray& ray)
{
	// First, check if we intersect
	float dDotN = dot(ray.direction, normal);

	if (dDotN == 0.0f)
	{
		// We just assume the ray is not embedded in the plane
		return false;
	}

	// Find point of intersection
	float t = dot(position - ray.origin, normal) / dDotN;

	if (t <= RAY_T_MIN || t >= ray.tMax)
	{
		// Outside relevant range
		return false;
	}

	return true;
}


Sphere::Sphere(const Point& centre, float radius,
	const Color& color)
	: centre(centre),
	radius(radius),
	color(color)
{
}

Sphere::~Sphere()
{
}

bool Sphere::intersect(Intersection& intersection)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = intersection.ray;
	localRay.origin -= centre;

	// Calculate quadratic coefficients
	float a = localRay.direction.length2();
	float b = 2 * dot(localRay.direction, localRay.origin);
	float c = localRay.origin.length2() - sqr(radius);

	// Check whether we intersect
	float discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

	// First check if close intersection is valid
	if (t1 > RAY_T_MIN && t1 < intersection.t)
	{
		intersection.t = t1;
	}
	else if (t2 > RAY_T_MIN && t2 < intersection.t)
	{
		intersection.t = t2;
	}
	else
	{
		// Neither is valid
		return false;
	}

	// Finish populating intersection
	intersection.pShape = this;
	intersection.color = color;

	return true;
}

bool Sphere::doesIntersect(const Ray& ray)
{
	// Transform ray so we can consider origin-centred sphere
	Ray localRay = ray;
	localRay.origin -= centre;

	// Calculate quadratic coefficients
	float a = localRay.direction.length2();
	float b = 2 * dot(localRay.direction, localRay.origin);
	float c = localRay.origin.length2() - sqr(radius);

	// Check whether we intersect
	float discriminant = sqr(b) - 4 * a * c;

	if (discriminant < 0.0f)
	{
		return false;
	}

	// Find two points of intersection, t1 close and t2 far
	float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
	if (t1 > RAY_T_MIN && t1 < ray.tMax)
		return true;

	float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
	if (t2 > RAY_T_MIN && t2 < ray.tMax)
		return true;

	return false;
}
