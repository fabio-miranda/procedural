#include "Node.h"


Node::Node(Vector3<float> position){
	m_position = position;

}

void Node::Render(){

	for (m_iterator = m_children.begin(); m_iterator != m_children.end(); m_iterator++ )
	{
		Node& node = **m_iterator;

		node.Render();
	}
}

void Node::AddNode(Node* node){

	this->m_children.insert(m_children.end(), node);

}

bool Node::IsWithin(Vector3<float> position){
	return false;
}

Node* Node::FindCurrentNode(Vector3<float> position){
	

	


}


