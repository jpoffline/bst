#pragma once
#include <string>
#include <iostream>
#include <vector>


///////////////////////////////////////////////////////////////////////////////////////
///
/// Definition of the hash table.
///
template <class BDT, class NDT>
class hashtable {

	///
	/// Template parameters: 
	///		-> bucket data type  (BDT)
	///		-> buckets node data type (NDT)
	///

	private:
		std::vector<BDT> _table;
		int _size;
		int _get_hash_value(std::string key);
		void _init();
		std::string _get_bars(int n, std::string bar = "|");
		std::string _get_padding(int n);
		int _ndigits(int n);
	public:
		hashtable(int n) { _size = n; _init(); }
		void add_item(std::string key, NDT item);
		void add_item(NDT item);
		BDT get_item(int idx);
		BDT get_item(std::string key);
		void print_table(std::ostream& out);
		void print_table_stats(std::ostream& out);
};
///
///////////////////////////////////////////////////////////////////////////////////////






///////////////////////////////////////////////////////////////////////////////////////
///
/// Implementation of the hash table.
///
template<class BDT, class NDT>
inline int 
hashtable<BDT, NDT>::_get_hash_value(std::string key) {

	///
	///	Method to obtain the hash value of the inputted 
	/// key variable.
	///

	int hash = 0;
	for (auto& c : key) hash += (int)c;
	return hash % _size;

}


template<class BDT, class NDT>
inline void 
hashtable<BDT, NDT>::_init() {

	///
	///	Method to initialise the hash table elements.
	/// Puts an empty instance of the "Bucket data type" object
	/// into each bucket/index of the table.
	///

	BDT bdt;
	for (int i = 0; i < _size; i++)
		_table.push_back(bdt);

}


template<class BDT, class NDT>
inline std::string 
hashtable<BDT, NDT>::_get_bars(int n, std::string bar) {

	std::string bars = "";

	for (int i = 0; i < n; i++)bars += bar;
	return bars;

}



template<class BDT, class NDT>
inline int 
hashtable<BDT, NDT>::_ndigits(int n) {
	int m = 0;
	while (n > 0) { 
		n = n / 10; m++; 
	}
	return m;
}


template<class BDT, class NDT>
inline void 
hashtable<BDT, NDT>::add_item(std::string key, NDT item) {

	///
	/// Method to add an item to the hash table
	/// @param key 
	///			The (string) key with which to assign which bucket the item should be placed in
	/// @param item 
	///			The node item to be placed in the bucket.
	///

	_table[_get_hash_value(key)].add_node(item);

}

template<class BDT, class NDT>
inline void hashtable<BDT, NDT>::add_item(NDT item) {

	///
	///	Method to add an item to the hash table.
	/// @param item 
	///			The item to be added. It is assumed that the item's datatype NDT has 
	///			a method (string)"hashablekey" to obtain a key
	///			with which to generate a hash key.
	///			
	///

	_table[_get_hash_value(item.hashablekey())].add_node(item);

}


template<class BDT, class NDT>
inline BDT 
hashtable<BDT, NDT>::get_item(int idx) {

	return _table[idx]; 

}


template<class BDT, class NDT>
inline BDT 
hashtable<BDT, NDT>::get_item(std::string key) { 

	return get_item(_get_hash_value(key)); 

}


template<class BDT, class NDT>
inline void 
hashtable<BDT, NDT>::print_table(std::ostream & out) {

	out << "\n";
	out << "The hash table has " << _size << " buckets\n";

	for (int i = 0; i < _size; i++) {
		out << "------------------------------------\n";
		out << "Bucket idx " << i;
		if (_table[i].is_empty()) {
			out << " - is empty\n";
		}
		else {
			out << " - contents...\n";
			out << "# items: " << _table[i].get_n_nodes() << "\n";
			_table[i].print(out, "\n");
		}
		out << "------------------------------------\n";
	}

}


template<class BDT, class NDT>
inline std::string hashtable<BDT, NDT>::_get_padding(int n) {

	std::string padding = "";
	for (int i = 0; i < n; i++) padding += " ";
	return padding;

}


template<class BDT, class NDT>
inline void 
hashtable<BDT, NDT>::print_table_stats(std::ostream & out) {

	out << "\n";
	out << "Hash table stats" << "\n\n";
	out << "Bucket occupancies:\n";
	int totn = _ndigits(_size);
	for (int i = 0; i < _size; i++) {
		auto n = _table[i].get_n_nodes();
		out << "   " << i << " " << _get_padding(totn - _ndigits(i)) << _get_bars(n) << "\n";
	}
	out << "\n";

}

///
///////////////////////////////////////////////////////////////////////////////////////