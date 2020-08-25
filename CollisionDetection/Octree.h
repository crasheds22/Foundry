#pragma once

/**
* @class Octree
* @brief class implementing an octree
*
* @author Kristian
*/

template <class T>
struct node {
	T info;
	T* parent;
	T* children[8];

	node() : children() {
		// initialises children to nullptr
	}
};

template <class T>
class Octree {
public:
	/**
	* @brief constructor
	* @post octree is constructed with root = nullptr
	*/
	Octree();
	
protected:
	node<T>* root;
private:
	
};