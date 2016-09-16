#pragma once
#include <ostream>
#include <vector>

template <class KY>
class NODE {
	private:
		KY data;
		NODE* next;
	public:
		
		KY get_data() {
			return data;
		}
		void set_data(KY d) {
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


template <class KY>
class linked_list {

	private:

		NODE<KY>* HEAD;
		NODE<KY>* CURR;
		NODE<KY>* TEMP;

	public:

		linked_list() { 
			HEAD = nullptr; 
			CURR = nullptr; 
			TEMP = nullptr; 
		};

		void add_node(KY data_add) {
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
			
		};

		void delete_node(KY data_del) {
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