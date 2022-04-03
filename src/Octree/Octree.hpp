#pragma once

#include <functional>

#include "..\glm\glm.hpp"
#include "BoundingBox.hpp"

namespace ta
{
	class Node
	{
	public:
		using ptr_t = Node*;
		using cptr_t = const Node*;

		Node() noexcept;
		~Node() noexcept;

		Node(const Node& _Other) = delete;
		Node& operator=(const Node& _Right) = delete;

		Node(Node&& _Other) noexcept;
		Node& operator=(Node&& _Right) noexcept;

		Node(const glm::vec3& _LowerBound, const glm::vec3 _UpperBound, ptr_t _Parent = nullptr);
		Node(const BoundingBox& _Bound, ptr_t _Parent = nullptr);

		ptr_t get_parent() noexcept;

		bool empty() noexcept;

		ptr_t& operator[](size_t _Idx) noexcept;
		void increase_visitable();

		BoundingBox& operator*() noexcept;
		BoundingBox* operator->() noexcept;

	private:
		void _swap(Node& _Other) noexcept;

		constexpr static size_t OctNumber = 8;

		BoundingBox mBound;
		ptr_t mParent;
		ptr_t mChildren[8];
		uint32_t mVisitable;
	};

	class Octree
	{
	public:
		using sdf_t = std::function<float(glm::vec3)>;

		Octree(const glm::vec3& _PR, const glm::vec3& _Size) noexcept;
		~Octree() noexcept;

		void generate(glm::vec3 _MinGridSize, sdf_t&& sdf);

		Node::ptr_t get_root();

	private:
		float get_vertices_weight(BoundingBox& box, sdf_t& sdf);

		constexpr static uint8_t BoxVertNumber = 8;
		constexpr static uint8_t SubBoxNumber = 8;
		glm::vec3 mEdgesSize;
		Node::ptr_t mSpace;
	};


}