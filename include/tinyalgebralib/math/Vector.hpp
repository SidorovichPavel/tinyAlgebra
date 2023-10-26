#pragma once

#include <array>
#include <algorithm>
#include <string>
#include <functional>
#include <cmath>

#include "Utility.hpp"

namespace ta
{
	namespace swz
	{
		constexpr size_t x = 0;
		constexpr size_t y = 1;
		constexpr size_t z = 2;
		constexpr size_t w = 3;
	}

	template <class T, size_t Dim>
	class Vector
	{
		static_assert(Dim > 1, "Invalidate Dimention");
		static_assert(std::is_arithmetic_v<T>, "Invaludate type");

	public:
		using value_type = T;
		using iterator = T*;
		using const_iterator = const T*;
		using this_type = Vector<T, Dim>;
		using value_ref_type = value_type&;

	private:
		value_type data_[Dim];

	public:
		constexpr std::pair<iterator, iterator> _get_range() noexcept
		{
			return { data_, data_ + Dim };
		}

		constexpr std::pair<const_iterator, const_iterator> _get_range() const noexcept
		{
			return { data_, data_ + Dim };
		}

		template <class Fn>
		Vector<T, Dim> transform_to_new(Fn&& _Func) const noexcept
		{
			Vector<T, Dim> result;
			auto [begin, end] = _get_range();
			auto [rbegin, _] = result._get_range();
			std::transform(begin, end, rbegin, _Func);
			return result;
		}

	public:

		constexpr Vector() noexcept
		{
			auto [begin, end] = _get_range();
			std::fill(begin, end, static_cast<T>(0));
		}

		constexpr Vector(T val) noexcept
		{
			auto [begin, end] = _get_range();
			std::fill(begin, end, val);
		}

		template<class U>
		constexpr Vector(Vector<U, Dim>& other) noexcept
		{
			std::copy(other.begin(), other.end(), data_);
		}

		template<class U>
		constexpr Vector(const Vector<U, Dim>& other) noexcept
		{
			std::copy(other.begin(), other.end(), data_);
		}

		template<class U>
		constexpr Vector(Vector<U, Dim>&& other) noexcept
		{
			std::copy(other.begin(), other.end(), data_);
		}

		constexpr Vector(std::initializer_list<T> init_list)
		{
			if (init_list.size() <= Dim)
				std::copy(init_list.begin(), init_list.end(), data_);
		}

		template<class U, class V>
		constexpr Vector(Vector<U, (Dim - 1)>& vec, V val) noexcept
		{
			auto [other_begin, other_end] = vec._get_range();
			std::copy(other_begin, other_end, data_);
			data_[Dim - 1] = static_cast<T>(val);
		}

		template<class U, class V>
		constexpr Vector(const Vector<U, (Dim - 1)>& vec, V val) noexcept
		{
			std::copy(vec.begin(), vec.end(), data_);
			data_[Dim - 1] = static_cast<T>(val);
		}

		template<class U, class V>
		constexpr Vector(Vector<U, (Dim - 1)>&& vec, V val) noexcept
		{
			std::copy(vec.begin(), vec.end(), data_);
			data_[Dim - 1] = static_cast<T>(val);
		}

		template<class U>
		constexpr Vector(Vector<U, (Dim + 1)>& vec) noexcept
		{
			auto [other_begin, _] = vec._get_range();
			std::copy_n(other_begin, Dim, data_);
		}

		template<class U>
		constexpr Vector(const Vector<U, (Dim + 1)>& vec) noexcept
		{
			auto [other_begin, _] = vec._get_range();
			std::copy_n(other_begin, Dim, data_);
		}

		template<class U>
		constexpr Vector(Vector<U, (Dim + 1)>&& vec) noexcept
		{
			auto [other_begin, _] = vec._get_range();
			std::copy_n(other_begin, Dim, data_);
		}

		template <class... Args>
		constexpr Vector(Args&&...args) noexcept
		{
			static_assert(sizeof...(Args) <= Dim, "Too many indices for construct");
			static_assert(((std::is_arithmetic_v<
				std::remove_cvref_t<Args>
			>) && ...), "Incorrect arguments type");

			auto it = begin();
			((*it++ = static_cast<T>(args)), ...);
		}

		constexpr ~Vector()
		{		}

		static constexpr size_t size() noexcept
		{
			return Dim;
		}

		template <class U>
		this_type& operator=(const Vector<U, Dim>& right) noexcept
		{
			auto [right_begin, right_end] = right._get_range();
			auto [begin, end] = _get_range();
			std::copy(right_begin, right_end, begin);
			return *this;
		}

		template <class U>
		this_type& operator=(Vector<U, Dim>&& right) noexcept
		{
			auto [right_begin, right_end] = right._get_range();
			auto [begin, end] = _get_range();
			std::copy(right_begin, right_end, begin);
			return *this;
		}

		constexpr this_type operator-() const noexcept
		{
			return transform_to_new([](auto e)
				{ return -e; });
		}

		constexpr this_type operator+() const noexcept
		{
			return *this;
		}

		value_ref_type operator[](size_t idx)
		{
			return data_[idx];
		}

		value_type operator[](size_t idx) const
		{
			return data_[idx];
		}

		template <class U>
		constexpr this_type& operator+=(const Vector<U, Dim>& right) noexcept
		{
			auto [right_begin, right_end] = right._get_range();
			auto [begin, end] = _get_range();
			std::transform(right_begin, right_end, begin, begin,
				[](auto a, auto b)
				{ return static_cast<T>(a + b); });
			return *this;
		}

		template <class U>
		constexpr this_type& operator-=(const Vector<U, Dim>& right) noexcept
		{
			auto [right_begin, right_end] = right._get_range();
			auto [begin, end] = _get_range();
			std::transform(begin, end, right_begin, begin,
				[](auto a, auto b)
				{ return static_cast<T>(a - b); });
			return *this;
		}

		template <class U>
		constexpr this_type& operator+=(const U& right) noexcept
		{
			auto [begin, end] = _get_range();
			std::transform(begin, end, begin,
				[&](auto a)
				{ return static_cast<T>(a + right); });
			return *this;
		}

		template <class U>
		constexpr this_type& operator-=(const U& right) noexcept
		{
			auto [begin, end] = _get_range();
			std::transform(begin, end, begin,
				[&](auto a)
				{ return static_cast<T>(a - right); });
			return *this;
		}

		template <class U>
		constexpr this_type& operator*=(const U& right) noexcept
		{
			auto [begin, end] = _get_range();
			std::transform(begin, end, begin,
				[&](auto a)
				{ return static_cast<T>(a * right); });
			return *this;
		}

		template <class U>
		constexpr this_type& operator/=(const U& right) noexcept
		{
			auto rright = 1.f / right;
			auto [begin, end] = _get_range();
			std::transform(begin, end, begin,
				[&](auto a)
				{ return static_cast<T>(a * rright); });
			return *this;
		}

		constexpr iterator begin() noexcept { return data_; }
		constexpr iterator end() noexcept { return data_ + Dim; }
		constexpr const_iterator begin() const noexcept { return data_; }
		constexpr const_iterator end() const noexcept { return data_ + Dim; }

		constexpr value_type* data() noexcept
		{
			return data_;
		}

		constexpr const value_type* data() const noexcept
		{
			return data_;
		}

		constexpr void* vdata() const noexcept
		{
			auto tmp = static_cast<const void*>(data_);
			return const_cast<void*>(tmp);
		}

		constexpr float length() const noexcept
		{
			return std::sqrt(static_cast<float>(dot2()));
		}

		constexpr value_type dot2() const noexcept
		{
			T res = static_cast<T>(0);
			for (auto& e : data_)
				res += e * e;
			return res;
		}

		std::string to_string() const
		{
			std::string result("{");
			bool not_first_value = false;
			for (auto& e : data_)
			{
				if (not_first_value)
					result += ", ";
				else
					not_first_value = true;

				result += std::to_string(e);
			}
			result += "}";
			return result;
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 0)> x() noexcept
		{
			return data_[0];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 0)> x() const noexcept
		{
			return data_[0];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 1)> y() noexcept
		{
			return data_[1];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 1)> y() const noexcept
		{
			return data_[1];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 2)> z() noexcept
		{
			return data_[2];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 2)> z() const noexcept
		{
			return data_[2];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 3)> w() noexcept
		{
			return data_[3];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 3)> w() const noexcept
		{
			return data_[3];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 0)> r() noexcept
		{
			return data_[0];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 0)> r() const noexcept
		{
			return data_[0];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 1)> g() noexcept
		{
			return data_[1];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 1)> g() const noexcept
		{
			return data_[1];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 2)> b() noexcept
		{
			return data_[2];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 2)> b() const noexcept
		{
			return data_[2];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U&, (Dim > 3)> a() noexcept
		{
			return data_[3];
		}

		template <class U = T>
		constexpr detail::enable_if_t<T, U, (Dim > 3)> a() const noexcept
		{
			return data_[3];
		}

		template <size_t... Indices>
		constexpr auto swizzle() const noexcept
		{
			static_assert(sizeof...(Indices) <= Dim, "Too many indices for swizzle");
			static_assert(((Indices < Dim) && ...), "Invalid swizzle index");

			Vector<T, sizeof...(Indices)> result;
			size_t idx = 0;
			((result[idx++] = (*this)[Indices]), ...);
			return result;
		}
	};

	template <class T, class U, size_t Dim>
	constexpr auto operator+(const Vector<T, Dim>& _V, const Vector<U, Dim>& _U) noexcept -> Vector<decltype(detail::declval_by_mul<T, U>()), Dim>
	{
		using return_type = decltype(detail::declval_by_mul<T, U>());

		Vector<return_type, Dim> result;
		auto [vbegin, vend] = _V._get_range();
		auto [ubegin, uend] = _U._get_range();
		auto [rbegin, rend] = result._get_range();

		std::transform(vbegin, vend, ubegin, rbegin,
			[](auto a, auto b)
			{ return static_cast<return_type>(a + b); });
		return result;
	}

	template <class T, class U, size_t Dim>
	constexpr auto operator-(const Vector<T, Dim>& _V, const Vector<U, Dim>& _U) noexcept -> Vector<decltype(detail::declval_by_mul<T, U>()), Dim>
	{
		using return_type = decltype(detail::declval_by_mul<T, U>());

		Vector<return_type, Dim> result;
		auto [vbegin, vend] = _V._get_range();
		auto [ubegin, uend] = _U._get_range();
		auto [rbegin, rend] = result._get_range();

		std::transform(vbegin, vend, ubegin, rbegin,
			[](auto a, auto b)
			{ return static_cast<return_type>(a - b); });
		return result;
	}

	constexpr Vector<float, 4> operator+(const Vector<float, 4>& _V, const Vector<float, 4>& _U) noexcept;
	constexpr Vector<float, 4> operator-(const Vector<float, 4>& _V, const Vector<float, 4>& _U) noexcept;

	template <class T, class U, size_t Dim>
	constexpr std::enable_if_t<std::is_arithmetic_v<U>, Vector<T, Dim>> operator*(const Vector<T, Dim>& vec, U _Val) noexcept
	{
		return vec.transform_to_new([_Val](auto e)
			{ return static_cast<T>(_Val * e); });
	}

	template <class T, class U, size_t Dim>
	constexpr std::enable_if_t<std::is_arithmetic_v<U>, Vector<T, Dim>> operator/(const Vector<T, Dim>& vec, U _Val) noexcept
	{
		return vec.transform_to_new([_Val](auto e)
			{ return static_cast<T>(e / _Val); });
	}

	template <class T, class U, size_t Dim>
	constexpr std::enable_if_t<std::is_arithmetic_v<U>, Vector<T, Dim>> operator*(U _Val, const Vector<T, Dim>& vec) noexcept
	{
		return vec.transform_to_new([_Val](auto e)
			{ return static_cast<T>(_Val * e); });
	}

	template <class T, class U, size_t Dim>
	constexpr std::enable_if_t<std::is_arithmetic_v<U>, Vector<T, Dim>> operator/(U _Val, const Vector<T, Dim>& vec) noexcept
	{
		return vec.transform_to_new([_Val](auto e)
			{ return static_cast<T>(_Val / e); });
	}
};
