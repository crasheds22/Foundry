#include "Octree.h"

template <class T>
Octree<T>::Octree() {
	root = nullptr;
}

template <class T>
Octree<T>::~Octree() {
	Destroy(root);
	delete root;
}

template <class T>
void Octree<T>::Traverse(node<T> n, std::function<void(const T&)> f) {
	for (int i = 0; i < 8; i++) {
		if (n.children[i] != nullptr) {
			f(n.children[i]->info);
		} // end if
	} // end for
}

template <class T>
void Octree<T>::InsertNode(node<T> in, node<T> prev) {
	
}

template <class T>
void Octree<T>::Insert(node<T> n) {
	if (root == nullptr) {
		root = n;
	} // end if
	else {
		InsertNode(n, root);
	} // end else
}

template <class T>
void Octree<T>::Insert(T t) {
	node<T> temp;
	temp.info = t;

	if (root == nullptr) {
		root = temp;
	} // end if
	else {
		InsertNode(temp, root);
	} // end else
}

template <class T>
void Octree<T>::Destroy(node<T> n) {
	for (int i = 0; i < 8; i++) {
		if (n.children[i] != nullptr) {
			Destroy(n.children[i]);
		} // end if
		delete n.children[i];
	} // end for
	
	delete n.parent;
}

template <class T>
void Octree<T>::DestroyTree() {
	Destroy(root);
	delete root;
}