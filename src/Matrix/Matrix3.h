#pragma once
#include "../mars_common.h"

namespace mars
{
	template<typename T> class Vector3;

	template<typename T>
	class Matrix3
	{
	public:
		T a, b, c, d, e, f, g, h, i;

		//Constructs a Matrix3 of 0.
		Matrix3()
			:a(0), b(0), c(0), d(0), e(0), f(0), g(0), h(0), i(0) {}
		//Constructs a Vector3 taking a, b, c, d, e, f, g, h, i.
		Matrix3(T a, T b, T c, T d, T e, T f, T g, T h, T i)
			: a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i) {}
		//Constructs a Matrix3 from three Vec3s.
		Matrix3(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c)
			: a(a.x), b(a.y), c(a.z), d(b.x), e(b.y), f(b.z), g(c.x), h(c.y), i(c.z) {}

		//Destructs the Matrix3.
		~Matrix3() {}

		//Calcuates determinant, and returns the sum of the vector components.
		float Det() const
		{
			T temp_i = a * (e * i - f * h);
			T temp_j = b * (f * g - d * i);
			T temp_k = c * (d * h - e * g);
			return static_cast<float>(temp_i + temp_j + temp_k);
		}
		//Calcuates determinant, and returns as a vector.
		Vector3<T> VecDet() const
		{
			T temp_i = +1 * a * (e * i - f * h);
			T temp_j = -1 * b * (f * g - d * i);
			T temp_k = +1 * c * (d * h - e * g);
			return Vector3<T>(temp_i, temp_j, temp_k);
		}

		//Swaps the Column/Row Major Ording of the current matrix object.
		Matrix3 Transpose()
		{
			*this = Matrix3::Transpose(*this);
			return *this;
		}
		//Swaps the Column/Row Major Ording of the input matrix object, return to a new Matrix3 object.
		static Matrix3 Transpose(const Matrix3& input)
		{
			return Matrix3(input.a, input.d, input.g, input.b, input.e, input.h, input.c, input.f, input.i);
		}

		//Inverts the current matrix object.
		Matrix3 Inverse()
		{
			*this = Matrix3::Inverse(*this);
			return *this;
		}
		//Inverts the input matrix object, return to a new Matrix3 object.
		static Matrix3 Inverse(const Matrix3& input)
		{
			float det = input.Det();
			if (det == 0.0f)
				return input;

			Matrix3<T> result = Matrix3<T>
				(
					static_cast<T>(+Matrix2<T>(input.e, input.f, input.h, input.i).Det() / det),
					static_cast<T>(-Matrix2<T>(input.b, input.c, input.h, input.i).Det() / det),
					static_cast<T>(+Matrix2<T>(input.b, input.c, input.e, input.f).Det() / det),
					static_cast<T>(-Matrix2<T>(input.d, input.f, input.g, input.i).Det() / det),
					static_cast<T>(+Matrix2<T>(input.a, input.c, input.g, input.i).Det() / det),
					static_cast<T>(-Matrix2<T>(input.a, input.c, input.d, input.f).Det() / det),
					static_cast<T>(+Matrix2<T>(input.d, input.e, input.g, input.h).Det() / det),
					static_cast<T>(-Matrix2<T>(input.a, input.b, input.g, input.h).Det() / det),
					static_cast<T>(+Matrix2<T>(input.a, input.b, input.d, input.e).Det() / det)
					);
			return result;
		}

		//Multiplies a Vector3 input by the current matrix transform.
		Vector3<T> operator*(const Vector3<T>& input) const
		{
			Vector3<T> transform_i(a, d, g);
			Vector3<T> transform_j(b, e, h);
			Vector3<T> transform_k(c, f, i);
			return Vector3<T>(transform_i * input.x + transform_j * input.y + transform_k * input.z);
		}
		//Multiplies, or creates the composition of, the current Matrix3 by a Matrix3 input.
		Matrix3 operator*(const Matrix3& input) const
		{
			Vector3<T> input_i(input.a, input.d, input.g);
			Vector3<T> input_j(input.b, input.e, input.h);
			Vector3<T> input_k(input.c, input.f, input.i);
			Vector3<T> output_i = *this * input_i;
			Vector3<T> output_j = *this * input_j;
			Vector3<T> output_k = *this * input_k;
			return Matrix3(output_i, output_j, output_k).Transpose();
		}
		//Multiplies, or creates the composition of, the current Matrix3 by a Matrix3 input.
		Matrix3& operator*=(const Matrix3& input)
		{
			*this = *this * input;
			return *this;
		}

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Matrix3& output)
		{
			SetOstream(stream);
			stream << output.a << ", " << output.b << ", " << output.c << std::endl;
			stream << output.d << ", " << output.e << ", " << output.f << std::endl;
			stream << output.g << ", " << output.h << ", " << output.i;
			ResetOstream(stream);
			return stream;
		}

		inline const T* const GetData() const { return &a; }
		constexpr static inline size_t GetSize() { return sizeof(Matrix3); }
	};

	typedef Matrix3<float> float3x3;
	typedef Matrix3<double> double3x3;
	typedef Matrix3<int32_t> int3x3;
	typedef Matrix3<uint32_t> uint3x3;
}
