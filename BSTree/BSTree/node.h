#ifndef _NODE_H
#define _NODE_H

struct Node
{
	int m_key;

	Node *m_pParent;
	Node *m_pRight;
	Node *m_pLeft;
};

#endif