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

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> min(const Vector<T, Dim>& vec1, const Vector<T, Dim>& vec2) noexcept {
		Vector<T, Dim> result;
		std::transform(vec1.begin(), vec1.end(), vec2.begin(), result.begin(), [](const auto& a, const auto& b) {return std::min(a, b);});
		return result;
	}

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> min(const Vector<T, Dim>& vec, const T& val) noexcept {
		Vector<T, Dim> result;
		std::transform(vec.begin(), vec.end(), result.begin(), [&val](const auto& a) {return std::min(a, val);});
		return result;
	}

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> min(const T& val, const Vector<T, Dim>& vec) noexcept {
		Vector<T, Dim> result;
		std::transform(vec.begin(), vec.end(), result.begin(), [&val](const auto& a) {return std::min(a, val);});
		return result;
	}

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> max(const Vector<T, Dim>& vec1, const Vector<T, Dim>& vec2) noexcept {
		Vector<T, Dim> result;
		std::transform(vec1.begin(), vec1.end(), vec2.begin(), result.begin(), [](const auto& a, const auto& b) {return std::max(a, b);});
		return result;
	}

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> max(const Vector<T, Dim>& vec, const T& val) noexcept {
		Vector<T, Dim> result;
		std::transform(vec.begin(), vec.end(), result.begin(), [&val](const auto& a) {return std::max(a, val);});
		return result;
	}

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> max(const T& val, const Vector<T, Dim>& vec) noexcept {
		Vector<T, Dim> result;
		std::transform(vec.begin(), vec.end(), result.begin(), [&val](const auto& a) {return std::max(a, val);});
		return result;
	}

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> clamp(const Vector<T, Dim>& val, const Vector<T, Dim>& lo, const Vector<T, Dim>& hi) noexcept {
		Vector<T, Dim> result;
		auto vbegin = val.begin();
		auto vend = val.end();
		auto lobegin = lo.begin();
		auto hibegin = hi.begin();
		auto resbegin = result.begin();
		for (;vbegin != vend;
			vbegin++,
			lobegin++,
			hibegin++,
			resbegin++)
			*resbegin = std::clamp(*vbegin, *lobegin, *hibegin);

		return result;
	}

	template<class T, std::size_t Dim>
	constexpr Vector<T, Dim> clamp(const Vector<T, Dim>& val, const T& lo, const T& hi) noexcept {
		return val.transform_to_new([&lo, &hi](const auto& v) {return std::clamp(v, lo, hi);});
	}

	template<std::size_t Dim>
	constexpr Vector<float, Dim> ceil(const Vector<float, Dim>& vec) noexcept {
		return vec.transform_to_new([](auto e) {return std::ceil(e);});
	}

	template<std::size_t Dim>
	constexpr Vector<double, Dim> ceil(const Vector<double, Dim>& vec) noexcept {
		return vec.transform_to_new([](auto e) {return std::ceil(e);});
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

	mat4 invert(const mat4& mat) noexcept;

	vec4 operator*(const mat4& mat, const vec4& vec) noexcept;
	vec4 operator*(const vec4& vec, const mat4& mat) noexcept;

	template <class T>
	constexpr T det(Matrix<T, 4, 4> const& m) noexcept
	{
		const ta::Matrix<T, 2, 2> A(m(0, 0), m(0, 1), m(1, 0), m(1, 1));
		const ta::Matrix<T, 2, 2> B(m(0, 2), m(0, 3), m(1, 2), m(1, 3));
		const ta::Matrix<T, 2, 2> C(m(2, 0), m(2, 1), m(3, 0), m(3, 1));
		const ta::Matrix<T, 2, 2> D(m(2, 2), m(2, 3), m(3, 2), m(3, 3));

		return det(A - B * inv(D) * C) * det(D);
	}

	mat4 look_at(vec3 pos, vec3 target, vec3 up) noexcept;
	mat4 perspective(float fovy, float aspect, float near, float far) noexcept;
	mat4 viewport(int32_t xmin, int32_t ymin, int32_t width, int32_t height) noexcept;

	float rad(float deg) noexcept;

	mat4 scale(const mat4& mat, const vec3& size) noexcept;
	mat4 rotate(const mat4& mat, const vec3& axis, float angle) noexcept;
	mat4 translate(const mat4& mat, const vec3& offset) noexcept;

	std::optional<vec3> barycentric(vec2i vtx1, vec2i vtx2, vec2i vtx3, vec2i p) noexcept;
}