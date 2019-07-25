#include "pch.h"
#include "../BSTree/BSTree.cpp"

// BSTREE TEST SOURCE

TEST(Operations, BasicEmpty) 
{
	BSTree tree;
	bool result = tree.isEmpty();

	ASSERT_EQ(tree.isEmpty(), true);
}

TEST(Operations, BasicSize)
{
	BSTree tree;

	tree.insertKey(20);
	tree.insertKey(2);
	tree.insertKey(4);
	tree.insertKey(7);

	ASSERT_EQ(tree.size(), 4);
}

TEST(Operations, BasicHeight)
{
	BSTree tree;

	tree.insertKey(20);
	tree.insertKey(2);
	tree.insertKey(4);
	tree.insertKey(7);

	ASSERT_EQ(tree.height(), 3);
}

TEST(Operations, Search)
{
	BSTree tree;

	tree.insertKey(20);

	ASSERT_TRUE(tree.findKey(20));
}

TEST(Modification, Insert)
{
	BSTree tree;

	tree.insertKey(20);

	ASSERT_FALSE(tree.isEmpty());
}

TEST(Modification, Remove)
{
	BSTree tree;

	tree.insertKey(20);
	tree.removeKey(20);

	ASSERT_TRUE(tree.isEmpty());
}
