#ifndef NODE_H
#define NODE_H


#include <vector>
#include "Vector3.h"
#include "glsl.h"
using namespace::std;



class Node{
public:
	vector<Node*> m_children;
	vector<Node*>::iterator m_iterator;

	Vector3<float> m_position;
	Vector3<float> m_color;
	int clicksFromCenterNode;
	
public:
	Node();
	virtual void Render(bool,int);
	virtual bool IsWithin(Vector3<float>);
	virtual void GenerateNeighbours(Node*);
	virtual Node* FindCurrentStandingNode(Vector3<float>);

};

#endif