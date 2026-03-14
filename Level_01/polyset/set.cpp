#include "set.hpp"

set::set() : sb(0) {}

set::set(searchable_bag &sb) : sb(&sb) {}

set::set(const set &other) : sb(other.sb) {}

set &set::operator=(const set &other) {
	if (this != &other){
		this->sb = other.sb;
	}
	return *this;
}

set::~set() {
    // A wrapper/view should not delete or clear the wrapped object.
    // The life of the bag is managed by whoever created it (in this case main).
}

void set::insert(int val) {
	if (this->sb && !this->sb->has(val))
		this->sb->insert(val);
}

void set::insert(int *array, int size) {
	if (!this->sb || !array || size <= 0)
		return;
	for (int i = 0; i < size; i++) {
		this->insert(array[i]);
	}
}

void set::print() const {
	if (this->sb)
		this->sb->print();
}

void set::clear() {
	if (this->sb)
		this->sb->clear();
}

bool set::has(int val) const {
	return (this->sb && this->sb->has(val));
}

searchable_bag &set::get_bag() {
	return *(this->sb);
}
