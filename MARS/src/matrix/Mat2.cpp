#include "Mat2.h"

using namespace mars;

Mat2::Mat2()
	:a(0), b(0), c(0), d(0) {}

Mat2::Mat2(float a, float b, float c, float d)
	: a(a), b(b), c(c), d(d) {}

Mat2::Mat2(const Vec2& a, const Vec2& b)
	: a(a.x), b(a.y), c(b.x), d(b.y) {}

Mat2::~Mat2() {}

float Mat2::Det()
{
	float temp_i = a * d;
	float temp_j = b * c;
	return temp_i - temp_j;
}

Vec2 Mat2::VecDet()
{
	float temp_i = a * d;
	float temp_j = b * c;
	return Vec2(temp_i, temp_j);
}

void Mat2::Transpose()
{
	a = a;
	d = d;

	float temp_b = b;
	b = c;
	c = temp_b;
}

Mat2 Mat2::Transpose(const Mat2& input)
{
	return Mat2 (input.a, input.c, input.b, input.d);
}

void Mat2::Inverse()
{
	float det = this->Det();
	if (det == 0.0f)
		return;

	*this = Mat2(d / det, -b / det, -c / det, a / det);
}

Mat2 Mat2::Inverse(const Mat2& input)
{
	Mat2 temp = input;
	float det = temp.Det();
	if (det == 0.0f)
		return input;

	return Mat2((input.d) / det, (-input.b) / det, (-input.c) / det, (input.a) / det);
}