#include "vect2.hpp"
#include "color.hpp"
#include <iostream>

int main()
{
	std::cout << BLUE << "=== Initializations ===" << RESET << std::endl;
	vect2 v1;           // x=0, y=0
	vect2 v2(1,2);      // x=1, y=2
	const vect2 v3(v2); // Copy of v2
	vect2 v4 = v2;      // Assignment

	std::cout << "v1: " << YELLOW << v1 << RESET << " [Default: {0, 0}]" << std::endl;
	std::cout << "v2: " << YELLOW << v2 << RESET << " [Params: {1, 2}]" << std::endl;
	std::cout << "v3: " << YELLOW << v3 << RESET << " [Copy: {1, 2}]" << std::endl;
	std::cout << "v4: " << YELLOW << v4 << RESET << " [Assign: {1, 2}]" << std::endl;
	
	std::cout << "\n" << BLUE << "=== Increments ===" << RESET << std::endl;
	std::cout << "v4++: " << GREEN << v4++ << RESET << " [Returns old {1, 2}, v4 becomes {2, 3}]" << std::endl;
	std::cout << "++v4: " << GREEN << ++v4 << RESET << " [v4 becomes {3, 4}, returns {3, 4}]" << std::endl;

	std::cout << "\n" << BLUE << "=== Arithmetic ===" << RESET << std::endl;
	v2+=v3;
	std::cout << "v2 += v3: " << GREEN << v2 << RESET << " [{1, 2} + {1, 2} = {2, 4}]" << std::endl;
    
	v1-=v2;
	std::cout << "v1 -= v2: " << GREEN << v1 << RESET << " [{0, 0} - {2, 4} = {-2, -4}]" << std::endl;
    
	v2 = 3 * (v3 + v3 * 2);
	std::cout << "3 * (v3 + v3 * 2): " << GREEN << v2 << RESET << " [3 * ({1, 2} + {2, 4}) = {9, 18}]" << std::endl;
    
	std::cout << "\n" << BLUE << "=== Comparisons ===" << RESET << std::endl;
	std::cout << "v1 == v3: " << (v1 == v3 ? GREEN : RED) << (v1 == v3) << RESET << " [Check equality]" << std::endl;
	std::cout << "v1 != v3: " << (v1 != v3 ? GREEN : RED) << (v1 != v3) << RESET << " [Check inequality]" << std::endl;

	return 0;
}
