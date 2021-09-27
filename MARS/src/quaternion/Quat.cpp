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
		(float)(1-2*(pow(j, 2) + pow(k, 2))),	(float)(2*(i*j - k*s)),					(float)(2*(i*k + j*s)),					0,
		(float)(2*(i*j + k*s)),					(float)(1-2*(pow(i, 2) + pow(k, 2))),	(float)(2*(j*k - i*s)),					0,
		(float)(2*(i*k - j*s)),					(float)(2*(j*k + i*s)),					(float)(1-2*(pow(i, 2) + pow(j, 2))),	0,
		0, 0, 0, 1);
}

Mat4 Quat::ToMat4(const Quat& input)
{
	Quat temp = input;
	temp.Normalise();
	return Mat4(
		(float)(1-2*(pow(temp.j, 2) + pow(temp.k, 2))), (float)(2*(temp.i*temp.j - temp.k*temp.s)),		(float)(2*(temp.i*temp.k + temp.j*temp.s)),		0,
		(float)(2*(temp.i*temp.j + temp.k*temp.s)),		(float)(1-2*(pow(temp.i, 2) + pow(temp.k, 2))), (float)(2*(temp.j*temp.k - temp.i*temp.s)),		0,
		(float)(2*(temp.i*temp.k - temp.j*temp.s)),		(float)(2*(temp.j*temp.k + temp.i*temp.s)),		(float)(1-2*(pow(temp.i, 2) + pow(temp.j, 2))), 0,
		0, 0, 0, 1);
}

Vec3 Quat::ToEulerAngles()
{
	return ToEulerAngles(*this);
}

Vec3 Quat::ToEulerAngles(const Quat& input)
{
	mars::Vec3 angles;

	// roll (x-axis rotation)
	double sinr_cosp = 2 * (input.s * input.i + input.j * input.k);
	double cosr_cosp = 1 - 2 * (input.i * input.i + input.j * input.j);
	angles.x = (float)std::atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = 2 * (input.s * input.j - input.k * input.i);
	if (std::abs(sinp) >= 1)
		angles.y = (float)std::copysign(pi / 2, sinp); // use 90 degrees if out of range
	else
		angles.y = (float)std::asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = 2 * (input.s * input.k + input.i * input.j);
	double cosy_cosp = 1 - 2 * (input.j * input.j + input.k * input.k);
	angles.z = (float)std::atan2(siny_cosp, cosy_cosp);

	return angles;
}

Quat Quat::FromEulerAngles(const Vec3& input)
{
	// Abbreviations for the various angular functions
	const float& roll = input.x;
	const float& pitch = input.y;
	const float& yaw = input.z;

	double cy = cos(yaw * 0.5);
	double sy = sin(yaw * 0.5);
	double cp = cos(pitch * 0.5);
	double sp = sin(pitch * 0.5);
	double cr = cos(roll * 0.5);
	double sr = sin(roll * 0.5);

	mars::Quat q;
	q.s = cr * cp * cy + sr * sp * sy;
	q.i = sr * cp * cy - cr * sp * sy;
	q.j = cr * sp * cy + sr * cp * sy;
	q.k = cr * cp * sy - sr * sp * cy;

	return q;
}

Quat mars::Quat::FromRotationMat4(const Mat4& input)
{
	Quat q;
	const double& a = static_cast<double>(input.a);
	const double& b = static_cast<double>(input.b);
	const double& c = static_cast<double>(input.c);
	
	const double& e = static_cast<double>(input.e);
	const double& f = static_cast<double>(input.f);
	const double& g = static_cast<double>(input.g);
	
	const double& i = static_cast<double>(input.i);
	const double& j = static_cast<double>(input.j);
	const double& k = static_cast<double>(input.k);

	if (a + f + k > 0.0)
	{
		float scale = sqrt((1.0 + a + f + k) / 4.0); //q.s
		q.s = scale;
		q.i = (j - g) / (4.0 * scale);
		q.j = (c - i) / (4.0 * scale);
		q.k = (e - b) / (4.0 * scale);
	}
	else if ((a > f) && (a > k))
	{
		float scale = sqrt((1.0 + a - f - k) / 4.0); //q.i 
		q.s = (j - g) / (4.0 * scale);
		q.i = scale;
		q.j = (b + e) / (4.0 * scale);
		q.k = (c + i) / (4.0 * scale);
	}
	else if (f > k)
	{
		float scale = sqrt((1.0 + f - a - k) / 4.0); //q.j
		q.s = (c - i) / (4.0 * scale);
		q.i = (b + e) / (4.0 * scale);
		q.j = scale;
		q.k = (g + j) / (4.0 * scale);
	}
	else 
	{
		float scale = sqrt((1.0 + k - a - f) / 4.0); //q.k
		q.s = (e - b) / (4.0 * scale);
		q.i = (c + i) / (4.0 * scale);
		q.j = (g + j) / (4.0 * scale);
		q.k = scale;
	}
	
	q.Normalise();
	return q;
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