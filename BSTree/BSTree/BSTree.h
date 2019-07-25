#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"

class BSTree
{

public:

	BSTree();

	~BSTree() { recursiveDestroy(m_pRoot); };

	bool isEmpty() const { return m_pRoot == 0; };

	unsigned size() const;
	
	int height() const { return recursiveHeightCalculation(m_pRoot); };

	void insertKey(const int _key) { recursiveInsert(m_pRoot, _key); };

	void removeKey(const int _key) { recursiveRemove(m_pRoot, _key); };

	Node * findKey(const int) const;

private:

	Node * m_pRoot;

	Node * BSTreeCreateNode(const int, Node * = nullptr);

	void removeNode(Node *);

	void leftRotation(Node *);

	void rightRotation(Node *);

	void leftThenRightRotation(Node *);

	void rightThenLeftRotation(Node *);

	Node * findMinKey(Node *) const;

	bool isLeftChild(Node * _node) const { return _node->m_pParent->m_pLeft == _node; };

	// Helpers

	void recursiveDestroy(Node *);

	void recursiveSizeCalculation(Node const *, unsigned&) const;

	int recursiveHeightCalculation(Node const *) const;

	void recursiveInsert(Node *, const int);

	void recursiveRemove(Node *, const int);

};

#endif
