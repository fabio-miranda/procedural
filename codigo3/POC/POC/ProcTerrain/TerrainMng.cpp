#include "TerrainMng.h"


TerrainMng::TerrainMng()
{
	//Init glew
	int err=glewInit();
	if(err!=GLEW_OK)
	{
		//exit();
	}

	//m_sceneGraph = new Node(Vector3<float>(0, 0, 0));
	
	

}



void TerrainMng::Update(Vector3<float> currentPosition){
	
	//See if the camera is on another node. If so, we have to generate its neighbours
	//TODO: mix IsWithin with GetNewStandingNode
	if(m_currentNode->IsWithin(currentPosition) == false){
		SquareNode* oldNode = m_currentNode;
		m_currentNode = m_currentNode->GetNewStandingNode(currentPosition);
		m_currentNode->GenerateNeighbours(oldNode);
		SetCurrentNode(m_currentNode);
	}
	

}

void TerrainMng::Render(){

	//m_sceneGraph->Render();
	m_currentNode->Render();

}

/*
void TerrainMng::AddNode(Node* node){
	m_sceneGraph->AddNode(node);

}
*/

void TerrainMng::SetCurrentNode(SquareNode* node){
	m_currentNode = node;
	
}

