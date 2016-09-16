#pragma once
#include <ostream>
#include <vector>

///////////////////////////////////////////////////////////////////////////////////////
/// Definition of the linked list node.
template <class KY>
class NODE {
	private:
		KY data;
		NODE* next;
	public:

		NODE() {};
		KY get_data() {return data;}
		void set_data(KY d) {data = d;}
		NODE* get_next() {return next;}
		void set_next(NODE* n) {next = n;}
		void print(std::ostream& out) {out << get_data();}

};
///////////////////////////////////////////////////////////////////////////////////////





///////////////////////////////////////////////////////////////////////////////////////
/// Prototype for the linked list template class
template <class KY>
class linked_list {

	private:

		NODE<KY>* HEAD;
		NODE<KY>* CURR;
		NODE<KY>* TEMP;

	public:

		linked_list();
		void add_node(KY data_add);
		void delete_node(KY data_del);
		void print(std::ostream& out);

};
///////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////
/// Implementation of the linked list template class

template<class KY>
inline linked_list<KY>::linked_list() {

	///
	/// Default constructor
	///

	HEAD = nullptr;
	CURR = nullptr;
	TEMP = nullptr;

}

template<class KY>
inline void 
linked_list<KY>::add_node(KY data_add) {

	NODE<KY>* n = new NODE<KY>;
	n->set_next(nullptr);
	n->set_data(data_add);

	if (HEAD != nullptr) {
		CURR = HEAD;
		while (CURR->get_next() != nullptr) {
			CURR = CURR->get_next();
		}
		CURR->set_next(n);
	}
	else {
		HEAD = n;
	}

}

template<class KY>
inline void 
linked_list<KY>::delete_node(KY data_del) {

	NODE<KY>* delPtr = nullptr;
	TEMP = HEAD;
	CURR = HEAD;
	while (CURR != nullptr && CURR->get_data() != data_del) {
		TEMP = CURR;
		CURR = CURR->get_next();
	}

	if (CURR == nullptr) {
		std::cerr << data_del << " was not in the list" << "\n";
		delete delPtr;
	}
	else {
		delPtr = CURR;
		CURR = CURR->get_next();
		TEMP->set_next(CURR);
		if (delPtr == HEAD) {
			HEAD = HEAD->get_next();
			TEMP = nullptr;
		}
		delete delPtr;
		std::cout << "The value " << data_del << " was deleted\n";
	}

}

template<class KY>
inline void 
linked_list<KY>::print(std::ostream & out) {

	CURR = HEAD;

	while (CURR != nullptr) {
		CURR->print(out);
		out << " ";
		CURR = CURR->get_next();
	}

	out << "\n";

}
