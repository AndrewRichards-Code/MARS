#pragma once
#include "../mars_common.h"

namespace mars
{
	class Mat4;
	class Vec4
	{
	public:
		union
		{
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { float s, t, p, q; };
		};

		//Constructs a Vec4 of 0.
		Vec4();
		//Constructs a Vec4 taking x, y, z, w.
		Vec4(float x, float y, float z, float w);
		//Constructs a Vec4 from another Vec4.
		Vec4(const Vec4 & copy);
		//Constructs a Vec4 from two Vec2 in the form of the first Vec2 go into x, y and the second Vec2 go into z, w.
		Vec4(const Vec2 & a, const Vec2 & b);
		//Constructs a Vec4 from a Vec3 and a 'w' value.
		Vec4(const Vec3& copy, float w);

		//Destructs the Vec4.
		~Vec4();

		//Takes the dot product of the current object and another Vec4.
		float Dot(const Vec4& other);

		//Normalise the current object.
		Vec4 Normalise();
		//Normalise the input object and return a new Vec4.
		Vec4 Normalise(const Vec4& other);

		//Returns the length of the Vector.
		float Length();

		//Adds two Vec4s.
		Vec4 operator+ (const Vec4& other) const;
		//Adds a Vec4 to the current object.
		Vec4& operator+= (const Vec4& other);
		//Subtracts two Vec4s.
		Vec4 operator- (const Vec4& other) const;
		//Subtracts a Vec3 from the current object.
		Vec4& operator-= (const Vec4& other);
		//Scales the Vec4 by the scaler a. The scaler go on the rhs of the object.
		Vec4 operator* (float a) const;
		//Scales the current object by the scaler a. The scaler go on the rhs of the object.
		Vec4& operator*= (float a);

		//Compare the Vec4 with another Vec4. If it's equal, it'll return true.
		bool operator== (const Vec4& other) const;
		//Compare the Vec4 with another Vec4. If it's not equal, it'll return true.
		bool operator!= (const Vec4& other) const;

		//Postive operator implicit cast
		Vec4 operator+ () { return *this; }
		//Negative operator implicit cast
		Vec4 operator- () { return (*this * -1); }

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Vec4& output)
		{
			SetOstream(stream);
			stream << output.x << ", " << output.y << ", " << output.z << ", " << output.w;
			SetOstream(stream);
			return stream;
		}

		inline const float* const GetData() const { return &x; }
		constexpr static inline size_t GetSize() { return sizeof(Vec4); }
	};
}
