#pragma once
#include "../mars_common.h"

namespace mars
{
	template<typename T> class Vector2;

	template<typename T>
	class Matrix2
	{
	public:
		T a, b, c, d;

		//Constructs a Matrix2 of 0.
		Matrix2()
			:a(0), b(0), c(0), d(0) {}
		//Constructs a Matrix2 taking a, b, c, d.
		Matrix2(T a, T b, T c, T d)
			: a(a), b(b), c(c), d(d) {}
		//Constructs a Matrix2 from two Vector2s.
		Matrix2(const Vector2<T>& a, const Vector2<T>& b)
			: a(a.x), b(a.y), c(b.x), d(b.y) {}

		//Destructs the Matrix2.
		~Matrix2() {}

		//Calcuates determinant, and returns the sum of the vector components.
		float Det() const
		{
			float temp_i = static_cast<float>(a * d);
			float temp_j = static_cast<float>(b * c);
			return temp_i - temp_j;
		}
		//Calcuates determinant, and returns as a vector.
		Vector2<T> VecDet() const
		{
			T temp_i = a * d;
			T temp_j = b * c;
			return Vector2<T>(temp_i, temp_j);
		}

		//Swaps the Column/Row Major Ording of the current matrix object.
		Matrix2 Transpose()
		{
			*this = Matrix2::Transpose(*this);
			return *this;
		}
		//Swaps the Column/Row Major Ording of the input matrix object, return to a new Matrix2 object.
		static Matrix2 Transpose(const Matrix2& input)
		{
			return Matrix2(input.a, input.c, input.b, input.d);
		}

		//Inverts the current matrix object.
		Matrix2 Inverse()
		{
			*this = Matrix2::Inverse(*this);
			return *this;
		}
		//Inverts the input matrix object, return to a new Matrix2 object.
		static Matrix2 Inverse(const Matrix2& input)
		{
			T det = static_cast<T>(input.Det());
			if (det == 0.0f)
				return input;

			return Matrix2((input.d) / det, (-1 * input.b) / det, (-1 * input.c) / det, (input.a) / det);
		}

		//Multiplies a Vector2 input by the current matrix transform.
		Vector2<T> operator*(const Vector2<T>& input) const
		{
			Vector2<T> transform_i(a, c);
			Vector2<T> transform_j(b, d);
			return Vector2<T>(transform_i * input.x + transform_j * input.y);
		}
		//Multiplies, or creates the composition of, the current Matrix2 by a Matrix2 input.
		Matrix2 operator*(const Matrix2& input) const
		{
			Vector2<T> input_i(input.a, input.c);
			Vector2<T> input_j(input.b, input.d);
			Vector2<T> output_i = *this * input_i;
			Vector2<T> output_j = *this * input_j;
			return Matrix2(output_i, output_j).Transpose();
		}
		//Multiplies, or creates the composition of, the current Matrix2 by a Matrix2 input.
		Matrix2& operator*=(const Matrix2& input)
		{
			*this = *this * input;
			return *this;
		}

		//Output stream operator.
		friend std::ostream& operator<< (std::ostream& stream, const Matrix2& output)
		{
			SetOstream(stream);
			stream << output.a << ", " << output.b << std::endl;
			stream << output.c << ", " << output.d;
			ResetOstream(stream);
			return stream;
		}

		inline const T* const GetData() const { return &a; }
		constexpr static inline size_t GetSize() { return sizeof(Matrix2); }
	};

	typedef Matrix2<float> float2x2;
	typedef Matrix2<double> double2x2;
	typedef Matrix2<int32_t> int2x2;
	typedef Matrix2<uint32_t> uint2x2;
}