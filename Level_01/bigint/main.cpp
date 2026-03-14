#include <iostream>
#include "bigint.hpp"
#include "color.hpp"

int main() {
    std::cout << BLUE << "=== Basic Initializations ===" << RESET << std::endl;
    const bigint a(42);
    bigint b(21), c, d(1337), e(d);

    std::cout << "a = " << YELLOW << a << RESET << " [Initialized with 42]" << std::endl;
    std::cout << "b = " << YELLOW << b << RESET << " [Initialized with 21]" << std::endl;
    std::cout << "c = " << YELLOW << c << RESET << " [Default initialized to 0]" << std::endl;
    std::cout << "d = " << YELLOW << d << RESET << " [Initialized with 1337]" << std::endl;
    std::cout << "e = " << YELLOW << e << RESET << " [Copy constructor from d]" << std::endl;

    std::cout << "\n" << BLUE << "=== Arithmetic ===" << RESET << std::endl;
    std::cout << "a + b = " << GREEN << a + b << RESET << " [Addition: 42 + 21]" << std::endl;
    std::cout << "(c += a) = " << GREEN << (c += a) << RESET << " [Addition Assignment: 0 + 42]" << std::endl;

    std::cout << "\n" << BLUE << "=== Increments ===" << RESET << std::endl;
    std::cout << "++b = " << GREEN << ++b << RESET << " [Prefix increment: 21 -> 22]" << std::endl;
    std::cout << "b++ = " << GREEN << b++ << RESET << " [Postfix increment: returns 22, b becomes 23]" << std::endl;
    std::cout << "Current b = " << YELLOW << b << RESET << " [After postfix increment]" << std::endl;

    std::cout << "\n" << BLUE << "=== Digit Shifting ===" << RESET << std::endl;
    std::cout << "(b << 10) + 42 = " << GREEN << ((b << 10) + 42) << RESET << " [Left shift b by 10 then add 42]" << std::endl; 
    std::cout << "(d <<= 4) = " << GREEN << (d <<= 4) << RESET << " [In-place left shift: append 4 zeros]" << std::endl; 
    std::cout << "(d >>= 2) = " << GREEN << (d >>= (const bigint)2) << RESET << " [In-place right shift: remove 2 digits]" << std::endl; 

    std::cout << "\n" << BLUE << "=== Comparisons ===" << RESET << std::endl;
    std::cout << "(d < a) = " << (d < a ? RED : GREEN) << (d < a) << RESET << " [133700 < 42]" << std::endl;
    std::cout << "(d > a) = " << (d > a ? GREEN : RED) << (d > a) << RESET << " [133700 > 42]" << std::endl;
    std::cout << "(d == d) = " << (d == d ? GREEN : RED) << (d == d) << RESET << " [Equality check]" << std::endl;

    std::cout << "\n" << BLUE << "=== Large Numbers ===" << RESET << std::endl;
	bigint x(1844674407370955161);
	bigint y(1844674407370955161);

	bigint z = x + y;
	std::cout << "z = " << YELLOW << z << RESET << " [Sum of two large numbers]" << std::endl;
	std::cout << "z + x + y + z = " << GREEN << z + x + y + z << RESET << " [Chained addition with overflow check]" << std::endl;

    return 0;
}
