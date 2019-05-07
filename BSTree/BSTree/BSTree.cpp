#include "BSTree.h"
#include "algorithm"
#include <cmath>


BSTree::BSTree()
{
	m_pRoot = nullptr;
}

BSTree::~BSTree()
{
	recursiveDestroy(m_pRoot);
}

void BSTree::recursiveDestroy(Node * _node)
{
	if (!_node)
		return;

	recursiveDestroy(_node->m_pLeft);
	recursiveDestroy(_node->m_pRight);

	delete _node;
}

bool BSTree::isEmpty() const
{
	return m_pRoot == 0;
}

unsigned BSTree::size() const
{
	unsigned size = 0;
	recursiveSizeCalculation(m_pRoot, size);

	return size;
}

void BSTree::recursiveSizeCalculation(Node const * _node, unsigned & _size) const
{
	if (!_node)
		return;

	recursiveSizeCalculation(_node->m_pLeft, _size);
	recursiveSizeCalculation(_node->m_pRight, _size);

	++_size;
}

int BSTree::height() const
{
	return recursiveHeightCalculation(m_pRoot);
}

int BSTree::recursiveHeightCalculation(Node const * node) const
{
	unsigned m_pLeftside;
	unsigned m_pRightside;

	if (!node)
		return 0;

	if (node->m_pLeft == 0)
		m_pLeftside = 0;
	else
		m_pLeftside = recursiveHeightCalculation(node->m_pLeft);

	if (node->m_pRight == 0)
		m_pRightside = 0;
	else
		m_pRightside = recursiveHeightCalculation(node->m_pRight);

	return 1 + std::max(m_pLeftside, m_pRightside);
}

void BSTree::insertKey(const int _key)
{
	recursiveInsertion(m_pRoot, _key);
} 

void BSTree::recursiveInsertion(Node * node, const int _key)
{
	if (!m_pRoot)
	{
		m_pRoot = BSTreeCreateNode(_key, nullptr);
		return;
	}
	
	if (_key == node->m_key)
		return;

	if (_key < node->m_key)
		if (node->m_pLeft)
		{
			recursiveInsertion(node->m_pLeft, _key);

			if (std::abs(recursiveHeightCalculation(node->m_pLeft)
				- recursiveHeightCalculation(node->m_pRight)) == 2)
				if (recursiveHeightCalculation(node->m_pLeft->m_pLeft) >
					recursiveHeightCalculation(node->m_pLeft->m_pRight))
					rightRotation(node);
				else
					leftThenRightRotation(node);
		}

		else
			node->m_pLeft = BSTreeCreateNode(_key, node);

	else
		if (node->m_pRight)
		{
			recursiveInsertion(node->m_pRight, _key);

			if (std::abs(recursiveHeightCalculation(node->m_pLeft)
				- recursiveHeightCalculation(node->m_pRight)) == 2)
				if (recursiveHeightCalculation(node->m_pLeft->m_pLeft) >
					recursiveHeightCalculation(node->m_pLeft->m_pRight))
					rightRotation(node);
				else
					leftThenRightRotation(node);
		}

		else
			node->m_pRight = BSTreeCreateNode(_key, node);

}

Node *BSTree::BSTreeCreateNode(const int _key, Node * node)
{
	Node * pNewNode = new Node;

	pNewNode->m_key = _key;

	pNewNode->m_pLeft = pNewNode->m_pRight = nullptr;
	
	pNewNode->m_pLeft->m_pParent = pNewNode;
	pNewNode->m_pRight->m_pParent = pNewNode;

	pNewNode->m_pParent = node;

	return pNewNode;
}

//void BSTree::insertKeyWithLoop(const int _key)
//{
//	Node * pCurrent = m_pRoot;
//	if (!pCurrent)
//	{
//		m_pRoot = BSTreeCreateNode(_key);
//		return;
//	}
//
//	while (pCurrent)
//	{
//		if (pCurrent->m_key == _key)
//			return;
//
//		else if (pCurrent->m_key > _key)
//			if (pCurrent->m_pLeft)
//				pCurrent = pCurrent->m_pLeft;
//
//			else
//			{
//				Node * pNewNode = BSTreeCreateNode(_key);
//				pNewNode->m_pParent = pCurrent;
//				pCurrent->m_pLeft = pNewNode;
//				return;
//			}
//
//		else
//			if (pCurrent->m_pRight)
//				pCurrent = pCurrent->m_pRight;
//
//			else
//			{
//				Node * pNewNode = BSTreeCreateNode(_key);
//				pNewNode->m_pParent = pCurrent;
//				pCurrent->m_pRight = pNewNode;
//				return;
//			}
//	}
//}

Node * BSTree::findKey(const int _key) const
{
	Node * pCurrent = m_pRoot;
	if (!pCurrent)
	{
		return nullptr;
	}

	while (pCurrent)
	{
		if (pCurrent->m_key == _key)
			return pCurrent;

		else if (pCurrent->m_key > _key)
			if (pCurrent->m_pLeft)
				pCurrent = pCurrent->m_pLeft;

			else
				return nullptr;

		else
			if (pCurrent->m_pRight)
				pCurrent = pCurrent->m_pRight;

			else
				return nullptr;
	}
}

//void BSTree::RemoveKey(Node *node, const int _m_key) 

void BSTree::leftRotation(Node * _node)
{
	Node * pTemp = _node->m_pRight;

	_node->m_pRight = pTemp->m_pLeft;
	_node->m_pRight->m_pParent = _node;

	pTemp->m_pParent = _node->m_pParent;
	if (_node->m_key > _node->m_pParent->m_key)
		_node->m_pParent->m_pRight = pTemp;
	else
		_node->m_pParent->m_pLeft = pTemp;

	pTemp->m_pLeft = _node;
	_node->m_pParent = pTemp;
}

void BSTree::rightRotation(Node * _node)
{
	Node * pTemp = _node->m_pLeft;

	_node->m_pLeft = pTemp->m_pRight;
	_node->m_pLeft->m_pParent = _node;

	pTemp->m_pParent = _node->m_pParent;
	if (_node->m_key > _node->m_pParent->m_key)
		_node->m_pParent->m_pRight = pTemp;
	else
		_node->m_pParent->m_pLeft = pTemp;

	pTemp->m_pRight = _node;
	_node->m_pParent = pTemp;
}

void BSTree::leftThenRightRotation(Node * _node)
{
	leftRotation(_node->m_pLeft);
	rightRotation(_node);
}

void BSTree::rightThenLeftRotation(Node * _node)
{
	rightRotation(_node->m_pRight);
	leftRotation(_node);
}

//void BSTree::balanceTree(Node * _node)
//{
//	if
//};