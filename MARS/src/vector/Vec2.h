#pragma once
#include "../mars_common.h"

namespace mars
{
	class Mat2;
	class Vec2
	{
	public:
		union
		{
			struct { float x, y; };
			struct { float r, g; };
			struct { float s, t; };
		};
		
		//Constructs a Vec2 of 0.
		Vec2();
		//Constructs a Vec2 taking x, y.
		Vec2(float x, float y);
		//Constructs a Vec2 from another Vec2.
		Vec2(const Vec2& copy);
		//Constructs a Vec2 from the struct CoordCart2D.
		Vec2(const CoordCart2D& other);
		//Constructs a Vec2 from the struct CoordPolar.
		Vec2(const CoordPolar& other);
		//Destructs the Vec2.
		~Vec2();

		//Takes the dot product of the current object and another Vec2.
		float Dot(const Vec2& other);
		//Takes the cross product/determinant of the current object and another Vec2.
		float Det(const Vec2& other);

		//Normalise the current object.
		Vec2 Normalise();
		//Normalise the input object and return a new Vec2.
		Vec2 Normalise(const Vec2& other);

		//Returns the length of the Vector.
		float Length();
		

		//ROTATIONS
		//Rotates the Vec2 by the input angle (in degrees). 
		Vec2 RotateDeg(double theta);
		//Rotates the Vec2 by the input angle (in radinas). 
		Vec2 RotateRad(double theta);
		//Rotates the Vec2 by 90 degress.
		Vec2 Rotate090();
		//Rotates the Vec2 by 180 degress.
		Vec2 Rotate180();
		//Rotates the Vec2 by 270 degress.
		Vec2 Rotate270();
		
		//Adds two Vec2s.
		Vec2 operator+ (const Vec2& other) const;
		//Adds a Vec2 to the current object.
		Vec2& operator+= (const Vec2& other);
		//Subtracts two Vec2s.
		Vec2 operator- (const Vec2& other) const;
		//Subtracts a Vec2 from the current object.
		Vec2& operator-= (const Vec2& other);
		//Scales the Vec2 by the scaler a. The scaler go on the rhs of the object.
		Vec2 operator* (float a) const;
		//Scales the current object by the scaler a. The scaler go on the rhs of the object.
		Vec2& operator*= (float a);
		//Compare the Vec2 with another Vec2. If it's equal, it'll return true.
		bool operator== (const Vec2& other) const;
		//Compare the Vec2 with another Vec2. If it's not equal, it'll return true.
		bool operator!= (const Vec2& other) const;

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Vec2& output)
		{
			stream << output.x << ", " << output.y;
			return stream;
		}

		inline const float* const GetData() const { return &x; }
		constexpr static inline size_t GetSize() { return sizeof(Vec2); }
	};
}