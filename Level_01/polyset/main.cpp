#include "searchable_tree_bag.hpp"
#include "searchable_array_bag.hpp"
#include "set.hpp"
#include "color.hpp"
#include <cstdlib>
#include <iostream>

int main(int ac, char **av)
{
	if (ac == 1) {
		std::cout << RED << "Usage: ./polyset [numbers...]" << RESET << std::endl;
		return 1;
	}

	std::cout << BLUE << "=== Tree vs Array Bag ===" << RESET << std::endl;
	searchable_bag *t = new searchable_tree_bag;
	searchable_bag *a = new searchable_array_bag;
	for (int i = 1; i < ac; i++)
	{
		t->insert(atoi(av[i]));
		a->insert(atoi(av[i]));
	}
	std::cout << YELLOW << "Tree Output: " << RESET; t->print();
	std::cout << YELLOW << "Array Output: " << RESET; a->print();

	std::cout << "\n" << BLUE << "=== Search Tests ===" << RESET << std::endl;
	for (int i = 1; i < ac; i++)
	{
		int val = atoi(av[i]);
		std::cout << "Searching " << val << ": " << (t->has(val) ? GREEN : RED) << "Found in T" << RESET << " | " << (a->has(val) ? GREEN : RED) << "Found in A" << RESET << std::endl;
	}

	std::cout << "\n" << BLUE << "=== Set Wrapper Tests ===" << RESET << std::endl;
	set sa(*a);
	for (int i = 1; i < ac; i++)
		sa.insert(atoi(av[i]));
	std::cout << YELLOW << "Set Result (No Duplicates): " << RESET; sa.print();
	std::cout << GRAY << "Note: Set uses the wrapped array_bag." << RESET << std::endl;

	delete t;
	delete a;
	return 0;
}
