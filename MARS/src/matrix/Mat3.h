#pragma once
#include "../mars_common.h"

namespace mars
{
	class Vec3;
	class Mat3
	{
	public:
		float a, b, c, d, e, f, g, h, i;

		//Constructs a Mat3 of 0.
		Mat3();
		//Constructs a Vec3 taking a, b, c, d, e, f, g, h, i.
		Mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
		//Constructs a Mat3 from three Vec3s.
		Mat3(const Vec3& a, const Vec3& b, const Vec3& c);

		//Destructs the Mat3.
		~Mat3();

		//Calcuates determinant, and returns the sum of the vector components.
		float Det();
		//Calcuates determinant, and returns as a vector.
		Vec3 VecDet();

		//Swaps the Column/Row Major Ording of the current matrix object.
		void Transpose();
		//Swaps the Column/Row Major Ording of the input matrix object, return to a new Mat3 object.
		Mat3 Transpose(const Mat3& input);

		//Inverts the current matrix object.
		void Inverse();
		//Inverts the input matrix object, return to a new Mat3 object.
		Mat3 Inverse(const Mat3& input);

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Mat3& output)
		{
			stream << output.a << ", " << output.b << ", " << output.c << std::endl;
			stream << output.d << ", " << output.e << ", " << output.f << std::endl;
			stream << output.g << ", " << output.h << ", " << output.i;
			return stream;
		}
	};
}
