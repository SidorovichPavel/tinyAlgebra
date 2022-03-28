#pragma once

#include "Utility.hpp"
#include "type_decl.hpp"

namespace ta
{
	template <class T, class U>
	auto cross(const Vector<T, 3>& _V, const Vector<U, 3>& _U) noexcept ->
		Vector<decltype(detail::declval_by_mul<T, U>()), 3>
	{
		using return_type = decltype(detail::declval_by_mul<T, U>());
		return Vector<return_type, 3>{
			_V.y()* _U.z() - _V.z() * _U.y(),
			_V.z()* _U.x() - _V.x() * _U.z(),
			_V.x()* _U.y() - _V.y() * _U.x()
		};
	}



}