#include "Node.h"

Node::Node(){
}

Node::Node(Vector3<float> position){
	m_position = position;

}

Node::~Node(){
	//m_children.~list();

	//TODO: Delete also the objects that the pointers on the list point...
}

void Node::Render(){

	for (m_iterator = m_children.begin(); m_iterator != m_children.end(); m_iterator++ )
	{
		Node& node = **m_iterator;

		node.Render();
	}
}
/*
void Node::AddNode(Node* parent, Node* node){

	//this->m_children.insert(m_children.end(), node);
	parent->AddNode(node);

}
*/

bool Node::IsWithin(Vector3<float> position){
	return false;
}





