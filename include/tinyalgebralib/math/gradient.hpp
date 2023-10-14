#pragma once

#include "..\glm\glm.hpp"
#include <type_traits>
#include <functional>

namespace ta
{
	template<class T, class SDF>
	auto gradient(const glm::vec<3, T>& p, SDF& sdf, T delta = static_cast<T>(1) + std::numeric_limits<T>::epsilon())
		-> std::enable_if_t<std::is_arithmetic_v<T> && std::is_same_v<decltype(sdf(p)), T>, glm::vec<3, T>>
	{
		using vec3 = glm::vec<3, T>;
		auto zero = static_cast<T>(0);
		vec3 dx(delta, zero, zero);
		vec3 dy(zero, delta, zero);
		vec3 dz(zero, zero, delta);

		vec3 grad = vec3(sdf(p)) - vec3(
			sdf(p - dx),
			sdf(p - dy),
			sdf(p - dz));

		return grad;
	}
}