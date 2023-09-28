#pragma once

#include "type_decl.hpp"
#include <limits>
#include <numeric>

namespace ta
{
	template <class T, size_t Dim>
	Vector<T, Dim> normalize(const Vector<T, Dim> &vec)
	{
		auto rlen = 1.f / vec.length();
		return vec * rlen;
	}

	template <class U, class V>
	auto cross(const Vector<U, 3> &u, const Vector<V, 3> &v) noexcept -> Vector<decltype(detail::declval_by_mul<U, V>()), 3>
	{
		using return_type = detail::decltype_by_mul<U, V>;
		return Vector<return_type, 3>{
			u.y() * v.z() - u.z() * v.y(),
			u.z() * v.x() - u.x() * v.z(),
			u.x() * v.y() - u.y() * v.x()};
	}


	mat4 operator*(const mat4 &A, const mat4 &B) noexcept;

	mat4 transpose(const mat4 &mat) noexcept;

	vec4 operator*(const mat4 &mat, const vec4 &vec) noexcept;
	vec4 operator*(const vec4& vec, const mat4& mat) noexcept;
	
	mat4 look_at(vec3 pos, vec3 target, vec3 up) noexcept;

	mat4 perspective(float fovy, float aspect, float near, float far) noexcept;

	float rad(float deg) noexcept;

	mat4 rotate(const mat4& mat, const vec3& axis, float angle) noexcept;
}