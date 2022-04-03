#include "BoundingBox.hpp"

namespace ta
{
	glm::vec3 BoundingBox::offsets[8] =
	{
		{0.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{1.0, 1.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0},
		{1.0, 0.0, 1.0},
		{1.0, 1.0, 1.0},
		{0.0, 1.0, 1.0}
	};


	BoundingBox::BoundingBox() noexcept
		:
		mLowerBound(0.f),
		mUpperBound(0.f)
	{	}


	BoundingBox::~BoundingBox() noexcept
	{	}

	BoundingBox::BoundingBox(const glm::vec3& _LowerBound, const glm::vec3& _UpperBound) noexcept
		:
		mLowerBound(_LowerBound),
		mUpperBound(_UpperBound)
	{	}

	void BoundingBox::bording(const glm::vec3 p, BoundingMode _BoundMode)
	{
		switch (_BoundMode)
		{
		case BoundingMode::Increase:
			mLowerBound.x = (mLowerBound.x > p.x) ? p.x : mLowerBound.x;
			mLowerBound.y = (mLowerBound.y > p.y) ? p.y : mLowerBound.y;
			mLowerBound.z = (mLowerBound.z > p.z) ? p.z : mLowerBound.z;

			mUpperBound.x = (mUpperBound.x < p.x) ? p.x : mUpperBound.x;
			mUpperBound.y = (mUpperBound.y < p.y) ? p.y : mUpperBound.y;
			mUpperBound.z = (mUpperBound.z < p.z) ? p.z : mUpperBound.z;
			break;
		case BoundingMode::Decrease:
			mLowerBound.x = (mLowerBound.x < p.x) ? p.x : mLowerBound.x;
			mLowerBound.y = (mLowerBound.y < p.y) ? p.y : mLowerBound.y;
			mLowerBound.z = (mLowerBound.z < p.z) ? p.z : mLowerBound.z;

			mUpperBound.x = (mUpperBound.x > p.x) ? p.x : mUpperBound.x;
			mUpperBound.y = (mUpperBound.y > p.y) ? p.y : mUpperBound.y;
			mUpperBound.z = (mUpperBound.z > p.z) ? p.z : mUpperBound.z;
			break;
		}
	}
	
	glm::vec3 BoundingBox::size()
	{
		return mUpperBound - mLowerBound;
	}

#pragma warning(push)
#pragma warning(disable:4715)
	glm::vec3 BoundingBox::operator[](uint8_t _Idx)
	{
		assert(_Idx < 8);
		switch (_Idx)
		{
		case 0: return mLowerBound;
		case 1: return glm::vec3(mUpperBound.x, mLowerBound.y, mLowerBound.z);
		case 2: return glm::vec3(mUpperBound.x, mUpperBound.y, mLowerBound.z);
		case 3: return glm::vec3(mLowerBound.x, mUpperBound.y, mLowerBound.z);
		case 4: return glm::vec3(mLowerBound.x, mLowerBound.y, mUpperBound.z);
		case 5: return glm::vec3(mUpperBound.x, mLowerBound.y, mUpperBound.z);
		case 6: return mUpperBound;
		case 7: return glm::vec3(mLowerBound.x, mUpperBound.y, mUpperBound.z);
		}
	}
#pragma warning(pop)

	std::pair<glm::vec3, glm::vec3> BoundingBox::get_bound()
	{
		return std::make_pair(mLowerBound, mUpperBound);
	}

	glm::vec3 BoundingBox::get_center()
	{
		return (mLowerBound + mUpperBound) / 2.f;
	}




}