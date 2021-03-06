#include "Mat3.h"

using namespace mars;

Mat3::Mat3()
	:a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0), i(0) {}

Mat3::Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
	: a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i) {}

Mat3::Mat3(const Vec3 & a, const Vec3 & b, const Vec3 & c)
	: a(a.x), b(a.y), c(a.z), d(b.x), e(b.y), f(b.z), g(c.x), h(c.y), i(c.z) {}

Mat3::~Mat3() {}

float Mat3::Det()
{
	float temp_i = a * (e * i - f * h);
	float temp_j = b * (f * g - d * i);
	float temp_k = c * (d * h - e * g);
	return temp_i + temp_j + temp_k;
}

Vec3 Mat3::VecDet()
{
	float temp_i = +a * (e * i - f * h);
	float temp_j = -b * (f * g - d * i);
	float temp_k = +c * (d * h - e * g);
	return Vec3(temp_i, temp_j, temp_k);
}

void Mat3::Transpose()
{
	a = a;
	i = i;
	e = e;

	float temp_b = b;
	float temp_c = c;
	float temp_f = f;

	b = d;
	c = g;
	f = h;

	d = temp_b;
	g = temp_c;
	h = temp_f;
}

Mat3 Mat3::Transpose(const Mat3& input)
{
	return Mat3 (input.a, input.d, input.g, input.b, input.e, input.h, input.c, input.f, input.i);
}

void Mat3::Inverse()
{
	float det = this->Det();
	if (det == 0.0f)
		return;

	Mat3 result = Mat3
	(
		+Mat2(e, f, h, i).Det() / det,
		-Mat2(b, c, h, i).Det() / det,
		+Mat2(b, c, e, f).Det() / det,
		-Mat2(d, f, g, i).Det() / det,
		+Mat2(a, c, g, i).Det() / det,
		-Mat2(a, c, d, f).Det() / det,
		+Mat2(d, e, g, h).Det() / det,
		-Mat2(a, b, g, h).Det() / det,
		+Mat2(a, b, d, e).Det() / det
	);
	*this = result;
}

Mat3 Mat3::Inverse(const Mat3& input)
{
	Mat3 temp = input;
	float det = temp.Det();
	if (det == 0.0f)
		return input;

	Mat3 result = Mat3
	(
		+Mat2(input.e, input.f, input.h, input.i).Det() / det,
		-Mat2(input.b, input.c, input.h, input.i).Det() / det,
		+Mat2(input.b, input.c, input.e, input.f).Det() / det,
		-Mat2(input.d, input.f, input.g, input.i).Det() / det,
		+Mat2(input.a, input.c, input.g, input.i).Det() / det,
		-Mat2(input.a, input.c, input.d, input.f).Det() / det,
		+Mat2(input.d, input.e, input.g, input.h).Det() / det,
		-Mat2(input.a, input.b, input.g, input.h).Det() / det,
		+Mat2(input.a, input.b, input.d, input.e).Det() / det
	);
	return result;
}

Vec3 Mat3::operator*(const Vec3& input) const
{
	float x = input.x;
	float y = input.y;
	float z = input.z;
	Vec3 transform_i(a, d, g);
	Vec3 transform_j(b, e, h);
	Vec3 transform_k(c, f, i);
	Vec3 output(transform_i * x + transform_j * y + transform_k * z);
	return output;
}

Mat3 Mat3::operator*(const Mat3& input) const
{
	Vec3 input_i(input.a, input.d, input.g);
	Vec3 input_j(input.b, input.e, input.h);
	Vec3 input_k(input.c, input.f, input.i);
	Vec3 output_i = *this * input_i;
	Vec3 output_j = *this * input_j;
	Vec3 output_k = *this * input_k;
	Mat3 output(output_i, output_j, output_k);
	output.Transpose();
	return output;
}

Mat3& Mat3::operator*=(const Mat3& input)
{
	*this = *this * input;
	return *this;
}