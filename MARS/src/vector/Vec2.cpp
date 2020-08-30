#include "Vec2.h"

using namespace mars;

Vec2::Vec2()
	: x(0), y(0) {}

Vec2::Vec2(float x, float y)
	: x(x), y(y) {}

Vec2::Vec2(const Vec2& copy)
	: x(copy.x), y(copy.y) {}

Vec2::Vec2(const CoordCart2D& other)
	: x((float)other.x), y((float)other.y) {}


Vec2::Vec2(const CoordPolar& other)
	: x((float)(other.r * cos(other.theta))), y((float)(other.r * sin(other.theta))) {}

Vec2::~Vec2() {}

float Vec2::Dot(const Vec2& other)
{
	return (this->x * other.x) + (this->y * other.y);
}

float Vec2::Det(const Vec2& other)
{
	return (this->x * other.y) - (this->y * other.x);
}

Vec2 Vec2::Normalise()
{
	float length = Length();
	if (length > 0.0f)
		return *this * (1 / length);
	else
		return *this;
}

Vec2 Vec2::Normalise(const Vec2& other)
{
	float length = other.Length();
	if (length > 0.0f)
		return other * (1 / length);
	else
		return other;
}

float Vec2::Length() const
{
	return sqrtf(x * x + y * y);
}

Vec2 Vec2::RotateDeg(double theta)
{
	float theta_rads = (float)DegToRad(theta);
	return Vec2((float)(x * cos(theta_rads) - y * sin(theta_rads)), (float)(x * sin(theta_rads) + y * cos(theta_rads)));
}

Vec2 Vec2::RotateRad(double theta)
{
	return Vec2((float)(x * cos(theta) - y * sin(theta)), (float)(x * sin(theta) + y * cos(theta)));
}

Vec2 Vec2::Rotate090()
{
	return Vec2(x * 0 + y * -1, x * 1 + y * 0);
}

Vec2 Vec2::Rotate180()
{
	return Vec2(x * -1 + y * 0, x * 0 + y * -1);
}

Vec2 Vec2::Rotate270()
{
	return Vec2(x * 0 + y * 1, x * -1 + y * 0);
}

Vec2 Vec2::operator+ (const Vec2& other) const
{
	return Vec2(x + other.x, y + other.y);
}

Vec2& Vec2::operator+= (const Vec2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vec2 Vec2::operator- (const Vec2& other) const
{
	return Vec2(x - other.x, y - other.y);
}

Vec2& Vec2::operator-= (const Vec2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2 Vec2::operator*(float a) const
{
	return Vec2(a * x, a * y);
}

Vec2& Vec2::operator*=(float a)
{
	x *= a;
	y *= a;
	return *this;
}

bool Vec2::operator==(const Vec2& other) const
{
	if (x == other.x && y == other.y)
		return true;
	else
		return false;
}

bool Vec2::operator!=(const Vec2& other) const
{
	if (x != other.x && y != other.y)
		return true;
	else
		return false;
}