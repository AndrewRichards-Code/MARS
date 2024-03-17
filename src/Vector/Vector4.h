#pragma once
#include "../mars_common.h"

namespace mars
{
	template<typename T> class Vector2;
	template<typename T> class Vector3;

	template<typename T>
	class Vector4
	{
	public:
		union
		{
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			struct { T s, t, p, q; };
		};

		//Constructs a Vector4 of 0.
		Vector4()
			:x(0), y(0), z(0), w(0) {}
		//Constructs a Vector4 taking x, y, z, w.
		Vector4(T x, T y, T z, T w)
			: x(x), y(y), z(z), w(w) {}
		//Constructs a Vector4 from another Vector4.
		Vector4(const Vector4& copy)
			: x(copy.x), y(copy.y), z(copy.z), w(copy.w) {}
		//Constructs a Vector4 from two Vector2 in the form of the first Vector2 go into x, y and the second Vector2 go into z, w.
		Vector4(const Vector2<T>& a, const Vector2<T>& b)
			: x(a.x), y(a.y), z(b.x), w(b.y) {}
		//Constructs a Vector4 from a Vector3 and a 'w' value.
		Vector4(const Vector3<T>& copy, T w)
			: x(copy.x), y(copy.y), z(copy.z), w(w) {}

		//Destructs the Vector4.
		~Vector4() {}

		//Takes the dot product of the current object and another Vector4.
		template<std::floating_point U>
		U Dot(const Vector4& other)
		{
			return Dot<U>(*this, other);
		}
		template<std::floating_point U>
		static U Dot(const Vector4& a, const Vector4& b)
		{
			return static_cast<U>((a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w));
		}

		//Normalise the current object.
		Vector4 Normalise()
		{
			*this = Normalise(*this);
			return *this;
		}
		//Normalise the input object and return a new Vector4.
		static Vector4 Normalise(const Vector4& other)
		{
			double length = other.Length<double>();
			if (length > 0.0)
				return other * static_cast<T>(1.0 / length);
			else
				return other;
		}

		//Returns the length of the Vector4.
		template<std::floating_point U>
		U Length() const
		{
			return static_cast<U>(sqrt(x * x + y * y + z * z + w * w));
		}

		//Returns component-wise the minimum value of the two Vector4s.
		static Vector4 Min(const Vector4& a, const Vector4& b)
		{
			Vector4 result;
			result.x = std::min<T>(static_cast<T>(a.x), static_cast<T>(b.x));
			result.y = std::min<T>(static_cast<T>(a.y), static_cast<T>(b.y));
			result.z = std::min<T>(static_cast<T>(a.z), static_cast<T>(b.z));
			result.w = std::min<T>(static_cast<T>(a.w), static_cast<T>(b.w));
			return result;
		}

		//Returns component-wise the maximum value of the two Vector4s.
		static Vector4 Max(const Vector4& a, const Vector4& b)
		{
			Vector4 result;
			result.x = std::max<T>(static_cast<T>(a.x), static_cast<T>(b.x));
			result.y = std::max<T>(static_cast<T>(a.y), static_cast<T>(b.y));
			result.z = std::max<T>(static_cast<T>(a.z), static_cast<T>(b.z));
			result.w = std::max<T>(static_cast<T>(a.w), static_cast<T>(b.w));
			return result;
		}

		//Linearly interpolate between two Vector4s.
		template<std::floating_point U>
		static Vector4<U> Lerp(const Vector4& start, const Vector4& end, U t)
		{
			Vector4<U> _start(static_cast<U>(start.x), static_cast<U>(start.y), static_cast<U>(start.z), static_cast<U>(start.w));
			Vector4<U> _end(static_cast<U>(end.x), static_cast<U>(end.y), static_cast<U>(end.z), static_cast<U>(start.w));
			return _start + (_end - _start) * t;
		}

		//Adds two Vector4s.
		Vector4 operator+ (const Vector4& other) const
		{
			return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
		}
		//Adds a Vector4 to the current object.
		Vector4& operator+= (const Vector4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}
		//Subtracts two Vector4s.
		Vector4 operator- (const Vector4& other) const
		{
			return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
		}
		//Subtracts a Vector4 from the current object.
		Vector4& operator-= (const Vector4& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}
		//Scales the Vector4 by the scaler a. The scaler go on the rhs of the object.
		Vector4 operator* (T a) const
		{
			return Vector4(x * a, y * a, z * a, w * a);
		}
		//Scales the current object by the scaler a. The scaler go on the rhs of the object.
		Vector4& operator*= (T a)
		{
			x *= a;
			y *= a;
			z *= a;
			w *= a;
			return *this;
		}
		//Divides the Vector4 by the scaler a. The scaler go on the rhs of the object.
		Vector4 operator/ (T a) const
		{
			return Vector4(x / a, y / a, z / a, w / a);
		}
		//Divides the current object by the scaler a. The scaler go on the rhs of the object.
		Vector4& operator/= (T a)
		{
			x /= a;
			y /= a;
			z /= a;
			w /= a;
			return *this;
		}

		//Compare the Vector4 with another Vector4. If it's equal, it'll return true.
		bool operator== (const Vector4& other) const
		{
			if (x == other.x && y == other.y && z == other.z && w == other.w)
				return true;
			else
				return false;
		}
		//Compare the Vector4 with another Vector4. If it's not equal, it'll return true.
		bool operator!= (const Vector4& other) const
		{
			if (x != other.x && y != other.y && z != other.z && w != other.w)
				return true;
			else
				return false;
		}

		//Postive operator implicit cast.
		Vector4 operator+ () { return *this; }
		//Negative operator implicit cast
		Vector4 operator- () { return (*this * -1); }

		//Vector3 operator implicit cast.
		inline operator Vector3<T>() { return Vector3<T>(x, y, z); }

		//Output stream operator.
		friend std::ostream& operator<< (std::ostream& stream, const Vector4& output)
		{
			SetOstream(stream);
			stream << output.x << ", " << output.y << ", " << output.z << ", " << output.w;
			SetOstream(stream);
			return stream;
		}

		inline const T* const GetData() const { return &x; }
		constexpr static inline size_t GetSize() { return sizeof(Vector4); }
	};

	typedef Vector4<float> float4;
	typedef Vector4<double> double4;
	typedef Vector4<int32_t> int4;
	typedef Vector4<uint32_t> uint4;
}
