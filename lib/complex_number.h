#pragma once
#include <iostream>
template <typename T>
class complex_number {
	private:
		T _real;
		T _imag;
	public:
		T get_real() { return _real; }
		T get_imag() { return _imag; }
		void set_real(T r) { _real = r; }
		void set_imag(T i) { _imag = i; }
		complex_number() {};
		complex_number(T r, T i) { _real = r; _imag = i; };
		~complex_number() {};
		void print(std::ostream& out) {
			out << "(" << get_real() << ", " << get_imag() << ")" << "\n";
		}
		void print() { print(std::cout); }
		T lensq() { return get_real() * get_real() + get_imag() * get_imag(); }
		T len() { return sqrt(lensq()); }
		void conjme() {set_imag(-get_imag());}
		complex_number<T> conj() { return complex_number<T>(get_real(), -get_imag()); }
		complex_number<T> operator+(complex_number<T> &c1) {
			return complex_number<T>(c1.get_real() + this->get_real(), c1.get_imag() + this->get_imag());
		}
		bool operator==(complex_number<T> &c1) {
			return (this->get_real() == c1.get_real()) && (this->get_imag() == c1.get_imag());
		}
		complex_number<T> operator-(complex_number<T> &c1) {
			return complex_number<T>(this->get_real() - c1.get_real() , this->get_imag() - c1.get_imag());
		}
		complex_number<T> operator*(complex_number<T> &c1) {
			return complex_number(c1.get_real() * this->get_real() - c1.get_imag() * this->get_imag(), c1.get_real() * this->get_imag() + this->get_real() * c1.get_imag());
		}
		complex_number<T> operator/(complex_number<T> &c1) {
			auto len_denom = c1.lensq();
			auto mult = complex_number<T>(this->get_real(), this->get_imag()) * c1.conj();
			return complex_number(mult.get_real() / len_denom, mult.get_imag() / len_denom);
		}
		friend std::ostream &operator <<(std::ostream& out, complex_number<T>& p) {
			out
				<< "(" << p.get_real() << ", " << p.get_imag() << ")";
			return out;
		}



};







