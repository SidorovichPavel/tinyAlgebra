#pragma once

#include "..\glm\glm.hpp"

namespace ta
{
	enum class BoundingMode
	{
		Decrease,
		Increase
	};

	class BoundingBox
	{
	public:
		BoundingBox() noexcept;
		~BoundingBox() noexcept;

		BoundingBox(const BoundingBox&) = default;
		BoundingBox(BoundingBox&&) = default;

		BoundingBox& operator=(const BoundingBox&) = default;
		BoundingBox& operator=(BoundingBox&&) = default;

		BoundingBox(const glm::vec3& _LowerBound, const glm::vec3& _UpperBound) noexcept;

		void bording(const glm::vec3 p, BoundingMode _BoundMode);
		
		glm::vec3 size();
		
		glm::vec3 operator[](uint8_t _Idx);

		std::pair<glm::vec3, glm::vec3> get_bound();
		glm::vec3 get_center();

		static glm::vec3 offsets[8];
	private:
		glm::vec3 mLowerBound;
		glm::vec3 mUpperBound;

	};


}