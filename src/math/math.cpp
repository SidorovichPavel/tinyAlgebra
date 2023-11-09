#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>

#include <cmath>
#include <numbers>

#include <tinyalgebralib/math/math.hpp>

namespace ta
{
	mat4 operator*(const mat4& A, const mat4& B) noexcept
	{
		mat4 result;

		auto b0 = _mm_loadu_ps(B(0));
		auto b1 = _mm_loadu_ps(B(1));
		auto b2 = _mm_loadu_ps(B(2));
		auto b3 = _mm_loadu_ps(B(3));

		for (int i = 0; i < 4; i++)
		{
			auto ai0 = _mm_set1_ps(A(i, 0));
			auto ai1 = _mm_set1_ps(A(i, 1));
			auto ai2 = _mm_set1_ps(A(i, 2));
			auto ai3 = _mm_set1_ps(A(i, 3));

			auto r = _mm_mul_ps(ai0, b0);
			r = _mm_fmadd_ps(ai1, b1, r);
			r = _mm_fmadd_ps(ai2, b2, r);
			r = _mm_fmadd_ps(ai3, b3, r);

			_mm_storeu_ps(result(i), r);
		}

		return result;
	}

	mat4 transpose(const mat4& mat) noexcept
	{
		mat4 result;

		__m128 row1 = _mm_loadu_ps(mat(0));
		__m128 row2 = _mm_loadu_ps(mat(1));
		__m128 row3 = _mm_loadu_ps(mat(2));
		__m128 row4 = _mm_loadu_ps(mat(3));

		_MM_TRANSPOSE4_PS(row1, row2, row3, row4);

		_mm_storeu_ps(result(0), row1);
		_mm_storeu_ps(result(1), row2);
		_mm_storeu_ps(result(2), row3);
		_mm_storeu_ps(result(3), row4);

		return result;
	}

	void invert4x4(const float* src, float* dst)
	{
		__m128 minor0, minor1, minor2, minor3;
		__m128 row0, row1, row2, row3;
		__m128 det, tmp1;

		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src + 4));
		row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src + 8)), (__m64*)(src + 12));

		row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
		row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);

		tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src + 2)), (__m64*)(src + 6));
		row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src + 10)), (__m64*)(src + 14));

		row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
		row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);

		tmp1 = _mm_mul_ps(row2, row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

		minor0 = _mm_mul_ps(row1, tmp1);
		minor1 = _mm_mul_ps(row0, tmp1);

		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

		minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
		minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
		minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

		tmp1 = _mm_mul_ps(row1, row2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

		minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
		minor3 = _mm_mul_ps(row0, tmp1);

		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
		minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
		minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

		tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
		row2 = _mm_shuffle_ps(row2, row2, 0x4E);

		minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
		minor2 = _mm_mul_ps(row0, tmp1);

		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

		minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
		minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
		minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

		tmp1 = _mm_mul_ps(row0, row1);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

		minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
		minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);

		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

		minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));

		tmp1 = _mm_mul_ps(row0, row3);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
		minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);

		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

		minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
		minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));

		tmp1 = _mm_mul_ps(row0, row2);
		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

		minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
		minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));

		tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

		minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
		minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);

		det = _mm_mul_ps(row0, minor0);
		det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
		det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);

		tmp1 = _mm_rcp_ss(det);

		det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
		det = _mm_shuffle_ps(det, det, 0x00);

		minor0 = _mm_mul_ps(det, minor0);
		_mm_storel_pi((__m64*)(dst), minor0);
		_mm_storeh_pi((__m64*)(dst + 2), minor0);

		minor1 = _mm_mul_ps(det, minor1);
		_mm_storel_pi((__m64*)(dst + 4), minor1);
		_mm_storeh_pi((__m64*)(dst + 6), minor1);

		minor2 = _mm_mul_ps(det, minor2);
		_mm_storel_pi((__m64*)(dst + 8), minor2);
		_mm_storeh_pi((__m64*)(dst + 10), minor2);

		minor3 = _mm_mul_ps(det, minor3);
		_mm_storel_pi((__m64*)(dst + 12), minor3);
		_mm_storeh_pi((__m64*)(dst + 14), minor3);
	}

	mat4 invert(const mat4& mat) noexcept
	{
		mat4 result;

		invert4x4(mat.data(), result.data());

		return result;
	}

	vec4 operator*(const mat4& mat, const vec4& vec) noexcept
	{
		vec4 result;

		result[0] = mat(0, 0) * vec[0] + mat(0, 1) * vec[1] + mat(0, 2) * vec[2] + mat(0, 3) * vec[3];
		result[1] = mat(1, 0) * vec[0] + mat(1, 1) * vec[1] + mat(1, 2) * vec[2] + mat(1, 3) * vec[3];
		result[2] = mat(2, 0) * vec[0] + mat(2, 1) * vec[1] + mat(2, 2) * vec[2] + mat(2, 3) * vec[3];
		result[3] = mat(3, 0) * vec[0] + mat(3, 1) * vec[1] + mat(3, 2) * vec[2] + mat(3, 3) * vec[3];

		return result;
	}

	vec4 operator*(const vec4& vec, const mat4& mat) noexcept
	{
		vec4 result;

		auto v0 = _mm_set1_ps(vec[0]);
		auto v1 = _mm_set1_ps(vec[1]);
		auto v2 = _mm_set1_ps(vec[2]);
		auto v3 = _mm_set1_ps(vec[3]);

		auto m0 = _mm_loadu_ps(mat(0));
		auto m1 = _mm_loadu_ps(mat(1));
		auto m2 = _mm_loadu_ps(mat(2));
		auto m3 = _mm_loadu_ps(mat(3));

		auto r = _mm_mul_ps(v0, m0);
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
			ta::vec4(camera_dir, 0.f),
			ta::vec4(0.f, 0.f, 0.f, 1.f)
			});

		mat4 b(1.f);
		b(0, 3) = -pos[0];
		b(1, 3) = -pos[1];
		b(2, 3) = -pos[2];

		return a * b;
	}

	float rad(float degs) noexcept
	{
		constexpr auto piondgr = std::numbers::pi / 180.f;
		return piondgr * degs;
	}

	mat4 perspective(float fovy, float aspect, float z_near, float z_far) noexcept
	{
		auto ctg_half_fovy = 1.f / std::tan(fovy / 2.f);
		auto rdist = 1.f / (z_far - z_near);

		mat4 result;

		result(0, 0) = ctg_half_fovy / aspect;
		result(1, 1) = ctg_half_fovy;
		result(2, 2) = (z_near - z_far) * rdist;
		result(2, 3) = -2 * z_far * z_near * rdist;
		result(3, 2) = -1.f;

		return result;
	}

	mat4 viewport(int32_t xmin, int32_t ymin, int32_t width, int32_t height) noexcept
	{
		auto half_width = width / 2.f;
		auto half_height = height / 2.f;
		return mat4({
			 half_width, 0.f, 0.f, xmin + half_width,
			0.f, -half_height, 0.f, ymin + half_height,
			0.f,0.f,1.f,0.f,
			0.f,0.f,0.f,1.f
			});
	}

	mat4 scale(const mat4& mat, const vec3& size) noexcept
	{
		mat4 scl(1.f);

		scl(0, 0) = size.x();
		scl(1, 1) = size.y();
		scl(2, 2) = size.z();

		return scl * mat;
	}

	mat4 rotate(const mat4& mat, const vec3& axis, float angle) noexcept
	{
		mat4 rtt;

		float sina = std::sin(angle);
		float cosa = std::cos(angle);

		float one_sub_cosa = 1 - cosa;
		float axis_xy = axis.x() * axis.y();
		float axis_xz = axis.x() * axis.z();
		float axis_yz = axis.y() * axis.z();

		rtt(0, 0) = cosa + axis.x() * axis.x() * one_sub_cosa;
		rtt(0, 1) = axis_xy * one_sub_cosa - axis.z() * sina;
		rtt(0, 2) = axis_xz * one_sub_cosa + axis.y() * sina;

		rtt(1, 0) = axis_xy + axis.z() * cosa;
		rtt(1, 1) = cosa + axis.y() * axis.y() * one_sub_cosa;
		rtt(1, 2) = axis_yz * one_sub_cosa - axis.x() * sina;

		rtt(2, 0) = axis_xz * one_sub_cosa - axis.y() * sina;
		rtt(2, 1) = axis_yz * one_sub_cosa + axis.x() * sina;
		rtt(2, 2) = cosa + axis.z() * axis.z() * one_sub_cosa;

		rtt(3, 3) = 1.f;

		return rtt * mat;
	}

	mat4 translate(const mat4& mat, const vec3& offset) noexcept
	{
		mat4 trlt(1.f);

		trlt(0, 3) = offset.x();
		trlt(1, 3) = offset.y();
		trlt(2, 3) = offset.z();

		return trlt * mat;
	}

	std::optional<vec3> barycentric(vec2i vtx1, vec2i vtx2, vec2i vtx3, vec2i p) noexcept {
		/* calculate the vector product to determine the barycentric coordinates */
		vec3 u = cross(vec3(vtx3[0] - vtx1[0], vtx2[0] - vtx1[0], vtx1[0] - p[0]),
			vec3(vtx3[1] - vtx1[1], vtx2[1] - vtx1[1], vtx1[1] - p[1]));

		/* check whether the triangle is degenerate (the area is zero) */
		if (std::abs(u.z()) > std::numeric_limits<float>::epsilon())
		{
			/* calculate and return result */
			auto rz = 1.f / u.z();
			return std::make_optional<ta::vec3>(1.f - (u.x() + u.y()) * rz, u.y() * rz, u.x() * rz);
		}

		return std::nullopt;
	}
}