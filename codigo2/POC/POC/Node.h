#ifndef NODE_H
#define NODE_H


#include <list>
using namespace::std;
#include "Vector3.h"



class Node{
public:
	list<Node*> m_children;
	list<Node*>::iterator m_iterator;

	Vector3<float> m_position;
	
public:
	Node();
	virtual void Render();
	virtual void AddNode(Node*);

};

#endif