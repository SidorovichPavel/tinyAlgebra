#pragma once

#include <array>
#include <algorithm>
#include <ranges>

#include <assert.h>
namespace ta
{

	template<class T, size_t M, size_t N>
	class Matrix
	{
		static_assert(M > 1, "Invalidate colomn size");
		static_assert(N > 1, "Invalidate row size");
		static_assert(std::is_arithmetic_v<T>, "T is not arithmetic type");

	public:
		using this_type = Matrix<T, M, N>;
		using value_type = T;
		using value_ref_type = T&;
		using iterator = T*;
		using const_iterator = const T*;

	private:

		alignas(16) value_type data_[M * N];

		std::pair<iterator, iterator> _get_range() noexcept
		{
			return { data_, data_ + M * N };
		}
		std::pair<const_iterator, const_iterator> _get_range() const noexcept
		{
			return { data_, data_ + M * N };
		}


	public:

		Matrix() noexcept
		{
			std::fill(data_, data_ + M * N, static_cast<T>(0));
		}

		Matrix(const T _Val) noexcept
		{
			std::fill(begin(), end(), static_cast<T>(0));
			static_assert(M == N, "Error matrix initialize. Matrix is not quadratic.");
			for (auto i = 0; i < M; i++)
				data_[i * N + i] = _Val;
		}

		Matrix(const this_type& other) noexcept
		{
			std::copy(other.begin(), other.end(), begin());
		}

		Matrix(this_type&& other) noexcept
		{
			std::copy(other.begin(), other.end(), begin());
		}

		Matrix(std::initializer_list<value_type> _Init_list)
		{
			std::copy(_Init_list.begin(), _Init_list.end(), begin());
		}

		template<std::ranges::range range>
		Matrix(std::initializer_list<range> list_of_ranges)
		{
			auto list_size = list_of_ranges.size();
			if (list_size <= M)
			{
				size_t idx = 0;
				for (auto&& r : list_of_ranges)
				{
					auto dist = std::distance(r.begin(), r.end());
					if (dist > N)
						continue;

					std::copy(r.begin(), r.end(), data_ + idx * N);
					idx++;
				}
			}
		}

		template <class... Args>
		Matrix(Args&&...args) noexcept {
			static_assert(sizeof...(Args) == (M * N), "Too many indices for construct");
			static_assert(((std::is_arithmetic_v<
				std::remove_cvref_t<Args>
			>) && ...), "Incorrect arguments type");

			auto it = begin();
			((*it++ = static_cast<T>(args)), ...);
		}


		Matrix(Matrix<T, (M - 1), (N - 1)>& other) noexcept {
			std::fill(begin(), end(), static_cast<T>(0));
			for (auto&& i : std::views::iota(0u, M - 1u))
				std::ranges::copy(other[i], (*this)[i].begin());
			data_[M * N - 1] = 1.f;
		}

		Matrix(const Matrix<T, (M - 1), (N - 1)>& other) noexcept {
			std::fill(begin(), end(), static_cast<T>(0));
			for (auto&& i : std::views::iota(0u, M - 1u))
				std::ranges::copy(other[i], (*this)[i].begin());
			data_[M * N - 1] = 1.f;
		}

		Matrix(Matrix<T, (M - 1), (N - 1)>&& other) noexcept {
			std::fill(begin(), end(), static_cast<T>(0));
			for (auto&& i : std::views::iota(0u, M - 1u))
				std::ranges::copy(other[i], (*this)[i].begin());
			data_[M * N - 1] = 1.f;
		}


		this_type& operator=(const this_type& _Right) noexcept
		{
			std::copy(_Right.begin(), _Right.end(), begin());
			return *this;
		}
		this_type& operator=(this_type&& _Right) noexcept
		{
			std::copy(_Right.begin(), _Right.end(), begin());
			return *this;
		}

		value_type* operator()(size_t i) noexcept
		{
			assert(i < M);
			return data_ + i * N;
		}

		const value_type* operator()(size_t i) const noexcept
		{
			assert(i < M);
			return data_ + i * N;
		}

		value_ref_type operator()(size_t i, size_t j) noexcept
		{
			assert(i < M);
			assert(j < N);
			return data_[i * N + j];
		}
		value_type operator()(size_t i, size_t j) const noexcept
		{
			assert(i < M);
			assert(j < N);
			return data_[i * N + j];
		}

		auto operator[](std::size_t i) noexcept {
			assert(i < M);
			return std::ranges::subrange(begin() + (i * N), begin() + ((i + 1) * N));
		}

		auto operator[](std::size_t i) const noexcept {
			assert(i < M);
			return std::ranges::subrange(begin() + (i * N), begin() + ((i + 1) * N));
		}

		value_ref_type at(size_t i, size_t j)
		{
			if (i >= M)
				throw std::runtime_error("Out of M range");
			if (j >= N)
				throw std::runtime_error("Out of N range");
			return data_[i * N + j];
		}

		value_type* data() noexcept
		{
			return data_;
		}

		const value_type* data() const noexcept
		{
			return data_;
		}

		iterator begin() noexcept
		{
			return data_;
		}
		const value_type* begin() const noexcept
		{
			return data_;
		}
		iterator end() noexcept
		{
			return data_ + (M * N);
		}
		const value_type* end() const noexcept
		{
			return data_ + (M * N);
		}

		std::string to_string() const
		{
			std::string result("[");
			for (auto&& [idx, e] : data_ | std::views::enumerate)
			{
				if (idx % N == 0)
					result += "{ ";

				result += std::to_string(e);

				if (idx % N == N - 1)
				{
					if ((idx / M) != (M - 1))
						result += "}\n";
				}
				else
					result += ", ";
			}
			result += "}]";
			return result;
		}

	};


}