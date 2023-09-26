#pragma once

#include "type_decl.hpp"
#include <limits>

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

}