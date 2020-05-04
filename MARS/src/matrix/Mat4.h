#pragma once
#include "../mars_common.h"

namespace mars
{
	class Vec3;
	class Vec4;
	class Mat4
	{
	public:
		float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

		//Constructs a Mat4 of 0.
		Mat4();
		//Constructs a Mat4 taking a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p.
		Mat4(float a, float b, float c, float d, float e, float f, float g, float h,
			float i, float j, float k, float l, float m, float n, float o, float p);
		//Constructs a Mat4 from four Vec4s.
		Mat4(const Vec4& a, const Vec4& b, const Vec4& c, const Vec4& d);
		//Constructs a Mat4 where the diagonal is the input.
		Mat4(float diagonal);

		//Destructs the Mat4.
		~Mat4();

		//Calcuates determinant, and returns the sum of the vector components.
		float Det();
		//Calcuates determinant, and returns as a vector.
		Vec4 VecDet();

		//Swaps the Column/Row Major Ording of the current matrix object.
		void Transpose();
		//Swaps the Column/Row Major Ording of the input matrix object, return to a new Mat4 object.
		Mat4 Transpose(const Mat4& input);

		//Inverts the current matrix object.
		void Inverse();
		//Inverts the input matrix object, return to a new Mat4 object.
		Mat4 Inverse(const Mat4& input);

		//Constructs a Mat4 where the diagonal is 1.
		static Mat4 Identity();
		//Constructs a orthographic matrix (Mat4).
		static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far);
		//Constructs a perspective matrix (Mat4). Input fov is in radians.
		static Mat4 Perspective(double fov, float aspectRatio, float near, float far);

		//Constructs a translation matrix (Mat4).
		static Mat4 Translation(const Vec3& translation);
		//Constructs a rotation matrix (Mat4). Input angle is in radians.
		static Mat4 Rotation(double angle, const Vec3& axis);
		//Constructs a scale matrix (Mat4).
		static Mat4 Scale(const Vec3& scale);

		//Multiplies a Vec4 input by the current matrix transform.
		Vec4 operator*(const Vec4& input) const;
		//Multiplies, or creates the composition of, the current Mat4 by a Mat4 transform.
		Mat4 operator*(const Mat4& transform) const;
		//Multiplies, or creates the composition of, the current Mat4 by a Mat4 transform.
		Mat4& operator*=(const Mat4& transform);

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Mat4 & output)
		{
			stream << output.a << ", " << output.b << ", " << output.c << ", " << output.d << std::endl;
			stream << output.e << ", " << output.f << ", " << output.g << ", " << output.h << std::endl;
			stream << output.i << ", " << output.j << ", " << output.k << ", " << output.l << std::endl;
			stream << output.m << ", " << output.n << ", " << output.o << ", " << output.p;
			return stream;
		}

		inline const float* const GetData() const { return &a; }
		constexpr static inline size_t GetSize() { return sizeof(Mat4); }
	};
}
