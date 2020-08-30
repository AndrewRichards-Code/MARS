#include "Quat.h"

using namespace mars;

Quat::Quat()
	:s(0), i(0), j(0), k(0) {}

Quat::Quat(double s, double i, double j, double k)
	:s(s), i(i), j(j), k(k)	{}

Quat::Quat(double angle, const Vec3& axis)
{
	Vec3 scaledAxis = axis * sinf((float)angle / 2.0f);
	s = cos(angle / 2.0);
	i = scaledAxis.x;
	j = scaledAxis.y;
	k = scaledAxis.z;
	Normalise();
}

Quat::Quat(const Vec4& sijk)
	: s(sijk.x), i(sijk.y), j(sijk.z), k(sijk.w) {}


Quat::~Quat() {}

Quat Quat::Conjugate() 
{
	return Quat(this->s, -this->i, -this->j, -this->k);
}

Quat Quat::Conjugate(const Quat& other)
{
	return Quat(other.s, -other.i, -other.j, -other.k);
}

Quat Quat::Normalise()
{
	double length = sqrt(s * s + i * i + j * j + k * k);
	if (length > 0.0f)
	{
		s /= length;
		i /= length;
		j /= length;
		k /= length;
	}
	return *this;
}

Quat Quat::Normalise(const Quat& input)
{
	Quat temp = input;
	return temp.Normalise();
}

Vec3 Quat::ToVec3()
{
	return ToVec3(*this);
}

Vec3 Quat::ToVec3(const Quat& other)
{
	Quat input = other; 
	input.Normalise();
	Vec3 result = Vec3((float)input.i, (float)input.j, (float)input.k).Normalise();
	float theta = 2 * acosf((float)input.s);
	float denom = sinf(theta / 2.0f);
	if (denom > 0.001)
	{
		result *= (1.0f / sinf(theta / 2.0f));
	}
	return result;
}

Mat4 Quat::ToMat4()
{
	Normalise();
	return Mat4(
		(float)(pow(s, 2) + pow(i, 2) - pow(j, 2) - pow(k, 2)), (float)(2*(i*j - k*s)), (float)(2*(i*k + j*s)), 0,
		(float)(2*(i*j + k*s)), (float)(pow(s, 2) - pow(i, 2) + pow(j, 2) - pow(k, 2)), (float)(2*(j*k - i*s)), 0,
		(float)(2*(i*k - j*s)), (float)(2*(j*k + i*s)), (float)(pow(s, 2) - pow(i, 2) - pow(j, 2) + pow(k, 2)), 0,
		0, 0, 0, 1);
}

Mat4 Quat::ToMat4(const Quat& input)
{
	Quat temp = input;
	temp.Normalise();
	return Mat4(
		(float)(pow(temp.s, 2) + pow(temp.i, 2) - pow(temp.j, 2) - pow(temp.k, 2)), (float)(2*(temp.i*temp.j - temp.k*temp.s)), (float)(2*(temp.i*temp.k + temp.j*temp.s)), 0,
		(float)(2*(temp.i*temp.j + temp.k*temp.s)), (float)(pow(temp.s, 2) - pow(temp.i, 2) + pow(temp.j, 2) - pow(temp.k, 2)), (float)(2*(temp.j*temp.k - temp.i*temp.s)), 0,
		(float)(2*(temp.i*temp.k - temp.j*temp.s)), (float)(2*(temp.j*temp.k + temp.i*temp.s)), (float)(pow(temp.s, 2) + pow(temp.i, 2) - pow(temp.j, 2) + pow(temp.k, 2)), 0,
		0, 0, 0, 1);
}

Quat Quat::operator+ (const Quat& other) const
{
	return Quat(s + other.s, i + other.i, j + other.j, k + other.k);
}

Quat& Quat::operator+=(const Quat& other)
{
	s += other.s;
	i += other.i;
	j += other.j;
	k += other.k;
	return *this;
}

Quat Quat::operator- (const Quat& other) const
{
	return Quat(s - other.s, i - other.i, j - other.j, k - other.k);
}

Quat& Quat::operator-= (const Quat& other)
{
	s -= other.s;
	i -= other.i;
	j -= other.j;
	k -= other.k;
	return *this;
}

Quat Quat::operator* (const Quat& other) const
{
	return Quat(
		((s * other.s) - (i * other.i) - (j * other.j) - (k * other.k)),
		((s * other.i) + (i * other.s) + (j * other.k) - (k * other.j)),
		((s * other.j) - (i * other.k) + (j * other.s) + (k * other.i)),
		((s * other.k) + (i * other.j) - (j * other.i) + (k * other.s))
	);										   
}

Quat& Quat::operator*= (const Quat& other)
{
	*this = *this * other;
	return *this;
}

Quat Quat::operator* (const Vec3& other) const
{
	return Quat(
		(- (i * other.x) - (j * other.y) - (k * other.z)),
		(+ (s * other.x) + (j * other.z) - (k * other.y)),
		(+ (s * other.y) + (k * other.x) - (i * other.z)),
		(+ (s * other.z) + (i * other.y) - (j * other.x))
	);
}

Quat& Quat::operator*= (const Vec3& other)
{
	*this = *this * other;
	return *this;
}

bool Quat::operator== (const Quat& other) const
{
	if (s == other.s && i == other.i && j == other.j && k == other.k)
		return true;
	else
		return false;
}

bool Quat::operator!= (const Quat& other) const
{
	if (s != other.s && i != other.i && j != other.j && k != other.k)
		return true;
	else
		return false;
}