#pragma once
#include <ostream>
#include <vector>

template <class T>
class NODE {
	private:
		T data;
		NODE* next;
	public:
		
		T get_data() {
			return data;
		}
		void set_data(T d) {
			data = d;
		}
		NODE* get_next() {
			return next;
		}
		void set_next(NODE* n) {
			next = n;
		}
		NODE() {};
		void print(std::ostream& out) {
			out << get_data();
		}
};


template <class T>
class linked_list {

	private:

		NODE<T>* HEAD;
		NODE<T>* CURR;
		NODE<T>* TEMP;

	public:

		linked_list() { 
			HEAD = nullptr; 
			CURR = nullptr; 
			TEMP = nullptr; 
		};

		void add_node(T data_add) {
			NODE<T>* n = new NODE<T>;
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
			
		};

		void delete_node(T data_del) {
			NODE<T>* delPtr = nullptr;
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

		};
		
		void print(std::ostream& out) {
			CURR = HEAD;
			while (CURR != nullptr) {
				CURR->print(out);
				out << " ";
				CURR = CURR->get_next();
			}
			out << "\n";
		};
};