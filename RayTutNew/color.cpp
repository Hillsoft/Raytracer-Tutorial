#include "color.h"

#include <cmath>
#include <algorithm>

Color::Color()
	: r(0.0f), g(0.0f), b(0.0f)
{
}

Color::Color(float l)
	: r(l), g(l), b(l)
{
}

Color::Color(float r, float g, float b)
	: r(r), g(g), b(b)
{
}

Color::~Color()
{
}

void Color::clamp(float min, float max)
{
	r = std::max(min, std::min(max, r));
	g = std::max(min, std::min(max, g));
	b = std::max(min, std::min(max, b));
}

void Color::applyGammaCorrection(float exposure, float gamma)
{
	r = std::pow(r * exposure, gamma);
	g = std::pow(g * exposure, gamma);
	b = std::pow(b * exposure, gamma);
}

Color& Color::operator =(const Color& c)
{
	r = c.r;
	g = c.g;
	b = c.b;
	return *this;
}

Color& Color::operator +=(const Color& c)
{
	r += c.r;
	g += c.g;
	b += c.b;
	return *this;
}

Color& Color::operator *=(const Color& c)
{
	r *= c.r;
	g *= c.g;
	b *= c.b;
	return *this;
}

Color& Color::operator *=(float f)
{
	r *= f;
	g *= f;
	b *= f;
	return *this;
}
