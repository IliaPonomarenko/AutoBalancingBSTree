#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"

class BSTree
{
public:
	BSTree();

	~BSTree();

	bool isEmpty() const;

	unsigned size() const;
	
	int height() const;

	void insertKey(const int _key);

	Node * findKey(const int _key) const;

	//void BSTreeRemoveKey(const BSTree const & _tree, const int _m_key);

private:
	Node * m_pRoot;

	Node * BSTreeCreateNode(const int _key, Node * _node);

	void leftRotation(Node * _node);

	void rightRotation(Node * _node);

	void leftThenRightRotation(Node * _node);

	void rightThenLeftRotation(Node * _node);

	void balanceTree(Node * _node);

	// Helpers

	void recursiveDestroy(Node *_node);

	void recursiveSizeCalculation(Node const *, unsigned&) const;

	int recursiveHeightCalculation(Node const *) const;

	void recursiveInsertion(Node *, const int _key);
};

#endif