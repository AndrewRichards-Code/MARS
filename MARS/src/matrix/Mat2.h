#pragma once
#include "../Common.h"

namespace mars
{
	class Vec2;
	
	class Mat2
	{
	public:
		float a, b, c, d;

		//Constructs a Mat2 of 0.
		Mat2();
		//Constructs a Mat2 taking a, b, c, d.
		Mat2(float a, float b, float c, float d);
		//Constructs a Mat2 from two Vec2s.
		Mat2(const Vec2& a, const Vec2& b);

		//Destructs the Mat2.
		~Mat2();

		//Calcuates determinant, and returns the sum of the vector components.
		float Det();
		//Calcuates determinant, and returns as a vector.
		Vec2 VecDet();

		//Swaps the Column/Row Major Ording of the current matrix object.
		void Transpose();
		//Swaps the Column/Row Major Ording of the input matrix object, return to a new Mat2 object.
		Mat2 Transpose(const Mat2& input);


		//Inverts the current matrix object.
		void Inverse();
		//Inverts the input matrix object, return to a new Mat2 object.
		Mat2 Inverse(const Mat2& input);

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Mat2& output)
		{
			stream << output.a << ", " << output.b << std::endl;
			stream << output.c << ", " << output.d;
			
			return stream;
		}
	};
}