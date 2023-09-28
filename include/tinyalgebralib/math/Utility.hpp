#pragma once

#include <type_traits>

namespace ta::detail
{
	template<class T, class U, bool Expr>
	using enable_if_t = std::enable_if_t<
		std::is_same_v<T, std::remove_reference_t<U>>&& Expr, U>;

	template<class, class...>
	struct is_same_pack {};

	template<class T, class U>
	struct is_same_pack<T, U>
	{
		static constexpr bool value = std::is_same_v<T, U>;
	};

	template<class T, class U, class... Args>
	struct is_same_pack<T, U, Args...>
	{
		static constexpr bool value = std::is_same_v<T, U> && is_same_pack<T, Args...>::value;
	};

	template<class T, class... Args>
	bool is_same_pack_v = is_same_pack<T, Args...>::value;

	template<class T, class U>
	auto declval_by_mul() noexcept -> decltype(std::declval<T>() * std::declval<U>())
	{
		static_assert(std::__declval_protector<T>::__stop, "declval() must not be used!");
      	return __declval<T>(0);
	}

	template<class T, class U>
	using decltype_by_mul = decltype(declval_by_mul<T, U>());
}