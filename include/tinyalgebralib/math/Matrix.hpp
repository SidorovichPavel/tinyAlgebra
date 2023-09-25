#pragma once

#include <array>
#include <algorithm>


#include "Vector.hpp"

namespace ta
{

	template<class T, size_t M, size_t N>
	class Matrix
	{
		static_assert(M > 1, "Invalidate colomn size");
		static_assert(N > 1, "Invalidate row size");
		//static_assert(std::is_arithmetic_v<T>, "T is not arithmetic type");

	public:
		using this_type = Matrix<T, M, N>;
		using row_type = Vector<T, N>;
		using column_type = Vector<T, N>;
		using value_type = T;
		using value_ref_type = T&;
		using iterator = row_type*;
		using const_iterator = const row_type*;

	public:
		row_type mData[M];

		std::pair<iterator, iterator> _get_range() noexcept
		{
			return { mData, mData + M };
		}
		std::pair<const_iterator, const_iterator> _get_range() const noexcept
		{
			return { mData, mData + M };
		}
	private:


	public:

		Matrix() noexcept
		{}
		Matrix(const T _Val) noexcept
		{
			static_assert(M == N, "Error matrix initialize. Matrix is not quadratic.");
			for (auto i = 0; i < M; i++)
				mData[i][i] = _Val;
		}

		Matrix(const this_type&) = default;
		Matrix(this_type&&) = default;

		Matrix(std::initializer_list<column_type> _Init_list)
		{
			std::copy(_Init_list.begin(), _Init_list.end(), begin());
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

		row_type& operator[] (size_t _Idx)
		{
			//assert(_Idx < M, "");
			return mData[_Idx];
		}
		row_type operator[] (size_t _Idx) const
		{
			//assert(_Idx < M, "");
			return mData[_Idx];
		}
		value_ref_type at(size_t _IdxI, size_t _IdxJ)
		{
			//assert((_IdxI < M)&& (_IdxJ < N), "");
			return mData[_IdxI][_IdxJ];
		}
		
		row_type* begin() noexcept
		{
			return mData;
		}
		const row_type* begin() const noexcept
		{
			return mData;
		}
		row_type* end() noexcept
		{
			return mData + M;
		}
		const row_type* end() const noexcept
		{
			return mData + M;
		}

		std::string to_string() const
		{
			std::string result("[");
			bool not_first_value = false;
			for (auto& e : mData)
			{
				if (not_first_value)
				{
					result += ",";
					result += "\n";
				}
				else
					not_first_value = true;

				result += e.to_string();
			}
			result += "]";
			return result;
		}

	};


}