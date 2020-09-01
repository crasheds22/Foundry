#pragma once

/**
* @class Octree
* @brief class implementing an octree
*
* @author Kristian
*/

#include <functional>
#include <iostream>

template <class T>
struct node {
	T info{};
	node* parent;
	node* children[8];

	node() : children() {
		// initialises children to nullptr
	}
};

template <class T>
class Octree {
public:
	/**
	* @brief constructor
	* 
	* @post octree is constructed with root = nullptr
	*/
	Octree();

	/**
	* @brief destructor
	* 
	* @post octree is destructed
	*/
	~Octree();
	
	/**
	* @brief function to insert node into tree
	* 
	* @param node<T> n - node to be inserted into tree
	*/
	void Insert(node<T> n);

	/**
	* @brief overload of previous insert function
	*	creates a new node and stores t into it and then inserts the new node into the tree
	* @param T t - value to be inserted into tree
	*/
	void Insert(T t);

	/**
	* @brief function to destroy tree
	*	calls Destroy() on root
	*/
	void DestroyTree();
protected:
	node<T>* root;
private:
	/**
	* @brief function to traverse the tree
	* 
	* @param node<T> n - node of type T to start traversing from
	* @param function f - function to perform on each node
	*/
	void Traverse(node<T> n, std::function<void(const T&)> f);
	void InsertNode(node<T> in, node<T> prev);

	/**
	* @brief function to destroy node and children
	* 
	* @param node<T> n - node to start from
	*/
	void Destroy(node<T> n);
};