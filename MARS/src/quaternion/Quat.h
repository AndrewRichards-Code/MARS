#pragma once
#include "../mars_common.h"

namespace mars
{
	class Vec3;
	class Vec4;
	class Mat4;
	class Quat
	{
	public:
		float s, i, j, k; 

		//Constructs a Quat of 0.
		Quat();
		//Constructs a Quat taking s, i, j, k.
		Quat(float s, float i, float j, float k);
		//Constructs a Quat taking angle, and an axis.
		Quat(float angle, const Vec3& axis);
		//Constructs a Quat taking Vec4.
		Quat(const Vec4& sijk);

		//Destructs the Quat.
		~Quat();

		//Finds the conjugate of the current object.
		Quat Conjugate();
		//Finds the conjugate of the input object.
		static Quat Conjugate(const Quat& other);

		//Normalises the current object.
		Quat Normalise();

		//Normalises the input object.
		static Quat Normalise(const Quat& input);

		//Converts a Quat and a Vec3.
		static Vec3 ToVec3(const Quat & other);
		//Converts the current object to a new Mat4.
		Mat4 ToMat4();
		//Converts the input object to a new Mat4.
		static Mat4 ToMat4(const Quat& input);

		//Adds two Quats.
		Quat operator+ (const Quat& other) const;
		//Adds a Quat to the current object.
		Quat& operator+= (const Quat& other);
		//Subtracts two Quats.
		Quat operator- (const Quat& other) const;
		//Subtracts a Quat from the current object.
		Quat& operator-= (const Quat& other);
		//Multiples two Quats.
		Quat operator* (const Quat& other) const;
		//Multiples the current object with another Quat.
		Quat& operator*= (const Quat& other);
		//Multiples Quat and a Vec3.
		Quat operator* (const Vec3& other) const;
		//Multiples the current object with a Vec3.
		Quat& operator*= (const Vec3& other);

		//Compare the Quat with another Quat. If it's equal, it'll return true.
		bool operator== (const Quat& other) const;
		//Compare the Quat with another Quat. If it's equal, it'll return true.
		bool operator!= (const Quat& other) const;

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Quat& output)
		{
			stream << output.s << ", " << output.i << "i, " << output.j << "j, " << output.k << "k" << std::endl;
			
			return stream;
		}
	};
}
