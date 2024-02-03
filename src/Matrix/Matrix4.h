#pragma once
#include "../mars_common.h"

namespace mars
{
	template<typename T> class Vector3;
	template<typename T> class Vector4;

	template<typename T>
	class Matrix4
	{
	public:
		T a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;

		//Constructs a Matrix4 of 0.
		Matrix4()
			:a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0),
			i(0), j(0), k(0), l(0), m(0), n(0), o(0), p(0) {}
		//Constructs a Matrix4 taking a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p.
		Matrix4(T a, T b, T c, T d, T e, T f, T g, T h,
			T i, T j, T k, T l, T m, T n, T o, T p)
			: a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h),
			i(i), j(j), k(k), l(l), m(m), n(n), o(o), p(p) {}
		//Constructs a Matrix4 from four Vector4s.
		Matrix4(const Vector4<T>& a, const Vector4<T>& b, const Vector4<T>& c, const Vector4<T>& d)
			: a(a.x), b(a.y), c(a.z), d(a.w), e(b.x), f(b.y), g(b.z), h(b.w),
			i(c.x), j(c.y), k(c.z), l(c.w), m(d.x), n(d.y), o(d.z), p(d.w) {}
		//Constructs a Matrix4 where the diagonal is the input.
		Matrix4(T diagonal)
			: a(diagonal), b(0), c(0), d(0), e(0), f(diagonal), g(0), h(0),
			i(0), j(0), k(diagonal), l(0), m(0), n(0), o(0), p(diagonal) {}

		//Destructs the Matrix4.
		~Matrix4() {}

		//Calcuates determinant, and returns the sum of the vector components.
		float Det() const
		{
			float temp_i = static_cast<float>(a) * Matrix3<T>(f, g, h, j, k, l, n, o, p).Det();
			float temp_j = static_cast<float>(b) * Matrix3<T>(e, g, h, i, k, l, m, o, p).Det();
			float temp_k = static_cast<float>(c) * Matrix3<T>(e, f, h, i, j, l, m, n, p).Det();
			float temp_l = static_cast<float>(d) * Matrix3<T>(e, f, g, i, j, k, m, n, o).Det();
			return temp_i - temp_j + temp_k - temp_l;
		}
		//Calcuates determinant, and returns as a vector.
		Vector4<T> VecDet() const
		{
			T temp_i = static_cast<T>(+1 * a * Matrix3<T>(f, g, h, j, k, l, n, o, p).Det());
			T temp_j = static_cast<T>(-1 * b * Matrix3<T>(e, g, h, i, k, l, m, o, p).Det());
			T temp_k = static_cast<T>(+1 * c * Matrix3<T>(e, f, h, i, j, l, m, n, p).Det());
			T temp_l = static_cast<T>(-1 * d * Matrix3<T>(e, f, g, i, j, k, m, n, o).Det());
			return Vector4<T>(temp_i, temp_j, temp_k, temp_l);
		}

		//Swaps the Column/Row Major Ording of the current matrix object.
		Matrix4 Transpose()
		{
			*this = Matrix4::Transpose(*this);
			return *this;
		}
		//Swaps the Column/Row Major Ording of the input matrix object, return to a new Matrix4 object.
		static Matrix4 Transpose(const Matrix4& input)
		{
			return Matrix4(input.a, input.e, input.i, input.m, input.b, input.f, input.j, input.n,
				input.c, input.g, input.k, input.o, input.d, input.h, input.l, input.p);
		}

		//Inverts the current matrix object.
		Matrix4 Inverse()
		{
			*this = Matrix4::Inverse(*this);
			return *this;
		}
		//Inverts the input matrix object, return to a new Matrix4 object.
		static Matrix4 Inverse(const Matrix4& input)
		{
			float det = input.Det();
			if (det == 0.0f)
				return input;

			Matrix4<T> result = Matrix4<T>
				(
					static_cast<T>(+Matrix3<T>(input.f, input.g, input.h, input.j, input.k, input.l, input.n, input.o, input.p).Det() / det),
					static_cast<T>(-Matrix3<T>(input.b, input.c, input.d, input.j, input.k, input.l, input.n, input.o, input.p).Det() / det),
					static_cast<T>(+Matrix3<T>(input.b, input.c, input.d, input.f, input.g, input.h, input.n, input.o, input.p).Det() / det),
					static_cast<T>(-Matrix3<T>(input.b, input.c, input.d, input.f, input.g, input.h, input.j, input.k, input.l).Det() / det),

					static_cast<T>(-Matrix3<T>(input.e, input.g, input.h, input.i, input.k, input.l, input.m, input.o, input.p).Det() / det),
					static_cast<T>(+Matrix3<T>(input.a, input.c, input.d, input.i, input.k, input.l, input.m, input.o, input.p).Det() / det),
					static_cast<T>(-Matrix3<T>(input.a, input.c, input.d, input.e, input.g, input.h, input.m, input.o, input.p).Det() / det),
					static_cast<T>(+Matrix3<T>(input.a, input.c, input.d, input.e, input.g, input.h, input.i, input.k, input.l).Det() / det),

					static_cast<T>(+Matrix3<T>(input.e, input.f, input.h, input.i, input.j, input.l, input.m, input.n, input.p).Det() / det),
					static_cast<T>(-Matrix3<T>(input.a, input.b, input.d, input.i, input.j, input.l, input.m, input.n, input.p).Det() / det),
					static_cast<T>(+Matrix3<T>(input.a, input.b, input.d, input.e, input.f, input.h, input.m, input.n, input.p).Det() / det),
					static_cast<T>(-Matrix3<T>(input.a, input.b, input.d, input.e, input.f, input.h, input.i, input.j, input.l).Det() / det),

					static_cast<T>(-Matrix3<T>(input.e, input.f, input.g, input.i, input.j, input.k, input.m, input.n, input.o).Det() / det),
					static_cast<T>(+Matrix3<T>(input.a, input.b, input.c, input.i, input.j, input.k, input.m, input.n, input.o).Det() / det),
					static_cast<T>(-Matrix3<T>(input.a, input.b, input.c, input.e, input.f, input.g, input.m, input.n, input.o).Det() / det),
					static_cast<T>(+Matrix3<T>(input.a, input.b, input.c, input.e, input.f, input.g, input.i, input.j, input.k).Det() / det)
					);
			return result;
		}

		//Constructs a Matrix4 where the diagonal is 1.
		static Matrix4 Identity()
		{
			return Matrix4(1);
		}

		//Constructs a orthographic matrix (Matrix4).
		//For Normalised Device Co-ordinates of X: -1 to 1, Y: -1 to 1 and Z: 0 to 1 in a Left-Handed system.  Options for Reverse Z and Right-Handed system.
		//https://github.com/microsoft/DirectXMath/blob/main/Inc/DirectXMathMatrix.inl //Handed-ness and Reverse Z.
		static Matrix4 Orthographic(float left, float right, float bottom, float top, float zNear, float zFar, bool reverseZ = false, bool rightHanded = false)
		{
			if (reverseZ)
			{
				const float temp = zNear;
				zNear = zFar;
				zFar = temp;
			}

			T A = 0, B = 0, C = 0, X = 0, Y = 0, Z = 0;
			A = static_cast<T>(2) / static_cast<T>(right - left);
			B = static_cast<T>(2) / static_cast<T>(top - bottom);
			X = static_cast<T>(-(right + left) / (right - left));
			Y = static_cast<T>(-(top + bottom) / (top - bottom));
			if (rightHanded) 
			{
				C = static_cast<T>(1) / static_cast<T>(zNear - zFar);
				Z = static_cast<T>(zNear) * C;
			}
			else
			{
				C = static_cast<T>(1) / static_cast<T>(zFar - zNear);
				Z = static_cast<T>(-zNear) * C;
			}
			return Matrix4(
				A, 0, 0, 0,
				0, B, 0, 0,
				0, 0, C, 0,
				X, Y, Z, 1);
		}

		//Constructs a perspective matrix (Matrix4). Input fov is in radians.
		//For Normalised Device Co-ordinates of X: -1 to 1, Y: -1 to 1 and Z: 0 to 1 in a Left-Handed system. Options for Reverse Z and Right-Handed system.
		//https://www.gamedev.net/tutorials/programming/graphics/perspective-projections-in-lh-and-rh-systems-r3598/ //Handed-ness.
		//https://github.com/sebbbi/rust_test/commit/d64119ce22a6a4972e97b8566e3bbd221123fcbb //Reverse Z.
		static Matrix4 Perspective(double fov, float aspectRatio, float zNear, float zFar, bool reverseZ = false, bool rightHanded = false)
		{

			T A = 0, B = 0, C = 0, D = 0, E = 0;
			A = static_cast<T>(1) / static_cast<T>(aspectRatio * static_cast<float>(tan(fov / 2.0)));
			B = static_cast<T>(1) / static_cast<T>(static_cast<float>(tan(fov / 2)));
			D = rightHanded ? static_cast<T>(-1) : static_cast<T>(1);
			if (reverseZ)
			{
				C = static_cast<T>((-zNear) / (zFar - zNear));
				E = (rightHanded ? static_cast<T>(zFar) : static_cast<T>(-zFar)) * C;
			}
			else
			{
				C = static_cast<T>((zFar) / (zFar - zNear));
				E = (rightHanded ? static_cast<T>(zNear) : static_cast<T>(-zNear)) * C;
			}

			return Matrix4(
				A, 0, 0, 0,
				0, B, 0, 0,
				0, 0, C, E,
				0, 0, D, 0);
		}

		//Constructs an offset perspective matrix (Matrix4). Inputs angles are in radians.
		//For Normalised Device Co-ordinates of X: -1 to 1, Y: -1 to 1 and Z: 0 to 1 in a Left-Handed system. Options for Reverse Z and Right-Handed system.
		//https://www.gamedev.net/tutorials/programming/graphics/perspective-projections-in-lh-and-rh-systems-r3598/ //Handed-ness.
		//https://github.com/sebbbi/rust_test/commit/d64119ce22a6a4972e97b8566e3bbd221123fcbb //Reverse Z.
		//https://github.com/KhronosGroup/OpenXR-Tutorials/blob/main/Common/xr_linear_algebra.h#L488-L544
		static Matrix4 PerspectiveOffset(double angleLeft, double angleRight, double angleDown, double angleUp, float zNear, float zFar, bool reverseZ = false, bool rightHanded = false)
		{
			const double tanLeft = tan(angleLeft);
			const double tanRight = tan(angleRight);
			const double tanDown = tan(angleDown);
			const double tanUp = tan(angleUp);

			const double tanWidth = tanRight - tanLeft;
			const double tanHeight = tanUp - tanDown;

			T A = 0, B = 0, C = 0, D = 0, E = 0, X = 0, Y = 0;
			A = static_cast<T>(2) / static_cast<T>(tanWidth);
			B = static_cast<T>(2) / static_cast<T>(tanHeight);
			X = static_cast<T>((tanRight + tanLeft) / tanWidth);
			Y = static_cast<T>((tanUp + tanDown) / tanHeight);
			D = rightHanded ? static_cast<T>(-1) : static_cast<T>(1);
			if (reverseZ)
			{
				C = D * static_cast<T>((-zNear) / (zFar - zNear));
				E = (rightHanded ? static_cast<T>(zFar) : static_cast<T>(-zFar)) * C;
			}
			else
			{
				C = D * static_cast<T>((zFar) / (zFar - zNear));
				E = (rightHanded ? static_cast<T>(zNear) : static_cast<T>(-zNear)) * C;
			}

			return Matrix4(
				A, 0, X, 0,
				0, B, Y, 0,
				0, 0, C, E,
				0, 0, D, 0);
		}

		//Constructs a translation matrix.
		static Matrix4 Translation(const Vector3<T>& translation)
		{
			Matrix4 result(1);
			result.d = translation.x;
			result.h = translation.y;
			result.l = translation.z;
			return result;
		}
		//Constructs a rotation matrix. Input angle is in radians.
		static Matrix4 Rotation(double angle, const Vector3<T>& axis)
		{
			Matrix4<T> result(1);
			T c_angle = static_cast<T>(cos(angle));
			T s_angle = static_cast<T>(sin(angle));
			T omcos = static_cast<T>(1 - c_angle);

			const T& x = static_cast<T>(axis.x);
			const T& y = static_cast<T>(axis.y);
			const T& z = static_cast<T>(axis.z);

			result.a = x * x * omcos + c_angle;
			result.e = x * y * omcos + z * s_angle;
			result.i = x * z * omcos - y * s_angle;
			result.m = 0;

			result.b = y * x * omcos - z * s_angle;
			result.f = y * y * omcos + c_angle;
			result.j = y * z * omcos + x * s_angle;
			result.n = 0;

			result.c = z * x * omcos + y * s_angle;
			result.g = z * y * omcos - x * s_angle;
			result.k = z * z * omcos + c_angle;
			result.o = 0;

			result.d = 0;
			result.h = 0;
			result.l = 0;
			result.p = 1;

			return result;
		}
		//Constructs a scale matrix.
		static Matrix4 Scale(const Vector3<T>& scale)
		{
			Matrix4 result(1);
			result.a = scale.x;
			result.f = scale.y;
			result.k = scale.z;
			return result;
		}

		//Multiplies a Vector4 input by the current matrix transform.
		Vector4<T> operator*(const Vector4<T>& input) const
		{
			Vector4<T> transform_i(a, e, i, m);
			Vector4<T> transform_j(b, f, j, n);
			Vector4<T> transform_k(c, g, k, o);
			Vector4<T> transform_l(d, h, l, p);
			return Vector4<T>(transform_i * input.x + transform_j * input.y + transform_k * input.z + transform_l * input.w);
		}
		//Multiplies, or creates the composition of, the current Matrix4 by a Matrix4 input.
		Matrix4 operator*(const Matrix4& input) const
		{
			Vector4<T> input_i(input.a, input.e, input.i, input.m);
			Vector4<T> input_j(input.b, input.f, input.j, input.n);
			Vector4<T> input_k(input.c, input.g, input.k, input.o);
			Vector4<T> input_l(input.d, input.h, input.l, input.p);
			Vector4<T> output_i = *this * input_i;
			Vector4<T> output_j = *this * input_j;
			Vector4<T> output_k = *this * input_k;
			Vector4<T> output_l = *this * input_l;
			return Matrix4(output_i, output_j, output_k, output_l).Transpose();
		}
		//Multiplies, or creates the composition of, the current Matrix4 by a Matrix4 input.
		Matrix4& operator*=(const Matrix4& input)
		{
			*this = *this * input;
			return *this;
		}

		//Output stream operator.
		friend std::ostream& operator<< (std::ostream& stream, const Matrix4& output)
		{
			SetOstream(stream);
			stream << output.a << ", " << output.b << ", " << output.c << ", " << output.d << std::endl;
			stream << output.e << ", " << output.f << ", " << output.g << ", " << output.h << std::endl;
			stream << output.i << ", " << output.j << ", " << output.k << ", " << output.l << std::endl;
			stream << output.m << ", " << output.n << ", " << output.o << ", " << output.p;
			ResetOstream(stream);
			return stream;
		}

		inline const T* const GetData() const { return &a; }
		constexpr static inline size_t GetSize() { return sizeof(Matrix4); }
	};

	typedef Matrix4<float> float4x4;
	typedef Matrix4<double> double4x4;
	typedef Matrix4<int32_t> int4x4;
	typedef Matrix4<uint32_t> uint4x4;
}
