#include "Vec3.h"

using namespace mars;

Vec3::Vec3()
	:x(0), y(0), z(0) {}

Vec3::Vec3(float x, float y, float z)
	: x(x), y(y), z(z) {}

Vec3::Vec3(const Vec3& copy)
	: x(copy.x), y(copy.y), z(copy.z) {}

Vec3::Vec3(const CoordCart3D& other)
	: x((float)other.x), y((float)other.y), z((float)other.z) {}

Vec3::Vec3(const CoordSph& other)
	: x((float)(other.r * sin(other.theta) * cos(other.phi))),
	y((float)(other.r * sin(other.theta) * sin(other.phi))),
	z((float)(other.r * cos(other.theta))) {}

Vec3::~Vec3() {}

float Vec3::Dot(const Vec3& other)
{
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

float Vec3::Dot(const Vec3& a, const Vec3& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vec3 Vec3::Cross(const Vec3& other)
{
	Mat3 mat(Vec3(1, 1, 1), Vec3(x, y, z), Vec3(other.x, other.y, other.z));
	Vec3 output = mat.VecDet();
	return output;
}

Vec3 Vec3::Cross(const Vec3& a, const Vec3& b)
{
	Mat3 mat(Vec3(1, 1, 1), Vec3(a.x, a.y, a.z), Vec3(b.x, b.y, b.z));
	Vec3 output = mat.VecDet();
	return output;
}

Vec3 Vec3::Normalise()
{
	return *this * (1 / sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2)));
}

Vec3 Vec3::Normalise(const Vec3& other)
{
	return other * (1 / sqrt(pow(other.x, 2) + pow(other.y, 2) + pow(other.z, 2)));
}

float Vec3::Length()
{
	return sqrtf(x * x + y * y + z * z);
}

Vec3 Vec3::RotateQuat(float theta, const Vec3& axis)
{
	return RotateQuat(Quat(theta, axis));
}

Vec3 Vec3::RotateQuat(const Quat& q)
{
	Quat rotation = q;
	Quat rotationConjugate = rotation.Conjugate();
	Quat result = (rotation * (*this)) * rotationConjugate;
	return Quat::ToVec3(result);
}

Vec3 Vec3::operator+ (const Vec3& other) const
{
	return Vec3 (x + other.x, y + other.y, z + other.z);
}

Vec3& Vec3::operator+= (const Vec3& other)
{
	x += other.x; 
	y += other.y; 
	z += other.z;
	return *this;
}

Vec3 Vec3::operator- (const Vec3& other) const
{
	return Vec3 (x - other.x, y - other.y, z - other.z);
}

Vec3& Vec3::operator-= (const Vec3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 Vec3::operator* (float a) const
{
	return Vec3 (a * x, a * y, a * z);
}

Vec3& Vec3::operator*= (float a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

bool Vec3::operator==(const Vec3& other) const
{
	if (x == other.x && y == other.y && z == other.z)
		return true;
	else
		return false;
}

bool Vec3::operator!=(const Vec3& other) const
{
	if (x != other.x && y != other.y && z != other.z)
		return true;
	else
		return false;
}