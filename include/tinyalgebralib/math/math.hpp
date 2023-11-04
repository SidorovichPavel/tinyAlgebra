#pragma once

#include <limits>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <optional>

#include "type_decl.hpp"


namespace ta
{
	template <class T, size_t Dim>
	constexpr Vector<T, Dim> normalize(const Vector<T, Dim>& vec) noexcept
	{
		return vec / vec.length();
	}

	template <class U, class V>
	constexpr auto cross(const Vector<U, 3>& u, const Vector<V, 3>& v) noexcept -> Vector<decltype(detail::declval_by_mul<U, V>()), 3>
	{
		using return_type = detail::decltype_by_mul<U, V>;
		return Vector<return_type, 3>{
			u.y()* v.z() - u.z() * v.y(),
				u.z()* v.x() - u.x() * v.z(),
				u.x()* v.y() - u.y() * v.x()};
	}

	constexpr float dot(const vec3& v1, const vec3& v2)
	{
		return v1.x() * v2.x() +
			v1.y() * v2.y() +
			v1.z() * v2.z();
	}

	mat4 operator*(const mat4& A, const mat4& B) noexcept;

	mat4 transpose(const mat4& mat) noexcept;

	vec4 operator*(const mat4& mat, const vec4& vec) noexcept;
	vec4 operator*(const vec4& vec, const mat4& mat) noexcept;

	mat4 look_at(vec3 pos, vec3 target, vec3 up) noexcept;
	mat4 perspective(float fovy, float aspect, float near, float far) noexcept;
	mat4 viewport(int32_t xmin, int32_t ymin, int32_t width, int32_t height) noexcept;

	float rad(float deg) noexcept;

	mat4 scale(const mat4& mat, const vec3& size) noexcept;
	mat4 rotate(const mat4& mat, const vec3& axis, float angle) noexcept;
	mat4 translate(const mat4& mat, const vec3& offset) noexcept;

	std::optional<vec3> barycentric(vec2i vtx1, vec2i vtx2, vec2i vtx3, vec2i p) noexcept;
}