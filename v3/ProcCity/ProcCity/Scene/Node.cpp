#include "Node.h"


Node::Node(){


}

void Node::AddNode(Node* node){

	this->m_children.insert(m_children.end(), node);



}

void Node::Update(){


}

void Node::Render(){

	for (m_iterator = m_children.begin(); m_iterator != m_children.end(); m_iterator++ )
	{

		Node& node = **m_iterator;

		node.Render();
		
	}
}
