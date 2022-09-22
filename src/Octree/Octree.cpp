#include "Octree.hpp"

#include "..\math\math.hpp"

#include <algorithm>
#include <vector>
#include <queue>

namespace ta
{
	Node::Node() noexcept
		:
		mParent(nullptr),
		mVisitable(0)
	{
		std::fill_n(mChildren, OctNumber, nullptr);
	}

	Node::~Node() noexcept
	{
		for (size_t i = 0; i < OctNumber; i++)
			delete mChildren[i];
	}

	Node::Node(Node&& _Other) noexcept
		:
		mParent(nullptr),
		mVisitable(0)
	{
		std::fill_n(mChildren, OctNumber, nullptr);
		_swap(_Other);
	}

	Node::Node(const glm::vec3& _LowerBound, const glm::vec3 _UpperBound, ptr_t _Parent)
		:
		mBound(_LowerBound, _UpperBound),
		mParent(_Parent),
		mVisitable(0)
	{
		std::fill_n(mChildren, OctNumber, nullptr);
	}

	Node::Node(const BoundingBox& _Bound, ptr_t _Parent)
		:
		mBound(_Bound),
		mParent(_Parent),
		mVisitable(0)
	{
		std::fill_n(mChildren, OctNumber, nullptr);
	}

	Node& Node::operator=(Node&& _Right) noexcept
	{
		_swap(_Right);
		return *this;
	}

	Node* Node::get_parent() noexcept
	{
		return mParent;
	}

	bool Node::empty() noexcept
	{
		for (auto i = 0; i < OctNumber; i++)
			if (mChildren[i])
				return false;
		return true;
	}

	Node*& Node::operator[](size_t _Idx) noexcept
	{
		assert(_Idx < OctNumber);
		return mChildren[_Idx];
	}

	void Node::increase_visitable()
	{
		mVisitable++;
	}

	BoundingBox& Node::operator*() noexcept
	{
		return mBound;
	}

	BoundingBox* Node::operator->() noexcept
	{
		return &mBound;
	}



	void Node::_swap(Node& _Other) noexcept
	{
		std::swap(mBound, _Other.mBound);
		std::swap(mParent, _Other.mParent);
		std::swap(mChildren, _Other.mChildren);
		std::swap(mVisitable, _Other.mVisitable);
	}








	GeneratingOctree::GeneratingOctree(const glm::vec3& _PR, const glm::vec3& _Size, sdf_t&& _SDF) noexcept
		:
		mSpace(nullptr),
		mEdgesSize(_Size),
		mSDF(_SDF)
	{
		auto half_size = abs(_Size) / 2.f;
		mSpace = new(std::nothrow) Node(_PR - half_size, _PR + half_size, nullptr);
	}

	GeneratingOctree::~GeneratingOctree() noexcept
	{
		delete mSpace;
	}

	float GeneratingOctree::operator()(const glm::vec3& p) noexcept
	{
		if (mSDF)
			return mSDF(p);
		else
			return std::numeric_limits<float>::infinity();
	}

	float GeneratingOctree::get_vertices_weight(BoundingBox& box, sdf_t& sdf)
	{
		constexpr float max_vertices_weight = 8.f;
		float result = 0.f;
		for (int i = 0; i < BoxVertNumber; i++)
			if (sdf(box[i]) < 0.f)
				result += 1.f;

		return std::max(result, max_vertices_weight - result);
	}

	void GeneratingOctree::generate(glm::vec3 _MinGridSize)
	{
		if (!mSpace)
			return;

		std::queue<Node*> targets;
		targets.push(mSpace);

		for (; !targets.empty();)
		{
			auto node = targets.front();
			targets.pop();

			auto size = (*node)->size() / 2.f;
			auto point_region = (*node)->get_center();

			if (size.x < _MinGridSize.x ||
				size.y < _MinGridSize.y ||
				size.z < _MinGridSize.z)
				continue;

			auto [lo_bound, up_bound] = (*node)->get_bound();

			std::vector<BoundingBox> boxes;
			std::vector<float> vert_weight;
			for (auto i = 0; i < SubBoxNumber; i++)
			{
				auto offset = size * BoundingBox::offsets[i];
				BoundingBox box(lo_bound + offset, point_region + offset);
				if (get_vertices_weight(box, mSDF) != 8.f)
				{
					(*node)[i] = new Node(box, node);	// child[i]
					(*node).increase_visitable();
					targets.push((*node)[i]);			// push(child[i])
				}
			}
		}
	}

	Node::ptr_t GeneratingOctree::get_root()
	{
		return mSpace;
	}



}