#pragma once

namespace mars
{
	template<typename T>
	struct Vector2
	{
		T x, y;
	};

	template<typename T>
	struct Vector3
	{
		T x, y, z;
	};

	template<typename T>
	struct Vector4
	{
		T x, y, z, w;
	};

	typedef Vector2<double> Double2;
	typedef Vector3<double> Double3;
	typedef Vector4<double> Double4;

	typedef Vector2<int32_t> Int2;
	typedef Vector3<int32_t> Int3;
	typedef Vector4<int32_t> Int4;

	typedef Vector2<uint32_t> Uint2;
	typedef Vector3<uint32_t> Uint3;
	typedef Vector4<uint32_t> Uint4;
}