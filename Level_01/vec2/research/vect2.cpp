#include "vect2.hpp"

vect2::vect2() : f(0), s(0) {}

vect2::vect2(int f, int s) : f(f), s(s) {}

vect2::vect2(const vect2& other) : f(other.f), s(other.s) {}

vect2 &vect2::operator=(const vect2& other) {
	if (this != &other) {
		this->f = other.f;
		this->s = other.s;
	}
	return *this;
}

int vect2::getFirst() const { return this->f;}

int vect2::getSecond() const{ return this->s;}

vect2::~vect2() {}

std::ostream &operator<<(std::ostream &os, vect2& vect) {
	os << vect.getFirst() << "," << vect.getSecond();
	return os;
}

// Non-const: allows v1[0] = 5
int& vect2::operator[](int indx) {
	return (indx == 0) ? f : s;
}

// Const: allows reading from const objects
int vect2::operator[](int indx) const {
	return (indx == 0) ? f : s;
}
// add

vect2 vect2::operator+(const vect2 &other) const {
	vect2 res;

	res.f = this->f + other.f;
	res.s = this->s + other.s;

	return res;
}

vect2 &vect2::operator+=(const vect2& other) {
	this->f += other.f;
	this->s += other.s;
	return *this;
}

// ++v
vect2 &vect2::operator++() {

	*this = *this + vect2(1,1);
	return *this;
}

// v++
vect2 vect2::operator++(int) { // dummy parameter to differentiate
	vect2 cpy = *this;
	this->operator++();
	return cpy;
}


// sub

vect2 vect2::operator-(const vect2& other)  const {
	vect2 res;

	res.f = this->f - other.f;
	res.s = this->s - other.s;

	return res;
}

vect2 &vect2::operator-=(const vect2& other) {
	this->f -= other.f;
	this->s -= other.s;
	return *this;
}

// --v
vect2 &vect2::operator--() {

	*this = *this - vect2(1,1);
	return *this;
}

// v--
vect2 vect2::operator--(int) { // dummy parameter to differentiate
	vect2 cpy = *this;
	this->operator--();
	return cpy;
}


bool vect2::operator==(const vect2 &other)  const {
	return (f == other.f && s == other.s);
}

bool vect2::operator!=(const vect2 &other) const {
	return (f != other.f || s != other.s);
}

vect2 vect2::operator*(int scalar) const {
	return vect2(this->f * scalar, this->s * scalar);
}

vect2 &vect2::operator*=(int scalar){
	this->f = this->f * scalar;
	this->s = this->s * scalar;
	return *this;
}

vect2 vect2::operator*(const vect2& other) {
	vect2 res;
	res.f = f * other.f;
	res.s = s * other.s;

	return res;
}

vect2 &vect2::operator*=(const vect2& other) {
	*this = *this * other;
	return *this;
}

vect2 operator*(int scalar, const vect2& v) {
	return vect2(v.getFirst() * scalar, v.getSecond() * scalar);
}

vect2 vect2::operator-() const {
    return vect2(-this->f, -this->s);
}







