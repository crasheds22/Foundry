#ifndef __QUADTREE_H__
#define __QUADTREE_H__

#include <vector>
#include <glm/vec2.hpp>
#include <unordered_map>

template<typename T>
class Node
{
public:
	Node(glm::vec2 min, glm::vec2 max, Node* parent);
	~Node();

	glm::vec2 Min;
	glm::vec2 Max;

	T Occupants[10];

	Node* Parent;
	Node* Children[4];
};

template <typename T>
class QuadTree
{
public:
	QuadTree(glm::vec2 min, glm::vec2 max);
	~QuadTree();

	void Insert(T item, glm::vec2 pos);
	void Update(T item, glm::vec2 pos);

	void Delete(T item);

private:
	Node* mRoot;
	
	std::unordered_map<T, Node*> mShortCut;

	void Insert(Node* node, T item, glm::vec2 pos);
	void Update(Node* node, T item, glm::vec2 pos);

	void Delete(Node* node, T item);

	void Split();
	void Collapse();
};

#endif
