#ifndef EXAM_ASSIGNMENTS_SEARCHABLE_BAG_HPP
#define EXAM_ASSIGNMENTS_SEARCHABLE_BAG_HPP
#include "bag.hpp"

class searchable_bag : virtual public bag {
public:
	virtual bool has(int) const = 0;
};

#endif