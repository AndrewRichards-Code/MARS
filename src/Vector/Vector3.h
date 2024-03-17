#pragma once
#include "../mars_common.h"
#include "../Conversion/Cartesian3DandSphericalCoord.h"

namespace mars
{
	class Quaternion;

	template<typename T>
	class Vector3
	{
	public:
		union
		{
			struct { T x, y, z; };
			struct { T r, g, b; };
			struct { T s, t, p; };
		};

		//Constructs a Vector3 of 0.
		Vector3()
			:x(0), y(0), z(0) {}
		//Constructs a Vector3 taking x, y, z.
		Vector3(T x, T y, T z)
			: x(x), y(y), z(z) {}
		//Constructs a Vector3 from another Vector3.
		Vector3(const Vector3& copy)
			: x(copy.x), y(copy.y), z(copy.z) {}
		//Constructs a Vector3 from the struct CoordCartesian3D.
		Vector3(const CoordCartesian3D& other)
			: x(static_cast<T>(other.x)), y(static_cast<T>(other.y)), z(static_cast<T>(other.z)) {}
		//Constructs a Vector3 from the struct CoordSpherical.
		Vector3(const CoordSpherical& other)
		{
			*this = Vector3(other.ToCartesian3D());
		}

		//Destructs the Vector3.
		~Vector3() {}

		//Takes the dot product of the current object and another Vector3.
		template<std::floating_point U>
		U Dot(const Vector3& other)
		{
			return Dot<U>(*this, other);
		}
		//Takes the dot product of two Vector3s.
		template<std::floating_point U>
		static U Dot(const Vector3& a, const Vector3& b)
		{
			return static_cast<U>((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
		}

		//Takes the cross product of the current object and another Vector3. RHRule.
		Vector3 Cross(const Vector3& other)
		{
			return Cross(*this, other);
		}
		//Takes the cross product of two Vector3s. RHRule.
		static Vector3 Cross(const Vector3& a, const Vector3& b)
		{
			Matrix3<T> mat(Vector3(1, 1, 1), Vector3(a.x, a.y, a.z), Vector3(b.x, b.y, b.z));
			return mat.VecDet();
		}

		//Normalise the current object.
		Vector3 Normalise()
		{
			*this = Normalise(*this);
			return *this;
		}
		//Normalise the input object and return a new Vector3.
		static Vector3 Normalise(const Vector3& other)
		{
			double length = other.Length<double>();
			if (length > 0.0)
				return other * static_cast<T>(1.0 / length);
			else
				return other;
		}

		//Returns the length of the Vector3.
		template<std::floating_point U>
		U Length() const
		{
			return static_cast<U>(sqrt(x * x + y * y + z * z));
		}

		//Returns component-wise the minimum value of the two Vector3s.
		static Vector3 Min(const Vector3& a, const Vector3& b)
		{
			Vector3 result;
			result.x = std::min<T>(static_cast<T>(a.x), static_cast<T>(b.x));
			result.y = std::min<T>(static_cast<T>(a.y), static_cast<T>(b.y));
			result.z = std::min<T>(static_cast<T>(a.z), static_cast<T>(b.z));
			return result;
		}

		//Returns component-wise the maximum value of the two Vector3s.
		static Vector3 Max(const Vector3& a, const Vector3& b)
		{
			Vector3 result;
			result.x = std::max<T>(static_cast<T>(a.x), static_cast<T>(b.x));
			result.y = std::max<T>(static_cast<T>(a.y), static_cast<T>(b.y));
			result.z = std::max<T>(static_cast<T>(a.z), static_cast<T>(b.z));
			return result;
		}

		//Linearly interpolate between two Vector3s.
		template<std::floating_point U>
		static Vector3<U> Lerp(const Vector3& start, const Vector3& end, U t)
		{
			Vector3<U> _start(static_cast<U>(start.x), static_cast<U>(start.y), static_cast<U>(start.z));
			Vector3<U> _end(static_cast<U>(end.x), static_cast<U>(end.y), static_cast<U>(end.z));
			return _start + (_end - _start) * t;
		}

		//Rotates the current object via quaternion and returns a new Vector3.
		Vector3 RotateQuaternion(double theta, const Vector3& axis)
		{
			*this = RotateQuaternion(Quaternion(theta, axis));
			return *this;
		}
		//Rotates the current object via quaternion and returns a new Vector3.
		Vector3 RotateQuaternion(const Quaternion& q)
		{
			Quaternion result = (q * (*this)) * Quaternion::Conjugate(q);
			return Quaternion::GetScaledAxis<T>(result);
		}

		//Adds two Vector3s.
		Vector3 operator+ (const Vector3& other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}
		//Adds a Vector3 to the current object.
		Vector3& operator+= (const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}
		//Subtracts two Vector3s.
		Vector3 operator- (const Vector3& other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
		//Subtracts a Vector3 from the current object.
		Vector3& operator-= (const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}
		//Scales the Vector3 by the scaler a. The scaler go on the rhs of the object.
		Vector3 operator* (T a) const
		{
			return Vector3(x * a, y * a, z * a);
		}
		//Scales the current object by the scaler a. The scaler go on the rhs of the object.
		Vector3& operator*= (T a)
		{
			x *= a;
			y *= a;
			z *= a;
			return *this;
		}
		//Divides the Vector3 by the scaler a. The scaler go on the rhs of the object.
		Vector3 operator/ (T a) const
		{
			return Vector3(x / a, y / a , z / a);
		}
		//Divides the current object by the scaler a. The scaler go on the rhs of the object.
		Vector3& operator/= (T a)
		{
			x /= a;
			y /= a;
			z /= a;
			return *this;
		}

		//Compare the Vector3 with another Vector3. If it's equal, it'll return true.
		bool operator== (const Vector3& other) const
		{
			if (x == other.x && y == other.y && z == other.z)
				return true;
			else
				return false;
		}
		//Compare the Vector3 with another Vector3. If it's not equal, it'll return true.
		bool operator!= (const Vector3& other) const
		{
			if (x != other.x && y != other.y && z != other.z)
				return true;
			else
				return false;
		}

		//Postive operator implicit cast.
		Vector3 operator+ () { return *this; }
		//Negative operator implicit cast.
		Vector3 operator- () { return (*this * -1); }

		//Output stream operator.
		friend std::ostream& operator<< (std::ostream& stream, const Vector3& output)
		{
			SetOstream(stream);
			stream << output.x << ", " << output.y << ", " << output.z;
			ResetOstream(stream);
			return stream;
		}

		inline const T* const GetData() const { return &x; }
		constexpr static inline size_t GetSize() { return sizeof(Vector3); }
	};

	typedef Vector3<float> float3;
	typedef Vector3<double> double3;
	typedef Vector3<int32_t> int3;
	typedef Vector3<uint32_t> uint3;
}