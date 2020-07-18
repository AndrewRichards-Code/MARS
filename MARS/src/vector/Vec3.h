#pragma once
#include "../mars_common.h"

namespace mars
{
	class Mat3;
	class Quat;
	class Vec3
	{
	public:
		union
		{
			struct { float x, y, z; };
			struct { float r, g, b; };
			struct { float s, t, p; };
		};

		//Constructs a Vec3 of 0.
		Vec3();
		//Constructs a Vec3 taking x, y, z.
		Vec3(float x, float y, float z);
		//Constructs a Vec3 from another Vec3.
		Vec3(const Vec3 & copy);
		//Constructs a Vec3 from the struct CoordCart3D.
		Vec3(const CoordCart3D& other);
		//Constructs a Vec3 from the struct CoordSph.
		Vec3(const CoordSph& other);

		//Destructs the Vec3.
		~Vec3();

		//Takes the dot product of the current object and another Vec3.
		float Dot(const Vec3& other);
		//Takes the dot product of two Vec3s.
		static float Dot(const Vec3& a, const Vec3& b);

		//Takes the cross product of the current object and another Vec3. RHRule.
		Vec3 Cross(const Vec3& other);
		//Takes the cross product of two Vec3s. RHRule.
		static Vec3 Cross(const Vec3& a, const Vec3& b);

		//Normalise the current object.
		Vec3 Normalise();
		//Normalise the input object and return a new Vec3.
		static Vec3 Normalise(const Vec3& other);

		//Returns the length of the Vector.
		float Length();

		//Rotates the current object via quaternions and returns a new Vec3.
		Vec3 RotateQuat(float theta, const Vec3& axis);
		//Rotates the current object via quaternions and returns a new Vec3.
		Vec3 RotateQuat(const Quat& q);

		//Adds two Vec3s.
		Vec3 operator+ (const Vec3& other) const;
		//Adds a Vec3 to the current object.
		Vec3& operator+= (const Vec3& other);
		//Subtracts two Vec3s.
		Vec3 operator- (const Vec3& other) const;
		//Subtracts a Vec3 from the current object.
		Vec3& operator-= (const Vec3& other);
		//Scales the Vec3 by the scaler a. The scaler go on the rhs of the object.
		Vec3 operator* (float a) const;
		//Scales the current object by the scaler a. The scaler go on the rhs of the object.
		Vec3& operator*= (float a);

		//Compare the Vec3 with another Vec3. If it's equal, it'll return true.
		bool operator== (const Vec3& other) const;
		//Compare the Vec3 with another Vec3. If it's not equal, it'll return true.
		bool operator!= (const Vec3& other) const;

		//Postive operator implicit cast
		Vec3 operator+ () { return *this; }
		//Negative operator implicit cast
		Vec3 operator- () { return (*this * -1); }

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Vec3& output)
		{
			SetOstream(stream);
			stream << output.x << ", " << output.y << ", " << output.z;
			ResetOstream(stream);
			return stream;
		}

		inline const float* const GetData() const { return &x; }
		constexpr static inline size_t GetSize() { return sizeof(Vec3); }
	};
}