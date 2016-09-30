// dataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "../lib/linked_list.h"
#include "../lib/binary_search_tree.h"
#include "../lib/data_structure_types.h"
#include "../lib/complex_number.h"
#include "../lib/hashtable.h"
#include <time.h>
EVENT_PROXY_COLLECTION<int, int, int>
gen_event_pc(int N) {
	/// Quick function to generate and return 
	/// "an event" with a set of proxies and haz bins.
	EVENT_PROXY_COLLECTION<int, int, int> this_event;
	this_event.set_eventid(N);
	for (int i = 0; i < N; i++) {
		int pid = i + 1;
		int hid = (i + 1)*(i + i) * N;
		this_event.add_pair(pid, hid);
	}
	return this_event;
}

void event_proxy_collection_example() {

	binary_search_tree<int, EVENT_PROXY_COLLECTION<int, int, int>> myTreeEvent_pc;


	auto this_event = gen_event_pc(10);
	myTreeEvent_pc.add_leaf(this_event.get_eventid(), this_event);
	this_event = gen_event_pc(5);
	myTreeEvent_pc.add_leaf(this_event.get_eventid(), this_event);
	//std::cout << this_event.get_eventid() << std::endl;

	myTreeEvent_pc.print_root();
	myTreeEvent_pc.print_in_order();

}

void event_example() {

	/////////////////////////////// EVENT EXAMPLE ///////////////////////////////////////////
	/// Here we construct a binary search tree.
	/// The tree will be over "events".
	/// An event is defined as the triple of items: eventid, proxyid, and hazbin.
	/// The data structure defining this allows for arbitrary data types for each item.
	/// Every node of the binary search tree will contain an "event", and the
	/// nodes key will be the eventid.

	/// Define two events: the eventid, proxyid, and hazbin types are all ints.
	EVENT<int, int, int> my_event, my_event2;
	my_event.set_eventid(1001);
	my_event.set_hazbin(21);
	my_event.set_proxyid(891);
	my_event2.set_eventid(100);
	my_event2.set_hazbin(21);
	my_event2.set_proxyid(891);

	/// Boot up a bst for the event.
	/// The key type is int (and will be the eventid),
	/// and the data attached to each node is the event.
	binary_search_tree<int, EVENT<int, int, int>> myTreeEvent;
	myTreeEvent.add_leaf(my_event.get_eventid(), my_event);
	myTreeEvent.add_leaf(my_event2.get_eventid(), my_event2);

	std::cout << "Printing the BST in order\n";
	myTreeEvent.print_in_order();

	std::cout << "Find and return the node with key = " << 1001 << "\n";
	auto n = myTreeEvent.return_node(1001);
	n->print(std::cout);

	/////////////////////////////// EVENT EXAMPLE ///////////////////////////////////////////

}

void points_example() {

	POINTS p1;
	POINTS p2;
	p1.add(2);
	p1.add(3);
	p1.add(5);
	p2.add(4);
	p2.add(5);
	p2.add(6);


	binary_search_tree<double, POINTS> myPTree;
	myPTree.add_leaf(p1.vec_size(), p1);
	myPTree.add_leaf(p2.vec_size(), p1);
	myPTree.print_in_order();


	int keys[16] = { 50,76,21,4,32,64,15,52,14,100,83,2,3,70,87,80 };

	binary_search_tree<int, int> myTree;
	myTree.print_in_order();
	for (int i = 0; i < 16; i++) {
		myTree.add_leaf(keys[i], keys[i]);
	}
	myTree.print_in_order();
	myTree.print_children(myTree.return_root_key());
	//myTree.print_children(32);
	std::cout << "smallest value in tree: " << myTree.find_smallest() << std::endl;

	int input = 0;
	std::cout << "enter a key value to delete. -1 to stop\n";
	while (input != -1) {
		std::cout << "delete node: ";
		std::cin >> input;
		{
			if (input != -1) {
				std::cout << std::endl;
				myTree.remove_node(input);
				//myTree.print_root();
				myTree.print_in_order();
				std::cout << std::endl;
			}
		}
	}

}

std::vector<std::vector<int>> 
gen_matrix(int nrows, int ncols) {
	std::vector<std::vector<int>> matrix;
	for (int i = 0; i < nrows; i++) {
		std::vector<int> row;
		row.reserve(ncols);
		for (int j = 0; j < ncols; j++) {
			row.push_back(j + i);
		}
		matrix.push_back(row);
	}
	return matrix;
}

void matrix_row_traversal(int nrows, int ncols, std::vector<std::vector<int>> matrix) {
	
	int result = 0;

	for (int row = 0; row < nrows; row++) {
		for (int col = 0; col < ncols; col++) {
			//std::cout << matrix[row][col] << " ";
			result = matrix[row][col] + 1;
		}
	}

}

void matrix_col_traversal(int nrows, int ncols, std::vector<std::vector<int>> matrix) {

	int result = 0;

	for (int col = 0; col < ncols; col++) {
		for (int row = 0; row < nrows; row++) {
			//std::cout << matrix[row][col] << " ";
			result = matrix[row][col] + 1;
		}
	}

}



double run_test(int log_2_size, int ntests) {

	double sum = 0.0;

	int nrows = 1 << log_2_size;
	int ncols = 1 << log_2_size;
	auto matrix = gen_matrix(nrows, ncols);

	for (int test = 0; test < ntests; test++) {
		clock_t t_start_row = clock();
		matrix_row_traversal(nrows, ncols, matrix);
		clock_t t_end_row = clock();

		clock_t t_start_col = clock();
		matrix_col_traversal(nrows, ncols, matrix);
		clock_t t_end_col = clock();

		auto delta_row = t_end_row - t_start_row;
		auto delta_col = t_end_col - t_start_col;
		auto frac = (double)delta_col / (double)delta_row;
		sum += frac;
	}
	return sum / (double)ntests;

}

class item {
private:
	public:
		std::string name;
		std::string drink;
		int age;
		item() {};
		~item() {};
		item(std::string n, std::string d, int a = 12) { name = n; drink = d; age = a; }
		friend std::ostream &operator <<(std::ostream& out, const item& p) {
			out
				<< "(" << p.name << ", " << p.drink << ", " << p.age << ")";
			return out;
		}
		std::string hashablekey() { return name+drink; }
};


void hash_tester() {

	/// Initialise a hashtable object.
	/// Pass in as template arguments the 
	/// bucket data type, and the data type of the nodes.
	hashtable<linked_list<item>, item> gash(30);

	/// Add items to the hash table
	gash.add_item("J", item("Jonathan", "coffee", 28));
	gash.add_item("M", item("Matt", "juice", 90));
	gash.add_item("M", item("Mattt", "juice", 31));
	gash.add_item("A", item("Jonathan", "coffee", 28));
	gash.add_item(item("Matt", "juice", 90));
	gash.add_item("C", item("Mattt", "juice", 31));
	gash.add_item("D", item("Jonathan", "coffee", 28));
	gash.add_item("E", item("Matt", "juice", 90));
	gash.add_item("F", item("Mattt", "juice", 31));
	gash.add_item("G", item("Jonathan", "coffee", 28));
	gash.add_item("H", item("Matt", "juice", 90));
	gash.add_item("I", item("Mattt", "juice", 31));
	gash.add_item("J", item("Jonathan", "coffee", 28));
	gash.add_item("K", item("Matt", "juice", 90));
	gash.add_item("L", item("Mattt", "juice", 31));
	gash.add_item(item("Jonathan", "coffee", 28));
	gash.add_item("N", item("Matt", "juice", 90));
	gash.add_item("O", item("Mattt", "juice", 31));
	gash.add_item("O", item("Mattt", "juice", 31));
	gash.add_item("O", item("Mattt", "juice", 31));
	gash.add_item("O", item("Mattt", "juice", 31));
	gash.add_item("O", item("Mattt", "juice", 31));
	gash.add_item("O", item("Mattt", "juice", 31));
	gash.add_item("O", item("Mattt", "juice", 31));

	//gash.print_table(std::cout);
	gash.print_table_stats(std::cout);


}

int main()
{

	//event_proxy_collection_example();
	//event_example();
	//points_example();

	//int log_2_size = 6;
	//int ntests = 100;
	//auto av = run_test(log_2_size, ntests);
	//std::cout << "log2_size = " << log_2_size << std::endl;
	//std::cout << "Col/row = " << av << std::endl;
	/*
	complex_number<double> c1(1, 1);
	complex_number<double> c2(2, 3);
	auto c3 = c1 + c2;
	auto c4 = c1 * c2;
	auto c5 = c2 - c1;
	auto c6 = c1 / c2;
	c5.print();
	c6.print();
	//c1.print();
	//c3.print();
	//c4.print();
	std::cout << c1.len() << std::endl;
	std::cout << c1 << std::endl;
	if (c1 == c2)std::cout << "yes" << std::endl;
	else std::cout << "no" << std::endl;
	*/

	hash_tester();

    return 0;
}

