#pragma once
#include "../mars_common.h"

namespace mars
{
	template<typename T> class Vector4;
	template<typename T> class Matrix4;

	class Quaternion
	{
	public:
		double s, i, j, k;

		//Constructs a Quaternion of 0.
		Quaternion()
			:s(0), i(0), j(0), k(0) {}
		//Constructs a Quaternion taking s, i, j, k.
		Quaternion(double s, double i, double j, double k)
			:s(s), i(i), j(j), k(k) {}
		//Constructs a Quaternion taking angle, and an axis.
		template<typename T>
		Quaternion(double angle, const Vector3<T>& axis)
		{
			Vector3<double> scaledAxis = Vector3(axis.x, axis.y, axis.z);
			scaledAxis *= sin(angle / 2.0);

			s = cos(angle / 2.0);
			i = scaledAxis.x;
			j = scaledAxis.y;
			k = scaledAxis.z;
			Normalise();
		}
		//Constructs a Quaternion taking Vector4.
		template<typename T>
		Quaternion(const Vector4<T>& sijk)
			: s(static_cast<double>(sijk.x)), i(static_cast<double>(sijk.y)), j(static_cast<double>(sijk.z)), k(static_cast<double>(sijk.w)) {}

		//Destructs the Quaternion.
		~Quaternion() {}

		//Finds the conjugate of the current object.
		Quaternion Conjugate()
		{
			*this = Quaternion::Conjugate(*this);
			return *this;
		}
		//Finds the conjugate of the input object.
		static Quaternion Conjugate(const Quaternion& other)
		{
			return Quaternion(other.s, -other.i, -other.j, -other.k);
		}

		//Normalises the current object.
		Quaternion Normalise()
		{
			*this = Quaternion::Normalise(*this);
			return *this;
		}
		//Normalises the input object.
		static Quaternion Normalise(const Quaternion& input)
		{
			Quaternion temp = input;
			double length = sqrt(temp.s * temp.s + temp.i * temp.i + temp.j * temp.j + temp.k * temp.k);
			if (length > 0.0)
			{
				temp.s /= length;
				temp.i /= length;
				temp.j /= length;
				temp.k /= length;
			}

			return temp;
		}

		//Gets the scaled axis (imagery) of current object as a Vector3.
		template<typename T>
		Vector3<T> GetScaledAxis() const
		{
			return GetScaledAxis<T>(*this);
		}
		//Gets the scaled axis (imagery) of input object as a Vector3.
		template<typename T>
		static Vector3<T> GetScaledAxis(const Quaternion& other)
		{
			Quaternion input = other;
			input.Normalise();
			Vector3<T> result = Vector3<T>(static_cast<T>(input.i), static_cast<T>(input.j), static_cast<T>(input.k)).Normalise();
			double theta = 2.0 * acos(input.s);
			double denom = sin(theta / 2.0);
			if (denom > 0.001)
			{
				result *= static_cast<T>(1.0f / sin(theta / 2.0f));
			}
			return result;
		}

		//Converts the current object to a new Matrix4.
		template<typename T>
		Matrix4<T> ToRotationMatrix4() const
		{
			return Quaternion::ToRotationMatrix4<T>(*this);
		}
		//Converts the input object to a new Matrix4.
		template<typename T>
		static Matrix4<T> ToRotationMatrix4(const Quaternion& input)
		{
			Quaternion temp = input;
			temp.Normalise();
			return Matrix4<T>(
				static_cast<T>(1-2*(pow(temp.j, 2) + pow(temp.k, 2))),	static_cast<T>(2*(temp.i*temp.j - temp.k*temp.s)),		static_cast<T>(2*(temp.i*temp.k + temp.j*temp.s)),		0,
				static_cast<T>(2*(temp.i*temp.j + temp.k*temp.s)),		static_cast<T>(1-2*(pow(temp.i, 2) + pow(temp.k, 2))),	static_cast<T>(2*(temp.j*temp.k - temp.i*temp.s)),		0,
				static_cast<T>(2*(temp.i*temp.k - temp.j*temp.s)),		static_cast<T>(2*(temp.j*temp.k + temp.i*temp.s)),		static_cast<T>(1-2*(pow(temp.i, 2) + pow(temp.j, 2))),	0,
				0, 0, 0, 1);
		}
		//Converts the input object to a new Quaternion.
		template<typename T>
		static Quaternion FromRotationMatrix4(const Matrix4<T>& input)
		{
			Quaternion q;
			const double& a = static_cast<double>(input.a);
			const double& b = static_cast<double>(input.b);
			const double& c = static_cast<double>(input.c);

			const double& e = static_cast<double>(input.e);
			const double& f = static_cast<double>(input.f);
			const double& g = static_cast<double>(input.g);

			const double& i = static_cast<double>(input.i);
			const double& j = static_cast<double>(input.j);
			const double& k = static_cast<double>(input.k);

			if (a + f + k > 0.0)
			{
				double scale = sqrt((1.0 + a + f + k) / 4.0); //q.s
				q.s = scale;
				q.i = (j - g) / (4.0 * scale);
				q.j = (c - i) / (4.0 * scale);
				q.k = (e - b) / (4.0 * scale);
			}
			else if ((a > f) && (a > k))
			{
				double scale = sqrt((1.0 + a - f - k) / 4.0); //q.i 
				q.s = (j - g) / (4.0 * scale);
				q.i = scale;
				q.j = (b + e) / (4.0 * scale);
				q.k = (c + i) / (4.0 * scale);
			}
			else if (f > k)
			{
				double scale = sqrt((1.0 + f - a - k) / 4.0); //q.j
				q.s = (c - i) / (4.0 * scale);
				q.i = (b + e) / (4.0 * scale);
				q.j = scale;
				q.k = (g + j) / (4.0 * scale);
			}
			else
			{
				double scale = sqrt((1.0 + k - a - f) / 4.0); //q.k
				q.s = (e - b) / (4.0 * scale);
				q.i = (c + i) / (4.0 * scale);
				q.j = (g + j) / (4.0 * scale);
				q.k = scale;
			}

			q.Normalise();
			return q;
		}

		//Converts the current object to a new EulerAngles: Vector3(roll, pitch, yaw).
		template<typename T>
		Vector3<T> ToEulerAngles() const
		{
			return ToEulerAngles<T>(*this);
		}
		//Converts the input object to a new EulerAngles: Vector3(roll, pitch, yaw).
		template<typename T>
		static Vector3<T> ToEulerAngles(const Quaternion& input)
		{
			Vector3<T> angles;

			// roll (x-axis rotation)
			double sinr_cosp = 2 * (input.s * input.i + input.j * input.k);
			double cosr_cosp = 1 - 2 * (input.i * input.i + input.j * input.j);
			angles.x = static_cast<T>(atan2(sinr_cosp, cosr_cosp));

			// pitch (y-axis rotation)
			double sinp = 2 * (input.s * input.j - input.k * input.i);
			if (abs(sinp) >= 1)
				angles.y = static_cast<T>(copysign(pi / 2, sinp)); // use 90 degrees if out of range
			else
				angles.y = static_cast<T>(asin(sinp));

			// yaw (z-axis rotation)
			double siny_cosp = 2 * (input.s * input.k + input.i * input.j);
			double cosy_cosp = 1 - 2 * (input.j * input.j + input.k * input.k);
			angles.z = static_cast<T>(atan2(siny_cosp, cosy_cosp));

			return angles;
		}
		//Converts from EulerAngles: Vector3(roll, pitch, yaw).
		template<typename T>
		static Quaternion FromEulerAngles(const Vector3<T>& input)
		{
			// Abbreviations for the various angular functions
			const double& roll = static_cast<double>(input.x);
			const double& pitch = static_cast<double>(input.y);
			const double& yaw = static_cast<double>(input.z);

			double cy = cos(yaw * 0.5);
			double sy = sin(yaw * 0.5);
			double cp = cos(pitch * 0.5);
			double sp = sin(pitch * 0.5);
			double cr = cos(roll * 0.5);
			double sr = sin(roll * 0.5);

			Quaternion q;
			q.s = cr * cp * cy + sr * sp * sy;
			q.i = sr * cp * cy - cr * sp * sy;
			q.j = cr * sp * cy + sr * cp * sy;
			q.k = cr * cp * sy - sr * sp * cy;

			return q;
		}

		//Adds two Quats.
		Quaternion operator+ (const Quaternion& other) const
		{
			return Quaternion(s + other.s, i + other.i, j + other.j, k + other.k);
		}
		//Adds a Quaternion to the current object.
		Quaternion& operator+= (const Quaternion& other)
		{
			s += other.s;
			i += other.i;
			j += other.j;
			k += other.k;
			return *this;
		}
		//Subtracts two Quats.
		Quaternion operator- (const Quaternion& other) const
		{
			return Quaternion(s - other.s, i - other.i, j - other.j, k - other.k);
		}
		//Subtracts a Quaternion from the current object.
		Quaternion& operator-= (const Quaternion& other)
		{
			s -= other.s;
			i -= other.i;
			j -= other.j;
			k -= other.k;
			return *this;
		}
		//Multiples two Quats.
		Quaternion operator* (const Quaternion& other) const
		{
			return Quaternion(
				((s * other.s) - (i * other.i) - (j * other.j) - (k * other.k)),
				((s * other.i) + (i * other.s) + (j * other.k) - (k * other.j)),
				((s * other.j) - (i * other.k) + (j * other.s) + (k * other.i)),
				((s * other.k) + (i * other.j) - (j * other.i) + (k * other.s))
			);
		}
		//Multiples the current object with another Quaternion.
		Quaternion& operator*= (const Quaternion& other)
		{
			*this = *this * other;
			return *this;
		}
		//Multiples Quaternion and a Vector3.
		template<typename T>
		Quaternion operator* (const Vector3<T>& other) const
		{
			return Quaternion(
				(-(i * static_cast<double>(other.x)) - (j * static_cast<double>(other.y)) - (k * static_cast<double>(other.z))),
				(+(s * static_cast<double>(other.x)) + (j * static_cast<double>(other.z)) - (k * static_cast<double>(other.y))),
				(+(s * static_cast<double>(other.y)) + (k * static_cast<double>(other.x)) - (i * static_cast<double>(other.z))),
				(+(s * static_cast<double>(other.z)) + (i * static_cast<double>(other.y)) - (j * static_cast<double>(other.x)))
			);
		}
		//Multiples the current object with a Vector3.
		template<typename T>
		Quaternion& operator*= (const Vector3<T>& other)
		{
			*this = *this * other;
			return *this;
		}

		//Compare the Quaternion with another Quaternion. If it's equal, it'll return true.
		bool operator== (const Quaternion& other) const
		{
			if (s == other.s && i == other.i && j == other.j && k == other.k)
				return true;
			else
				return false;
		}
		//Compare the Quaternion with another Quaternion. If it's equal, it'll return true.
		bool operator!= (const Quaternion& other) const
		{
			if (s != other.s && i != other.i && j != other.j && k != other.k)
				return true;
			else
				return false;
		}

		//Output stream operator
		friend std::ostream& operator<< (std::ostream& stream, const Quaternion& output)
		{
			SetOstream(stream);
			stream << output.s << ", " << output.i << "i, " << output.j << "j, " << output.k << "k" << std::endl;
			ResetOstream(stream);
			return stream;
		}

		inline const double* const GetData() const { return &s; }
		constexpr static inline size_t GetSize() { return sizeof(Quaternion); }
	};
}
