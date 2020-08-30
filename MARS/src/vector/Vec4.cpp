#include "Vec4.h"

using namespace mars;

Vec4::Vec4()
	:x(0), y(0), z(0), w(0) {}

Vec4::Vec4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w) {}

Vec4::Vec4(const Vec4 & copy)
	: x(copy.x), y(copy.y), z(copy.z), w(copy.w) {}

Vec4::Vec4(const Vec2 & a, const Vec2 & b)
	: x(a.x), y(a.y), z(b.x), w(b.y) {}

Vec4::Vec4(const Vec3& copy, float w)
	:x(copy.x), y(copy.y), z(copy.z), w(w){}

Vec4::~Vec4() {}

float Vec4::Dot(const Vec4& other)
{
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z) + (this->w * other.w);
}

Vec4 Vec4::Normalise()
{
	float length = Length();
	if (length > 0.0f)
		return *this * (1 / length);
	else
		return *this;
}

Vec4 Vec4::Normalise(const Vec4& other)
{
	float length = other.Length();
	if (length > 0.0f)
		return other * (1 / length);
	else
		return other;
}

float Vec4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

Vec4 Vec4::operator+ (const Vec4& other) const
{
	return Vec4 (x + other.x, y + other.y, z + other.z, w + other.w);
}

Vec4& Vec4::operator+= (const Vec4& other)
{
	x += other.x; 
	y += other.y; 
	z += other.z; 
	w += other.w;
	return *this;
}

Vec4 Vec4::operator- (const Vec4& other) const
{
	return Vec4 (x - other.x, y - other.y, z - other.z, w - other.w);
}

Vec4& Vec4::operator-= (const Vec4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vec4  Vec4 ::operator* (float a) const
{
	return Vec4 (a * x, a * y, a * z, a * w);
}

Vec4& Vec4::operator*= (float a)
{
	x *= a;
	y *= a;
	z *= a;
	w *= a;
	return *this;
}

bool Vec4 ::operator==(const Vec4 & other) const
{
	if (x == other.x && y == other.y && z == other.z && w == other.w)
		return true;
	else
		return false;
}

bool Vec4 ::operator!=(const Vec4 & other) const
{
	if (x != other.x && y != other.y && z != other.z && w != other.w)
		return true;
	else
		return false;
}