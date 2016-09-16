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
			out << p.get_eventid() << " " << p.get_proxyid() << " " << p.get_hazbin();
			return out;
		}

};