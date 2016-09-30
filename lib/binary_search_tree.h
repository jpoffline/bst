#pragma once
#include <iostream>




///////////////////////////////////////////////////////////////////////////////////////
///
/// Definition of the binary search tree node.
///

template <typename KY, typename DT>
class bst_node {
	
	///
	/// Template parameters: 
	///		-> key type  (KY)
	///		-> data type (DT)
	///

	private:
		KY _key;
		DT _data;
		bst_node* _left;
		bst_node* _right;
		void _print(std::ostream& out) {
			out << "-------------------------------------------------\n"
				<< "BST NODE KEY: " << _key << "\n"
				<< "BST NODE DATA: \n" << _data << "\n"
				<< "-------------------------------------------------\n";
		}
	public:
		bst_node* get_left() {return _left;}
		bst_node* get_right() {return _right;}
		void set_left(bst_node* l) {_left = l;}
		void set_right(bst_node* r) {_right = r;}
		void set_key(KY k) {_key = k;}
		void set_data(DT d) { _data = d; }
		KY get_key() {return _key;}
		void print(std::ostream& out) { _print(out); }
};
///
///////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////
///
/// Prototype for the binary search tree template class
///

template <typename KY, typename DT>
class binary_search_tree {
	private:
		
		///
		///	Template parameters: 
		///		-> key type  (KY)
		///		-> data type (DT)
		///

		bst_node<KY, DT>* root;
		bst_node<KY, DT>* _create_leaf(KY key, DT data);
		void _add_leaf(KY key, DT data, bst_node<KY, DT>* ptr);
		void _print_in_order(bst_node<KY, DT>* ptr);
		bst_node<KY, DT>* _return_node(KY key, bst_node<KY, DT>* ptr);
		
		KY _find_smallest(bst_node<KY, DT>* ptr);
		void _remove_node(KY key, bst_node<KY, DT>* parent);
		void _remove_root_match();
		void _remove_match(bst_node<KY, DT>* parent, bst_node<KY, DT>* match, bool left);
		void _remove_subtree(bst_node<KY, DT>* ptr);

	public:

		binary_search_tree();
		~binary_search_tree();
		void add_leaf(KY key, DT data);
		void print_in_order();
		KY return_root_key();
		void print_children(KY key);
		KY find_smallest();
		void remove_node(KY key);
		void print_root();
		bst_node<KY, DT>* return_node(KY key);

};

///
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
///
/// Implementation of the binary search tree class
///

template <typename KY, typename DT>
void 
binary_search_tree<KY, DT>::print_root() {

	std::cout << "The binary tree root node:\n ";
	root->print(std::cout);
	std::cout << std::endl;

}


template<typename KY, typename DT>
inline bst_node<KY, DT>* 
binary_search_tree<KY, DT>::_create_leaf(KY key, DT data) {

	bst_node<KY, DT>* n = new bst_node<KY, DT>;
	n->set_key(key);
	n->set_data(data);
	n->set_left(nullptr);
	n->set_right(nullptr);
	return n;

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::_add_leaf(KY key, DT data, bst_node<KY, DT>* ptr) {

	if (root == nullptr) {
		root = _create_leaf(key, data);
	}
	else if (key < ptr->get_key()) {
		if (ptr->get_left() != nullptr) {
			_add_leaf(key, data, ptr->get_left());
		}
		else {
			ptr->set_left(_create_leaf(key, data));
		}
	}
	else if (key > ptr->get_key()) {
		if (ptr->get_right() != nullptr) {
			_add_leaf(key, data, ptr->get_right());
		}
		else {
			ptr->set_right(_create_leaf(key, data));
		}
	}
	else {
		std::cerr << "The key " << key << " has already been added to the tree\n";
	}

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::_print_in_order(bst_node<KY, DT>* ptr) {

	if (root != nullptr) {

		if (ptr->get_left() != nullptr) {
			_print_in_order(ptr->get_left());
		}

		ptr->print(std::cout);

		if (ptr->get_right() != nullptr) {
			_print_in_order(ptr->get_right());
		}

	}
	else {
		std::cerr << "The tree is empty\n";
	}

}


template<typename KY, typename DT>
inline bst_node<KY, DT>* 
binary_search_tree<KY, DT>::_return_node(KY key, bst_node<KY, DT>* ptr) {

	if (ptr != nullptr) {
		if (ptr->get_key() == key) {
			return ptr;
		}
		else {
			if (key < ptr->get_key()) {
				return _return_node(key, ptr->get_left());
			}
			else {
				return _return_node(key, ptr->get_right());
			}
		}
	}
	else {
		return nullptr;
	}

}


template<typename KY, typename DT>
inline bst_node<KY, DT>* 
binary_search_tree<KY, DT>::return_node(KY key) {

	return _return_node(key, root);

}


template<typename KY, typename DT>
inline KY 
binary_search_tree<KY, DT>::_find_smallest(bst_node<KY, DT>* ptr) {

	if (root == nullptr) {
		std::cerr << "The tree is empty" << std::endl;
		return KY(0);
	}
	else {
		if (ptr->get_left() != nullptr) {
			return _find_smallest(ptr->get_left());
		}
		else {
			return ptr->get_key();
		}
	}

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::_remove_node(KY key, bst_node<KY, DT>* parent) {

	if (root != nullptr) {
		if (root->get_key() == key) {
			_remove_root_match();
		}
		else {
			if (key < parent->get_key() && parent->get_left() != nullptr) {
				parent->get_left()->get_key() == key ?
					_remove_match(parent, parent->get_left(), true) :
					_remove_node(key, parent->get_left());
			}
			else if (key > parent->get_key() && parent->get_right() != nullptr) {
				parent->get_right()->get_key() == key ?
					_remove_match(parent, parent->get_right(), false) :
					_remove_node(key, parent->get_right());
			}
			else {
				std::cerr << "The key " << key << " was not found in the tree\n";
			}
		}
	}
	else {
		std::cerr << "the tree is empty" << std::endl;
	}

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::_remove_root_match() {

	if (root != nullptr) {
		bst_node<KY, DT>* delPtr = root;
		KY root_key = root->get_key();

		// root node has zero children
		if (root->get_left() == nullptr && root->get_right() == nullptr) {
			root = nullptr;
			delete delPtr;
		}
		// root node has one child
		else if (root->get_left() == nullptr && root->get_right() != nullptr) {
			root = root->get_right();
			delPtr->set_right(nullptr);
			delete delPtr;
			std::cout << "The root node with key " << root_key << " was deleted.\n ";
			std::cout << "The new root contains key " << root->get_key() << "\n";
		}
		else if (root->get_left() != nullptr && root->get_right() == nullptr) {
			root = root->get_left();
			delPtr->set_left(nullptr);
			delete delPtr;
			std::cout << "The root node with key " << root_key << " was deleted.\n ";
			std::cout << "The new root contains key " << root->get_key() << "\n";
		}
		// root node has two children
		else {
			KY smallest_in_right_subtree;
			smallest_in_right_subtree = _find_smallest(root->get_right());
			_remove_node(smallest_in_right_subtree, root);
			root->set_key(smallest_in_right_subtree);
			std::cout << "The root key containing key " << root_key << " was overwritten with key " << root->get_key() << "\n";
		}

	}
	else {
		std::cerr << "cannot remove root; the tree is empty" << std::endl;
	}

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::_remove_match(bst_node<KY, DT>* parent, bst_node<KY, DT>* match, bool left) {

	if (root != nullptr) {
		bst_node<KY, DT>* delPtr;
		KY match_key = match->get_key();
		KY smallest_in_right_subtree;

		if (match->get_left() == nullptr && match->get_right() == nullptr) {
			delPtr = match;
			left == true ?
				parent->set_left(nullptr) :
				parent->set_right(nullptr);

			delete delPtr;
			std::cout << "The key containing " << match_key << " was removed\n";
		}
		else if (match->get_left() == nullptr && match->get_right() != nullptr) {
			left == true ?
				parent->set_left(match->get_right()) :
				parent->set_right(match->get_right());

			match->set_right(nullptr);
			delPtr = match;
			delete delPtr;
			std::cout << "The key containing " << match_key << " was removed\n";
		}
		else if (match->get_left() != nullptr && match->get_right() == nullptr) {
			left == true ?
				parent->set_left(match->get_left()) :
				parent->set_right(match->get_left());

			match->set_left(nullptr);
			delPtr = match;
			delete delPtr;
			std::cout << "The key containing " << match_key << " was removed\n";
		}
		else {
			smallest_in_right_subtree = _find_smallest(match->get_right());
			_remove_node(smallest_in_right_subtree, match);
			match->set_key(smallest_in_right_subtree);
		}
	}
	else {
		std::cerr << "Cannot remove match: tree is empty\n";
	}

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::_remove_subtree(bst_node<KY, DT>* ptr) {

	///
	///	Method to recursively remove the subtree,
	/// starting at node "ptr".
	///

	if (ptr != nullptr) {
		if (ptr->get_left() != nullptr) {
			_remove_subtree(ptr->get_left());
		}
		else if (ptr->get_right() != nullptr) {
			_remove_subtree(ptr->get_right());
		}
		delete ptr;
	}

}


template<typename KY, typename DT>
inline 
binary_search_tree<KY, DT>::binary_search_tree() { 

	///
	///	Default constructor.
	///
	/// Set the root to point at nullptr.

	root = nullptr; 

}


template<typename KY, typename DT>
inline 
binary_search_tree<KY, DT>::~binary_search_tree() {

	///
	///	Default destructor.
	///
	/// Recursively remove the subtree, starting from the root node.
	///

	_remove_subtree(root); 

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::add_leaf(KY key, DT data) {
	///
	/// when adding leaves to the binary search tree, pass in two arguments:
	/// 1) the key value of the node: this will be used to index the nodes
	/// 2) the data attached to the node.
	///

	_add_leaf(key, data, root);

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::print_in_order() {

	_print_in_order(root);
	std::cout << std::endl;

}


template<typename KY, typename DT>
inline KY 
binary_search_tree<KY, DT>::return_root_key() {

	if (root != nullptr) {
		return root->get_key();
	}
	else {
		return KY(0);
	}

}


template<typename KY, typename DT>
inline void 
binary_search_tree<KY, DT>::print_children(KY key) {

	bst_node<KY, DT>* ptr = return_node(key);
	if (ptr != nullptr) {
		std::cout << "parent node = " << ptr->get_key() << "\n";
		ptr->get_left() == nullptr ?
			std::cout << "left child = null\n" :
			std::cout << "left child = " << ptr->get_left()->get_key() << std::endl;
		ptr->get_right() == nullptr ?
			std::cout << "right child = null\n" :
			std::cout << "right child = " << ptr->get_right()->get_key() << std::endl;
	}
	else {
		std::cerr << "the key " << key << " is not in the tree\n";
	}

}


template<typename KY, typename DT>
inline KY 
binary_search_tree<KY, DT>::find_smallest() {

	return _find_smallest(root);

}


template <typename KY, typename DT>
void 
binary_search_tree<KY, DT>::remove_node(KY key) {

	///
	///	Method to remove the node with key "key"
	///

	/// Call the private method to recursively remove
	/// a node with a given key, starting at the root node.
	_remove_node(key, root);

};