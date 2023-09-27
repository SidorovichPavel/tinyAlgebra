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

	template <class T, class U>
	auto cross(const Vector<T, 3> &_V, const Vector<U, 3> &_U) noexcept -> Vector<detail::decltype_by_mul<T, U>, 3>;

	mat4 operator*(const mat4 &A, const mat4 &B) noexcept;

	vec4 operator*(const mat4 &mat, const vec4 &vec) noexcept;
	vec4 operator*(const vec4& vec, const mat4& mat) noexcept;
	
	mat4 look_at(vec3 pos, vec3 target, vec3 up) noexcept;

	mat4 perspective(float fovy, float aspect, float near, float far) noexcept;

	float rad(float deg) noexcept;
}