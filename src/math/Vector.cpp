#include <tinyalgebralib/math/Vector.hpp>

#include <immintrin.h>

namespace ta {

    Vector<float, 4> operator+(const Vector<float, 4>& u, const Vector<float, 4>& v) noexcept {
        Vector<float, 4> result;
        __m128 uu = _mm_load_ps(u.data());
        __m128 vv = _mm_load_ps(v.data());
        __m128 res = _mm_add_ps(vv, uu);
        _mm_store_ps(result.data(), res);
        return result;
    }

    Vector<float, 4> operator-(const Vector<float, 4>& u, const Vector<float, 4>& v) noexcept {
        Vector<float, 4> result;
        __m128 uu = _mm_load_ps(u.data());
        __m128 vv = _mm_load_ps(v.data());
        __m128 res = _mm_sub_ps(uu, vv);
        _mm_store_ps(result.data(), res);
        return result;
    }

    Vector<float, 4> operator*(const Vector<float, 4>& vec, const float val) noexcept {
        Vector<float, 4> result;
        auto vval = _mm_set1_ps(val);
        auto vec128 = _mm_load_ps(vec.data());
        auto vres = _mm_mul_ps(vec128, vval);
        _mm_store_ps(result.data(), vres);
        return result;
    }

    Vector<float, 4> operator*(const float val, const Vector<float, 4>& vec) noexcept {
        Vector<float, 4> result;
        auto vval = _mm_set1_ps(val);
        auto vec128 = _mm_load_ps(vec.data());
        auto vres = _mm_mul_ps(vec128, vval);
        _mm_store_ps(result.data(), vres);
        return result;
    }

    Vector<float, 4> operator/(const Vector<float, 4>& vec, const float val) noexcept {
        Vector<float, 4> result;
        auto vval = _mm_set1_ps(1.f / val);
        auto vec128 = _mm_load_ps(vec.data());
        auto vres = _mm_mul_ps(vec128, vval);
        _mm_store_ps(result.data(), vres);
        return result;
    }

    Vector<float, 4> operator/(const float val, const Vector<float, 4>& vec) noexcept {
        Vector<float, 4> result;
        auto vval = _mm_set1_ps(1.f / val);
        auto vec128 = _mm_load_ps(vec.data());
        auto vres = _mm_mul_ps(vec128, vval);
        _mm_store_ps(result.data(), vres);
        return result;
    }

}