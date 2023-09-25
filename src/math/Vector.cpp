#include <tinyalgebralib/math/Vector.hpp>

#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

namespace ta
{
	Vector<float, 4> operator+(const Vector<float, 4>& _V, const Vector<float, 4>& _U) noexcept
	{
		Vector<float, 4> result;
		__m128 v = _mm_load_ps(_V.data());
		__m128 u = _mm_load_ps(_U.data());
		__m128 res = _mm_add_ps(v, u);
		_mm_storeu_ps(result.data(), res);
		return result;
	}

	Vector<float, 4> operator-(const Vector<float, 4>& _V, const Vector<float, 4>& _U) noexcept
	{
		Vector<float, 4> result;
		__m128 v = _mm_load_ps(_V.data());
		__m128 u = _mm_load_ps(_U.data());
		__m128 res = _mm_sub_ps(v, u);
		_mm_storeu_ps(result.data(), res);
		return result;
	}


}