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
		float Dot(const Vector3& other)
		{
			return Dot(*this, other);
		}
		//Takes the dot product of two Vec3s.
		static float Dot(const Vector3& a, const Vector3& b)
		{
			return static_cast<float>((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
		}

		//Takes the cross product of the current object and another Vector3. RHRule.
		Vector3 Cross(const Vector3& other)
		{
			return Cross(*this, other);
		}
		//Takes the cross product of two Vec3s. RHRule.
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
			float length = other.Length();
			if (length > 0.0f)
				return other * static_cast<T>(1.0f / length);
			else
				return other;
		}

		//Returns the length of the Vector.
		float Length() const
		{
			return static_cast<float>(sqrt(x * x + y * y + z * z));
		}

		//Rotates the current object via quaternions and returns a new Vector3.
		Vector3 RotateQuat(double theta, const Vector3& axis)
		{
			*this = RotateQuat(Quaternion(theta, axis));
			return *this;
		}
		//Rotates the current object via quaternions and returns a new Vector3.
		Vector3 RotateQuat(const Quaternion& q)
		{
			Quaternion rotation = q;
			Quaternion rotationConjugate = rotation.Conjugate();
			Quaternion result = (rotation * (*this)) * rotationConjugate;
			return Quaternion::GetScaledAxis<T>(result);
		}

		//Adds two Vec3s.
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
		//Subtracts two Vec3s.
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
			return Vector3(a * x, a * y, a * z);
		}
		//Scales the current object by the scaler a. The scaler go on the rhs of the object.
		Vector3& operator*= (T a)
		{
			x *= a;
			y *= a;
			z *= a;
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

		//Postive operator implicit cast
		Vector3 operator+ () { return *this; }
		//Negative operator implicit cast
		Vector3 operator- () { return (*this * -1); }

		//Output stream operator
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