#pragma once

namespace mars
{
	template<typename T>
	struct Matrix2
	{
		T a, b, c, d;
	};

	template<typename T>
	struct Matrix3
	{
		T a, b, c, d, e, f, g, h, i;
	};

	template<typename T>
	struct Matrix4
	{
		T a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
	};

	typedef Matrix2<double> DMat2;
	typedef Matrix3<double> DMat3;
	typedef Matrix4<double> DMat4;

	typedef Matrix2<int32_t> IMat2;
	typedef Matrix3<int32_t> IMat3;
	typedef Matrix4<int32_t> IMat4;

	typedef Matrix2<uint32_t> UIMat2;
	typedef Matrix3<uint32_t> UIMat3;
	typedef Matrix4<uint32_t> UIMat4;
}