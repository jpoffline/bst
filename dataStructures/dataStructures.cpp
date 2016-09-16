// dataStructures.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include "../lib/linked_list.h"
#include "../lib/binary_search_tree.h"
#include "../lib/data_structure_types.h"


int main()
{
	
	/// Define an event: the eventid, proxyid, and hazbin types are all ints.
	EVENT<int, int, int> my_event, my_event2;
	my_event.set_eventid(1001);
	my_event.set_hazbin(21);
	my_event.set_proxyid(891);
	my_event2.set_eventid(100);
	my_event2.set_hazbin(21);
	my_event2.set_proxyid(891);

	/// boot up a bst for the event.
	/// the key type is int (and will be the eventid),
	/// and the data attached to each node is the event.
	binary_search_tree<int, EVENT<int, int, int>> myTreeEvent;
	myTreeEvent.add_leaf(my_event.get_eventid(), my_event);
	myTreeEvent.add_leaf(my_event2.get_eventid(), my_event2);
	myTreeEvent.print_in_order();


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
	/*
	linked_list<int> myList;

	myList.add_node(12);
	myList.add_node(31);
	myList.add_node(1);
	myList.add_node(678);
	myList.print(std::cout);
	myList.delete_node(12);
	myList.print(std::cout);
	*/
	
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
	
    return 0;
}

