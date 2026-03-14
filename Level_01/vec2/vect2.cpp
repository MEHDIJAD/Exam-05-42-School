#include "vect2.hpp"

// 1. OF
vect2::vect2() : x(0), y(0) {}

vect2::vect2(int x, int y) : x(x), y(y) {}

vect2::vect2(const vect2& other) : x(other.x), y(other.y) {}

vect2 &vect2::operator=(const vect2& other) {
	if (this != &other) {
		this->x = other.x;
		this->y = other.y;
	}
	return *this;
}

// ADD
vect2 vect2::operator+(const vect2& other) const {
	vect2 result;

	result.x = this->x + other.x;
	result.y = this->y + other.y;
	
	return result;
}

vect2 &vect2::operator++() {
	*this = *this + vect2(1,1);
	return *this;
}

vect2 vect2::operator++(int) {
	vect2 copy = *this;
	++(*this);
	return copy;
}

vect2 &vect2::operator+=(const vect2& other) {
	*this = *this + other;
	return *this;
}

// 3. SUB
vect2 vect2::operator-(const vect2& other) const {
	vect2 result;

	result.x = this->x - other.x;
	result.y = this->y - other.y;
	
	return result;
}

// -obj
vect2 vect2::operator-() const {
	return vect2(-x, -y);
}

vect2 &vect2::operator--() {
	*this = *this - vect2(1,1);
	return *this;
}

vect2 vect2::operator--(int) {
	vect2 copy = *this;
	--(*this);
	return copy;
}

vect2 &vect2::operator-=(const vect2& other) {
	*this = *this - other;
	return *this;
}

// 4. MULT BY SCLALER

// obj * scaler
vect2 vect2::operator*(int scaler) const {
	return vect2(this->x * scaler, this->y * scaler);
}

// obj * obj
vect2 vect2::operator*(const vect2& other) const {
	return vect2(this->x * other.x, this->y * other.y);
}

// obj *= scaler
vect2 &vect2::operator*=(int scaler) {
	*this = *this * vect2(scaler, scaler);
	return *this;
}

// 5. op[]

// Read
const int &vect2::operator[](int index) const {
	return (index == 0) ? x : y; 
}

// Write
int &vect2::operator[](int index) {
	return (index == 0) ? x : y; 
}

// 7. GETTERS
int vect2::getX() const {return this->x;}

int vect2::getY() const {return this->y;}


// == && !=
bool vect2::operator==(const vect2& other) const {
	return (this->x == other.x && this->y == other.y);
}

bool vect2::operator!=(const vect2& other) const {
	return !(*this == other);
}


// 6. op<<
std::ostream &operator<<(std::ostream &os, const vect2& vec) {
	os << "{" << vec.getX() << ", " << vec.getY() << "}";
	return os;
}

vect2 operator*(int scaler, const vect2 &vec) {
	return (vec * scaler); // this calles operator*(int scaler);
}



