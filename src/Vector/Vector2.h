#pragma once
#include "../mars_common.h"
#include "../Conversion/Cartesian2DandPolarCoord.h"

namespace mars
{
	template<typename T>
	class Vector2
	{
	public:
		union
		{
			struct { T x, y; };
			struct { T r, g; };
			struct { T s, t; };
		};
		
		//Constructs a Vector2 of 0.
		Vector2()
			: x(0), y(0) {}
		//Constructs a Vector2 taking x, y.
		Vector2(T x, T y)
			: x(x), y(y) {}
		//Constructs a Vector2 from another Vector2.
		Vector2(const Vector2& copy)
			: x(copy.x), y(copy.y) {}
		//Constructs a Vector2 from the struct CoordCartesian2D.
		Vector2(const CoordCartesian2D& other)
			: x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
		//Constructs a Vector2 from the struct CoordPolar.
		Vector2(const CoordPolar& other)
		{
			*this = Vector2(other.ToCartesian2D());
		}
		//Destructs the Vector2.
		~Vector2() {}

		//Takes the dot product of the current object and another Vector2.
		template<std::floating_point U>
		U Dot(const Vector2& other)
		{
			return Dot<U>(*this, other);
		}
		//Takes the dot product of two Vector2s.
		template<std::floating_point U>
		static U Dot(const Vector2& a, const Vector2& b)
		{
			return static_cast<U>((a.x * b.x) + (a.y * b.y));
		}

		//Normalise the current object.
		Vector2 Normalise()
		{
			*this = Normalise(*this);
			return *this;
		}
		//Normalise the input object and return a new Vector2.
		static Vector2 Normalise(const Vector2& other)
		{
			double length = other.Length<double>();
			if (length > 0.0)
				return other * static_cast<T>(1.0 / length);
			else
				return other;
		}

		//Returns the length of the Vector.
		template<std::floating_point U>
		U Length() const
		{
			return static_cast<U>(sqrt(x * x + y * y));
		}

		//Linearly interpolate between two Vector2s.
		template<std::floating_point U>
		static Vector2<U> Lerp(const Vector2& start, const Vector2& end, U t)
		{
			Vector2<U> _start(static_cast<U>(start.x), static_cast<U>(start.y));
			Vector2<U> _end(static_cast<U>(end.x), static_cast<U>(end.y));
			return _start + (_end - _start) * t;
		}

		//Rotates the Vector2 by the input angle (in degrees).
		Vector2 RotateDeg(double theta)
		{
			double theta_rads = DegToRad(theta);
			return RotateRad(theta_rads);
		}
		//Rotates the Vector2 by the input angle (in radinas).
		Vector2 RotateRad(double theta)
		{
			return Vector2(static_cast<T>(x * cos(theta) - y * sin(theta)), static_cast<T>(x * sin(theta) + y * cos(theta)));
		}

		//Adds two Vector2s.
		Vector2 operator+ (const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}
		//Adds a Vector2 to the current object.
		Vector2& operator+= (const Vector2& other)
		{
			x += other.x;
			y += other.y;
			return *this;
		}
		//Subtracts two Vector2s.
		Vector2 operator- (const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}
		//Subtracts a Vector2 from the current object.
		Vector2& operator-= (const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}
		//Scales the Vector2 by the scaler a. The scaler go on the rhs of the object.
		Vector2 operator* (T a) const
		{
			return Vector2(a * x, a * y);
		}
		//Scales the current object by the scaler a. The scaler go on the rhs of the object.
		Vector2& operator*= (T a)
		{
			x *= a;
			y *= a;
			return *this;
		}
		//Compare the Vector2 with another Vector2. If it's equal, it'll return true.
		bool operator== (const Vector2& other) const
		{
			if (x == other.x && y == other.y)
				return true;
			else
				return false;
		}
		//Compare the Vector2 with another Vector2. If it's not equal, it'll return true.
		bool operator!= (const Vector2& other) const
		{
			if (x != other.x && y != other.y)
				return true;
			else
				return false;
		}

		//Postive operator implicit cast.
		Vector2 operator+ () { return *this; }
		//Negative operator implicit cast.
		Vector2 operator- () { return (*this * -1); }

		//Output stream operator.
		friend std::ostream& operator<< (std::ostream& stream, const Vector2& output)
		{
			SetOstream(stream);
			stream << output.x << ", " << output.y;
			ResetOstream(stream);
			return stream;
		}

		inline const T* const GetData() const { return &x; }
		constexpr static inline size_t GetSize() { return sizeof(Vector2); }
	};

	typedef Vector2<float> float2;
	typedef Vector2<double> double2;
	typedef Vector2<int32_t> int2;
	typedef Vector2<uint32_t> uint2;
}