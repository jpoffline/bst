// dataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "../lib/linked_list.h"
#include "../lib/binary_search_tree.h"
#include "../lib/data_structure_types.h"

EVENT_PROXY_COLLECTION<int, int, int>
gen_event_pc(int N) {
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

int main()
{

	event_proxy_collection_example();
	event_example();
	points_example();
    return 0;
}

