#include "BSTree.h"
#include <iostream>

int main()
{
	BSTree tree;

	bool empt = tree.isEmpty();

	tree.insertKey(20);

	tree.insertKey(2);

	tree.insertKey(4);

	tree.insertKey(7);

	tree.insertKey(5);

	tree.insertKey(12);

	tree.insertKey(9);

	std::cout << tree.size();

	std::cout << tree.height();

	bool empt2 = tree.isEmpty();
	//Node node = tree.findKey(20);

}