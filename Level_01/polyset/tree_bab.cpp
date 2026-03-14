#include "tree_bag.hpp"
#include <iostream>

/*! @brief the tree is empty at first
*/
tree_bag::tree_bag() : tree(0) {}

tree_bag::tree_bag(const tree_bag &other)
{
	this->tree = copy_node(other.tree);
}

tree_bag &tree_bag::operator=(const tree_bag &other) {
	this->clear();

	this->tree = copy_node(other.tree);
	
	return *this;
}

tree_bag::~tree_bag() {
	this->destroy_tree(this->tree);
}

/*! @brief Set @param ret pointer and return it and set tree to NULL */
tree_bag::node *tree_bag::extract_tree() {
	node *ret = this->tree;
	this->tree = 0;
	return ret;
}

/*! @brief destroy the tree and SET it to tree pointer @param t
	
*/
void tree_bag::set_tree(node *t) {
	destroy_tree(this->tree);
	this->tree = t;
}

void tree_bag::insert(int val) {
	/*! @brief double pointer holding @param tree address */
	node **n = &this->tree;

	while (*n) // while (we have a tree)
	{
		if (val < (*n)->value) /*! if ( @param val to insert < value of node we are att)*/
			n = &(*n)->l; /*! @param n = the address of Left node we are at */
		else if (val >= (*n)->value) // else we give it ot right adress of where we at
			n = &(*n)->r;
	}
	*n = new node((node){0, 0, val}); // creat a new nod at the possion we get left or right 🤔
}

void tree_bag::insert(int *array, int size) {
	for (int i = 0; i < size; i++)
		this->insert(array[i]);
}

void tree_bag::print() const {
	this->print_node(this->tree);
	std::cout << std::endl;
}

void tree_bag::destroy_tree(node *n) {
	if (!n)
		return;
	destroy_tree(n->l);
	destroy_tree(n->r);
	delete(n);
}

void tree_bag::print_node(node *n) {
	if (!n)
		return;
	print_node(n->l);
	std::cout << n->value << " ";
	print_node(n->r);
}

tree_bag::node *tree_bag::copy_node(node *n) {
	if (!n)
		return 0;
	return new node((node){copy_node(n->l), copy_node(n->r), n->value});
	/*! @brief Recursion*/
}

void tree_bag::clear() {
	this->destroy_tree(this->tree);
	this->tree = NULL;
}
