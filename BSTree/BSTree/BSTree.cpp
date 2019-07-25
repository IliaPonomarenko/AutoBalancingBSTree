#include "BSTree.h"
#include "algorithm"
#include <cmath>


BSTree::BSTree()
{
	m_pRoot = nullptr;
}

void BSTree::recursiveDestroy(Node * _node)
{
	if (!_node)
		return;

	recursiveDestroy(_node->m_pLeft);
	recursiveDestroy(_node->m_pRight);

	delete _node;
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

int BSTree::recursiveHeightCalculation(Node const * _node) const
{
	unsigned m_pLeftside;
	unsigned m_pRightside;

	if (!_node)
		return 0;

	(_node->m_pLeft == 0) ? m_pLeftside = 0 
		: m_pLeftside = recursiveHeightCalculation(_node->m_pLeft);

	(_node->m_pRight == 0) ? m_pRightside = 0 
		: m_pRightside = recursiveHeightCalculation(_node->m_pRight);

	return 1 + std::max(m_pLeftside, m_pRightside);
}

void BSTree::recursiveInsert(Node * _node, const int _key)
{
	if (!m_pRoot)
	{
		m_pRoot = BSTreeCreateNode(_key);
		return;
	}
	
	if (_key == _node->m_key)
		return;

	if (_key < _node->m_key)
		if (_node->m_pLeft)
		{
			recursiveInsert(_node->m_pLeft, _key);
			
			unsigned leftHeight = recursiveHeightCalculation(_node->m_pLeft);
			unsigned rightHeight = recursiveHeightCalculation(_node->m_pRight);

			if (leftHeight - 2 == rightHeight)
				(_key < _node->m_pLeft->m_key) ? rightRotation(_node) : leftThenRightRotation(_node);
		}
		else
			_node->m_pLeft = BSTreeCreateNode(_key, _node);
	else
		if (_node->m_pRight)
		{
			recursiveInsert(_node->m_pRight, _key);

			unsigned leftHeight = recursiveHeightCalculation(_node->m_pLeft);
			unsigned rightHeight = recursiveHeightCalculation(_node->m_pRight);

			if (rightHeight - 2 == leftHeight)
				(_key < _node->m_pRight->m_key) ? rightThenLeftRotation(_node) : leftRotation(_node);
		}
		else
			_node->m_pRight = BSTreeCreateNode(_key, _node);

}

Node *BSTree::BSTreeCreateNode(const int _key, Node * _parent)
{
	Node * pNewNode = new Node;

	pNewNode->m_key = _key;

	pNewNode->m_pLeft = pNewNode->m_pRight = nullptr;
	pNewNode->m_pParent = _parent;

	return pNewNode;
}

void BSTree::recursiveRemove(Node * _node, const int _key)
{
	if (m_pRoot->m_key == _key)
		removeNode(m_pRoot);

	if (!findKey(_key))
		return;

	if (_key < _node->m_key)
	{
		if (_node->m_pLeft->m_key == _key)
			removeNode(_node->m_pLeft);
		else 
			recursiveRemove(_node->m_pLeft, _key);

		unsigned leftHeight = recursiveHeightCalculation(_node->m_pLeft);
		unsigned rightHeight = recursiveHeightCalculation(_node->m_pRight);

		if (leftHeight + 2 == rightHeight)
			(_key < _node->m_pRight->m_key) ? rightThenLeftRotation(_node) : leftRotation(_node);
	}
	else {
		if (_node->m_pRight->m_key == _key)
			removeNode(_node->m_pRight);
		else
			recursiveRemove(_node->m_pRight, _key);

		unsigned leftHeight = recursiveHeightCalculation(_node->m_pLeft);
		unsigned rightHeight = recursiveHeightCalculation(_node->m_pRight);

		if (rightHeight + 2 == leftHeight)
			(_key < _node->m_pLeft->m_key) ? leftThenRightRotation(_node) : rightRotation(_node);
	}
}

void BSTree::removeNode(Node * _node)
{
	if (!_node->m_pLeft && !_node->m_pRight)
	{
		if (_node != m_pRoot)
			(isLeftChild(_node)) ? _node->m_pParent->m_pLeft = nullptr
				: _node->m_pParent->m_pRight = nullptr;
		else
			m_pRoot = nullptr;
		delete _node;

		return;
	}

	if (!_node->m_pLeft)
	{
		_node->m_key = _node->m_pRight->m_key;

		delete _node->m_pRight;
		_node->m_pRight = nullptr;

		return;
	}

	if (!_node->m_pRight)
	{
		_node->m_key = _node->m_pLeft->m_key;

		delete _node->m_pLeft;
		_node->m_pLeft = nullptr;

		return;
	}

	Node * nodeForChange = findMinKey(_node->m_pRight);
	
	_node->m_key = nodeForChange->m_key;

	if (nodeForChange->m_pRight)
	{
		nodeForChange->m_key = nodeForChange->m_pRight->m_key;

		delete nodeForChange->m_pRight;
		nodeForChange->m_pRight = nullptr;
	}
	else {
		delete nodeForChange;
		nodeForChange = nullptr;
	}
}

Node * BSTree::findKey(const int _key) const
{
	Node * pCurrent = m_pRoot;

	while (pCurrent)
	{
		if (pCurrent->m_key == _key)
			return pCurrent;

		if (pCurrent->m_key > _key)
			(pCurrent->m_pLeft) ? pCurrent = pCurrent->m_pLeft : pCurrent = 0;

		else
			(pCurrent->m_pRight) ? pCurrent = pCurrent->m_pRight : pCurrent = 0;
	}

	return nullptr;
}

Node * BSTree::findMinKey(Node * _node) const
{
	Node* current = _node;

	while (current->m_pLeft)
		current = current->m_pLeft;

	return current;
}

void BSTree::leftRotation(Node * _node)
{
	Node * pTemp = _node->m_pRight;

	_node->m_pRight = pTemp->m_pLeft;
	if (pTemp->m_pLeft)
		pTemp->m_pLeft->m_pParent = _node;

	pTemp->m_pParent = _node->m_pParent;
	pTemp->m_pLeft = _node;
	
	if (_node != m_pRoot)
		(isLeftChild(_node)) ? _node->m_pParent->m_pLeft = pTemp 
			: _node->m_pParent->m_pRight = pTemp;
	else
		m_pRoot = pTemp;

	pTemp->m_pLeft->m_pParent = pTemp;

	_node = pTemp;
}

void BSTree::rightRotation(Node * _node)
{
	Node * pTemp = _node->m_pLeft;

	_node->m_pLeft = pTemp->m_pRight;
	if (pTemp->m_pRight)
		pTemp->m_pRight->m_pParent = _node;

	pTemp->m_pParent = _node->m_pParent;
	pTemp->m_pRight = _node;

	if (_node != m_pRoot)
		(isLeftChild(_node)) ? _node->m_pParent->m_pLeft = pTemp
			: _node->m_pParent->m_pRight = pTemp;
	else
		m_pRoot = pTemp;

	pTemp->m_pRight->m_pParent = pTemp;

	_node = pTemp;
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