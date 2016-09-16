#pragma once
#include <iostream>

template <typename K, typename D>
class bst_node {
	///
	///	node element of the binary search tree.
	///
	/// - template: key type, data type
	///
	private:
		K key;
		D data;
		bst_node* left;
		bst_node* right;
	public:
		bst_node* get_left() {return left;}
		bst_node* get_right() {return right;}
		void set_left(bst_node* l) {left = l;}
		void set_right(bst_node* r) {right = r;}
		void set_key(K k) {key = k;}
		void set_data(D d) { data = d; }
		K get_key() {return key;}
		void print(std::ostream& out) {
			out << "KEY: "  << get_key() << "\n" 
				<< "DATA: " << data      << "\n";
		}
};

template <typename T, typename D>
class binary_search_tree {
	private:
		
		///
		/// binary search tree
		///
		///	- template: key type, data type

		bst_node<T, D>* root;

		bst_node<T, D>* _create_leaf(T key, D data) {
			bst_node<T, D>* n = new bst_node<T, D>;
			n->set_key(key);
			n->set_data(data);
			n->set_left(nullptr);
			n->set_right(nullptr);
			return n;
		};

		void _add_leaf(T key, D data, bst_node<T, D>* ptr) {
			if (root == nullptr) root = _create_leaf(key, data);
			else if(key < ptr->get_key()){
				if (ptr->get_left() != nullptr)_add_leaf(key, data, ptr->get_left());
				else ptr->set_left(_create_leaf(key, data));
			}
			else if (key > ptr->get_key()) {
				if (ptr->get_right() != nullptr) _add_leaf(key, data, ptr->get_right());
				else ptr->set_right(_create_leaf(key, data));
			}
			else {
				std::cerr << "The key " << key << " has already been added to the tree\n";
			}
		};

		void _print_in_order(bst_node<T, D>* ptr) {
		
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
		
		};

		bst_node<T, D>* _return_node(T key, bst_node<T, D>* ptr) {

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

		};

		bst_node<T, D>* return_node(T key) {

			return _return_node(key, root);

		};

		T _find_smallest(bst_node<T, D>* ptr) {
		
			if (root == nullptr) {
				std::cerr << "The tree is empty" << std::endl;
				return T(0);
			}
			else {
				if (ptr->get_left() != nullptr) {
					return _find_smallest(ptr->get_left());
				}
				else {
					return ptr->get_key();
				}
			}
		
		};

		void _remove_node(T key, bst_node<T, D>* parent) {
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
		};

		void _remove_root_match() {
			if (root != nullptr) {
				bst_node<T, D>* delPtr = root;
				T root_key = root->get_key();
				
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
					T smallest_in_right_subtree;
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

		void _remove_match(bst_node<T, D>* parent, bst_node<T, D>* match, bool left) {
			if (root != nullptr) {
				bst_node<T, D>* delPtr;
				T match_key = match->get_key();
				T smallest_in_right_subtree;

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

		void _remove_subtree(bst_node<T, D>* ptr) {
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

	public:

		binary_search_tree() {root = nullptr;};

		~binary_search_tree() { _remove_subtree(root); };

		void add_leaf(T key, D data) {
			///
			/// when adding leaves to the binary search tree, pass in two arguments:
			/// 1) the key value of the node: this will be used to index the nodes
			/// 2) the data attached to the node.
			///
			
			_add_leaf(key, data, root);

		};

		void print_in_order() { 
			_print_in_order(root); 
			std::cout << std::endl; 
		};

		T return_root_key() {
		
			if (root != nullptr) {
				return root->get_key();
			}
			else {
				return T(0);
			}
			
		};

		void print_children(T key) {
			bst_node<T, D>* ptr = return_node(key);
			if (ptr != nullptr) {
				std::cout << "parent node = " << ptr->get_key() << "\n";
				ptr->get_left() == nullptr  ? std::cout << "left child = null\n"  : std::cout << "left child = "  << ptr->get_left()->get_key()  << std::endl;
				ptr->get_right() == nullptr ? std::cout << "right child = null\n" : std::cout << "right child = " << ptr->get_right()->get_key() << std::endl;
			}
			else {
				std::cerr << "the key " << key << " is not in the tree\n";
			}
		}

		T find_smallest() { 
			return _find_smallest(root); 
		};

		void remove_node(T key) {
			_remove_node(key, root);
		};

		void print_root() {
			std::cout << "The root has key ";
			root->print(std::cout);
			std::cout << std::endl;
		}

};

