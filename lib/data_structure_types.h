#pragma once

#include <iostream>
#include <vector>

class POINTS {
	private:
		std::vector<double> _points;
	public:
		double get_point(int idx);
		void add(double p);
		double vec_size();
		size_t n_points();
		bool operator <(POINTS& other);
		bool operator >(POINTS& other);
		bool operator ==(POINTS& other);
		friend std::ostream &operator <<(std::ostream& out,  POINTS& p);
};

template <typename E, typename P, typename H>
class EVENT {
	private:
		E _eventid;
		P _proxyid;
		H _hazbin;
	public:
		EVENT() {};
		void set_eventid(E e) {
			_eventid = e;
		}
		void set_proxyid(P p) {
			_proxyid = p;
		}
		void set_hazbin(H h) {
			_hazbin = h;
		}
		E get_eventid() {
			return _eventid;
		}
		P get_proxyid() {
			return _proxyid;
		}
		H get_hazbin() {
			return _hazbin;
		}
		bool operator <(EVENT& other) {
			if (_eventid < other.get_eventid()) return true;
			return false;

		}
		bool operator >(EVENT& other) {
			if (_eventid > other.get_eventid()) return true;
			return false;
		}
		bool operator ==(EVENT& other) {
			if (_eventid == other.get_eventid()) return true;
			return false;
		}
		friend std::ostream &operator <<(std::ostream& out, EVENT& p) {
			out 
				<< "EventID: " << p.get_eventid() << "\n" 
				<< "ProxyID: " << p.get_proxyid() << "\n" 
				<< "Haz bin: " << p.get_hazbin();
			return out;
		}

};



template <typename E, typename P, typename H>
class EVENT_PROXY_COLLECTION {
	private:

		struct pair {
			P _proxyid;
			H _hazbin;
			pair(P p, H h) {_proxyid = p; _hazbin = h; }
		};

		E _eventid;

		std::vector<pair> _locs;

	public:

		EVENT_PROXY_COLLECTION() {};

		void add_pair(P p, H h) {
			_locs.push_back(pair(p, h));
		}

		E get_eventid() { return _eventid; }

		void set_eventid(E e) { _eventid = e; }

		bool operator <(EVENT_PROXY_COLLECTION& other) {
			if (_eventid < other.get_eventid()) return true;
			return false;
		}

		bool operator >(EVENT_PROXY_COLLECTION& other) {
			if (_eventid > other.get_eventid()) return true;
			return false;
		}

		bool operator ==(EVENT_PROXY_COLLECTION& other) {
			if (_eventid == other.get_eventid()) return true;
			return false;
		}

		size_t get_nlocs() {
			return _locs.size();
		}

		P get_ith_proxy(int i) {
			return _locs[i]._proxyid;
		}

		H get_ith_hazbin(int i) {
			return _locs[i]._hazbin;
		}

		friend std::ostream &operator <<(std::ostream& out, EVENT_PROXY_COLLECTION& p) {
			out
				<< "EventID: " << p.get_eventid() << "\n";
			for (int i = 0; i < p.get_nlocs(); i++) {
				out << "(ProxyID, hazBin): (" 
					<< p.get_ith_proxy(i) << ", " << p.get_ith_hazbin(i) 
					<< ")\n";
			}
			return out;
		}

};