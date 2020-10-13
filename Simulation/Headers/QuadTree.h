#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <array>
#include <glm/vec2.hpp>
#include <unordered_map>

template<typename T>
class Node
{
public:
	Node(glm::vec2 min, glm::vec2 max, Node* parent)
	{
		Parent = parent;

		MinBound = min;
		MaxBound = max;

		Children[0] = nullptr;
		Children[1] = nullptr;
		Children[2] = nullptr;
		Children[3] = nullptr;

		Occupants = std::array<T, 10>();
	}

	Node* Parent;
	Node* Children[4];

	glm::vec2 MinBound;
	glm::vec2 MaxBound;

	std::array<T, 10> Occupants;
};

template <typename T>
class QuadTree
{
public:
	QuadTree(glm::vec2 min, glm::vec2 max)
	{
		mRoot = new Node(min, max, nullptr);
	}

	~QuadTree()
	{
		if (mRoot->Children[0] != nullptr)
		{
			Delete(mRoot->Children[0]);
			delete mRoot->Children[0];
			mRoot->Children[0] = nullptr;
		}

		if (mRoot->Chidlren[1] != nullptr)
		{
			Delete(mRoot->Children[1]);
			delete mRoot->Children[1];
			mRoot->Children[1] = nullptr;
		}

		if (mRoot->Children[2] != nullptr)
		{
			Delete(mRoot->Children[2]);
			delete mRoot->Children[2];
			mRoot->Children[2] = nullptr;
		}

		if (mRoot->Children[3] != nullptr)
		{
			Delete(mRoot->Children[3]);
			delete mRoot->Children[3];
			mRoot->Children[3] = nullptr;
		}

		delete mRoot;
		mRoot = nullptr;
	}

	void Insert(T& object, glm::vec2 position)
	{

	}

private:
	Node* mRoot;

	void Delete(Node* node)
	{
		if (node->Children[0] != nullptr)
		{
			Delete(node->Children[0]);
			delete node->Children[0];
			node->Children[0] = nullptr;
		}
		if(node->Children[1] != nullptr)
		{
			Delete(node->Children[1]);
			delete node->Children[1];
			node->Children[1] = nullptr;
		}
		if(node->Children[2] != nullptr)
		{
			Delete(node->Children[2]);
			delete node->Children[2];
			node->Children[2] = nullptr;
		}
		if(node->Children[3] != nullptr)
		{
			Delete(node->Children[3]);
			delete node->Children[3];
			node->Children[3] = nullptr;
		}

		node->Parent = nullptr;
	}

	void Insert(Node* node, T& object, glm::vec2 position)
	{

	}
};

#endif
