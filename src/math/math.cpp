#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

#include <cmath>
#include <numbers>

#include <tinyalgebralib/math/math.hpp>

namespace ta
{

	template <class V, class U>
	auto cross(const Vector<V, 3> &v, const Vector<U, 3> &u) noexcept -> Vector<detail::decltype_by_mul<V, U>, 3>
	{
		using return_type = decltype(detail::declval_by_mul<V, U>());
		return Vector<return_type, 3>{
			v.y() * u.z() - v.z() * u.y(),
			v.z() * u.x() - v.x() * u.z(),
			v.x() * u.y() - v.y() * u.x()};
	}

	float dot2(const vec3 &v1, const vec3 &v2)
	{
		return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() + v2.z();
	}

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

	mat4 operator*(const mat4 &A, const mat4 &B) noexcept
	{
		mat4 result;

		result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0] + A[0][2] * B[2][0] + A[0][3] * B[3][0];
		result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1] + A[0][2] * B[2][1] + A[0][3] * B[3][1];
		result[0][2] = A[0][0] * B[0][2] + A[0][1] * B[1][2] + A[0][2] * B[2][2] + A[0][3] * B[3][2];
		result[0][3] = A[0][0] * B[0][3] + A[0][1] * B[1][3] + A[0][2] * B[2][3] + A[0][3] * B[3][3];

		result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0] + A[1][2] * B[2][0] + A[1][3] * B[3][0];
		result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1] + A[1][2] * B[2][1] + A[1][3] * B[3][1];
		result[1][2] = A[1][0] * B[0][2] + A[1][1] * B[1][2] + A[1][2] * B[2][2] + A[1][3] * B[3][2];
		result[1][3] = A[1][0] * B[0][3] + A[1][1] * B[1][3] + A[1][2] * B[2][3] + A[1][3] * B[3][3];

		result[2][0] = A[2][0] * B[0][0] + A[2][1] * B[1][0] + A[2][2] * B[2][0] + A[2][3] * B[3][0];
		result[2][1] = A[2][0] * B[0][1] + A[2][1] * B[1][1] + A[2][2] * B[2][1] + A[2][3] * B[3][1];
		result[2][2] = A[2][0] * B[0][2] + A[2][1] * B[1][2] + A[2][2] * B[2][2] + A[2][3] * B[3][2];
		result[2][3] = A[2][0] * B[0][3] + A[2][1] * B[1][3] + A[2][2] * B[2][3] + A[2][3] * B[3][3];

		result[3][0] = A[3][0] * B[0][0] + A[3][1] * B[1][0] + A[3][2] * B[2][0] + A[3][3] * B[3][0];
		result[3][1] = A[3][0] * B[0][1] + A[3][1] * B[1][1] + A[3][2] * B[2][1] + A[3][3] * B[3][1];
		result[3][2] = A[3][0] * B[0][2] + A[3][1] * B[1][2] + A[3][2] * B[2][2] + A[3][3] * B[3][2];
		result[3][3] = A[3][0] * B[0][3] + A[3][1] * B[1][3] + A[3][2] * B[2][3] + A[3][3] * B[3][3];

		return result;
	}

	vec4 operator*(const mat4 &mat, const vec4 &vec) noexcept
	{
		vec4 result;

		result[0] = mat[0][0] * vec[0] + mat[0][1] * vec[1] + mat[0][2] * vec[2] + mat[0][3] * vec[3];
		result[1] = mat[1][0] * vec[0] + mat[1][1] * vec[1] + mat[1][2] * vec[2] + mat[1][3] * vec[3];
		result[2] = mat[2][0] * vec[0] + mat[2][1] * vec[1] + mat[2][2] * vec[2] + mat[2][3] * vec[3];
		result[3] = mat[3][0] * vec[0] + mat[3][1] * vec[1] + mat[3][2] * vec[2] + mat[3][3] * vec[3];

		return result;
	}

	vec4 operator*(const vec4 &vec, const mat4 &mat) noexcept
	{
		vec4 result;

		result[0] = vec[0] * mat[0][0] + vec[0] * mat[1][0] + vec[0] * mat[2][0] + vec[0] * mat[3][0];
		result[1] = vec[1] * mat[0][1] + vec[1] * mat[1][1] + vec[1] * mat[2][1] + vec[1] * mat[3][1];
		result[2] = vec[2] * mat[0][2] + vec[2] * mat[1][2] + vec[2] * mat[2][0] + vec[2] * mat[3][2];
		result[3] = vec[3] * mat[0][3] + vec[3] * mat[1][3] + vec[3] * mat[2][3] + vec[3] * mat[3][3];

		return result;
	}

	mat4 look_at(vec3 pos, vec3 target, vec3 up) noexcept
	{
		vec3 camera_dir = normalize(pos - target);
		vec3 camera_right = normalize(cross(up, camera_dir));
		vec3 camera_up = cross(camera_dir, camera_right);

		mat4 a(1.f);

		a[0][0] = camera_right[0];
		a[0][1] = camera_right[1];
		a[0][2] = camera_right[2];

		a[1][0] = camera_up[0];
		a[1][1] = camera_up[1];
		a[1][2] = camera_up[2];

		a[2][0] = camera_dir[0];
		a[2][1] = camera_dir[1];
		a[2][2] = camera_dir[2];

		mat4 b(1.f);
		b[0][3] = -pos[0];
		b[1][3] = -pos[1];
		b[2][3] = -pos[2];

		return a * b;
	}

	float rad(float deg) noexcept
	{
		return 180.f * deg / std::numbers::pi;
	}

	mat4 perspective(float fovy, float aspect, float z_near, float z_far) noexcept
	{
		auto tg_half_fovy = std::tan(fovy / 2.f);
		auto rdist = 1.f / (z_far - z_near);

		mat4 result(0.f);

		result[0][0] = 1.f / (aspect * tg_half_fovy);
		result[1][1] = 1.f / (tg_half_fovy);
		result[2][2] = (z_far+z_near) * rdist;
		result[2][3] = -2 * z_far * z_near * rdist;
		result[3][2] = -1.f;

		return result;
	}

}