#include "stdafx.h"
#include "data_structure_types.h"


double POINTS::get_point(int idx) {
	return _points[idx];
}

void POINTS::add(double p) {

	_points.push_back(p); 

}

double POINTS::vec_size() {

	double s = 0.0;
	for (auto& p : _points) s += p*p;
	return s;// sqrt(s);

}

size_t POINTS::n_points() {

	return _points.size();

}

bool POINTS::operator <(POINTS& other) {

	if (other.n_points() == n_points()) {
		auto s1 = vec_size();
		auto s2 = other.vec_size();
		if (s1 < s2) return true;
		return false;
	}
	else {
		std::cerr << "The vectors are of different dimension: ERROR" << std::endl;
		return false;
	}

}

bool POINTS::operator >(POINTS& other) {

	if (other.n_points() == n_points()) {
		auto s1 = vec_size();
		auto s2 = other.vec_size();
		if (s1 > s2) return true;
		return false;
	}
	else {
		std::cerr << "The vectors are of different dimension: ERROR" << std::endl;
		return false;
	}

}

bool POINTS::operator==(POINTS & other) {
	if (other.n_points() == n_points()) {
		auto s1 = vec_size();
		auto s2 = other.vec_size();
		if (s1 == s2) return true;
		return false;
	}
	else {
		std::cerr << "The vectors are of different dimension: ERROR" << std::endl;
		return false;
	}
}

std::ostream & operator<<(std::ostream & out, POINTS& p) {
	auto s = p.n_points();
	out << "(" << p.get_point(0);
	if (s > 1) {
		for (int i = 1; i < s - 1; i++)
			out << ", " << p.get_point(i);
		out << ", " << p.get_point(s - 1);
	}
	out << ")";
	return out;
}

