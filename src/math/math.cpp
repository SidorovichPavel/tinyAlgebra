#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

#include <cmath>
#include <numbers>

#include <tinyalgebralib/math/math.hpp>

namespace ta
{
	float dot(const vec3 &v1, const vec3 &v2)
	{
		return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() + v2.z();
	}

	Vector<float, 4> operator+(const Vector<float, 4> &_V, const Vector<float, 4> &_U) noexcept
	{
		Vector<float, 4> result;
		__m128 v = _mm_load_ps(_V.data());
		__m128 u = _mm_load_ps(_U.data());
		__m128 res = _mm_add_ps(v, u);
		_mm_storeu_ps(result.data(), res);
		return result;
	}

	Vector<float, 4> operator-(const Vector<float, 4> &_V, const Vector<float, 4> &_U) noexcept
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

		auto b0 = _mm_loadu_ps(B[0].data());
		auto b1 = _mm_loadu_ps(B[1].data());
		auto b2 = _mm_loadu_ps(B[2].data());
		auto b3 = _mm_loadu_ps(B[3].data());

		for (int i = 0; i < 4; i++)
		{
			__m128 r = _mm_setzero_ps();

			auto ai0 = _mm_set1_ps(A[i][0]);
			auto ai1 = _mm_set1_ps(A[i][1]);
			auto ai2 = _mm_set1_ps(A[i][2]);
			auto ai3 = _mm_set1_ps(A[i][3]);

			r = _mm_fmadd_ps(ai0, b0, r);
			r = _mm_fmadd_ps(ai1, b1, r);
			r = _mm_fmadd_ps(ai2, b2, r);
			r = _mm_fmadd_ps(ai3, b3, r);

			_mm_storeu_ps(result[i].data(), r);
		}

		return result;
	}

	mat4 transpose(const mat4 &mat) noexcept
	{
		mat4 result;

		for (int i = 0; i < 4; i++)
			for (int j = i; j < 4; j++)
			{
				result[i][j] = mat[j][i];
				result[j][i] = mat[i][j];
			}

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
		vec4 result(0.f);

		auto v0 = _mm_set1_ps(vec[0]);
		auto v1 = _mm_set1_ps(vec[1]);
		auto v2 = _mm_set1_ps(vec[2]);
		auto v3 = _mm_set1_ps(vec[3]);

		__m128 r = _mm_setzero_ps();

		auto m0 = _mm_loadu_ps(mat[0].data());
		auto m1 = _mm_loadu_ps(mat[1].data());
		auto m2 = _mm_loadu_ps(mat[2].data());
		auto m3 = _mm_loadu_ps(mat[3].data());

		r = _mm_fmadd_ps(v0, m0, r);
		r = _mm_fmadd_ps(v1, m1, r);
		r = _mm_fmadd_ps(v2, m2, r);
		r = _mm_fmadd_ps(v3, m3, r);

		_mm_storeu_ps(result.data(), r);

		return result;
	}

	mat4 look_at(vec3 pos, vec3 target, vec3 up) noexcept
	{
		vec3 camera_dir = normalize(pos - target);
		vec3 camera_right = normalize(cross(up, camera_dir));
		vec3 camera_up = cross(camera_dir, camera_right);

		mat4 a({
			ta::vec4(camera_right, 0.f),
			ta::vec4(camera_up, 0.f),
			ta::vec4(-camera_dir, 0.f),
			ta::vec4(ta::vec3(0.f), 1.f)
		});

		mat4 b(1.f);
		b[0][3] = -pos[0];
		b[1][3] = -pos[1];
		b[2][3] = -pos[2];

		return a * b;
	}

	float rad(float degs) noexcept
	{
		constexpr auto degsppi = std::numbers::pi / 180.f;
		return degsppi * degs;
	}

	mat4 perspective(float fovy, float aspect, float z_near, float z_far) noexcept
	{
		auto tg_half_fovy = std::tan(fovy / 2.f);
		auto rdist = 1.f / (z_far - z_near);

		mat4 result(0.f);

		result[0][0] = 1.f / (aspect * tg_half_fovy);
		result[1][1] = 1.f / (tg_half_fovy);
		result[2][2] = (z_near - z_far) * rdist;
		result[2][3] = -1.f;
		result[3][2] = -2 * z_far * z_near * rdist;

		return result;
	}

	mat4 scale(const mat4 &mat, const vec3 &size) noexcept
	{
		mat4 scl(1.f);

		scl[0][0] = size.x();
		scl[1][1] = size.y();
		scl[2][2] = size.z();

		return scl * mat;
	}

	mat4 rotate(const mat4 &mat, const vec3 &axis, float angle) noexcept
	{
		mat4 rtt;

		float sina = std::sin(angle);
		float cosa = std::cos(angle);

		float one_sub_cosa = 1 - cosa;
		float axis_xy = axis.x() * axis.y();
		float axis_xz = axis.x() * axis.z();
		float axis_yz = axis.y() * axis.z();

		rtt[0][0] = cosa + axis.x() * axis.x() * one_sub_cosa;
		rtt[0][1] = axis_xy * one_sub_cosa - axis.z() * sina;
		rtt[0][2] = axis_xz * one_sub_cosa + axis.y() * sina;

		rtt[1][0] = axis_xy + axis.z() * cosa;
		rtt[1][1] = cosa + axis.y() * axis.y() * one_sub_cosa;
		rtt[1][2] = axis_yz * one_sub_cosa - axis.x() * sina;

		rtt[2][0] = axis_xz * one_sub_cosa - axis.y() * sina;
		rtt[2][1] = axis_yz * one_sub_cosa + axis.x() * sina;
		rtt[2][2] = cosa + axis.z() * axis.z() * one_sub_cosa;

		rtt[3][3] = 1.f;

		return rtt * mat;
	}

	mat4 translate(const mat4 &mat, const vec3 &offset) noexcept
	{
		mat4 trlt(1.f);

		trlt[0][3] = offset.x();
		trlt[1][3] = offset.y();
		trlt[2][3] = offset.z();

		return trlt * mat;
	}

}