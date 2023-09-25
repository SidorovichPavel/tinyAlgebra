#pragma once

#include "type_decl.hpp"
#include <limits>

namespace ta
{
	template <class T, class U>
	auto cross(const Vector<T, 3>& _V, const Vector<U, 3>& _U) noexcept ->
		Vector<decltype(detail::declval_by_mul<T, U>()), 3>;
}