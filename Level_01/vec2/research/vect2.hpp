#ifndef VEC2_HPP
#define VEC2_HPP

#include <ostream>
#include <iostream>

class vect2 {
	private:
		int f;
		int s;
	public:
		vect2();
		vect2(int, int );
		vect2(const vect2&);
		vect2 &operator=(const vect2& );
		~vect2();

		// Getter

		int getFirst() const;
		int getSecond() const;

		// addition
		vect2 operator+(const vect2&) const;
		vect2 &operator+=(const vect2&);
		vect2 operator++(int);
		vect2 &operator++();

		// equality
		bool operator==(const vect2 &other) const;
		bool operator!=(const vect2 &other) const ;

		// sub
		vect2 operator-(const vect2&) const;
		vect2 operator-() const;
		vect2 &operator-=(const vect2&);
		vect2 &operator--();
		vect2 operator--(int);

		// mult
		vect2 operator*(int) const;
		vect2 operator*(const vect2&);
		vect2 &operator*=(int);
		vect2 &operator*=(const vect2& other);

		// [op]
		int &operator[](int);
		int operator[](int) const;
};

std::ostream &operator<<(std::ostream&, const vect2&);

vect2 operator*(int , const vect2&);

#endif