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
	
	m_gui = new GUI();

	//Shaders
	//SetUpShaders();
	m_terrainGenerationShader = new Shader("../../ProcTerrain/Shaders/terrainGeneration.vert", "../../ProcTerrain/Shaders/terrainGeneration.frag");
	m_terrainRenderingShader = new Shader("../../ProcTerrain/Shaders/terrainRendering.vert", "../../ProcTerrain/Shaders/terrainRendering.frag");

	SquareNode* node = new SquareNode(m_terrainGenerationShader, m_terrainRenderingShader, Vector3<float>(0,0,0),50.0f, conf_numDivisions);
	node->GenerateNeighbours(NULL, conf_numNeighbours);
	SetCurrentNode(node);


	

	

}



void TerrainMng::Update(Vector3<float> currentPosition){
	
	//See if the camera is on another node. If so, we have to generate its neighbours
	//TODO: mix IsWithin with GetNewStandingNode
	if(m_currentNode->IsWithin(currentPosition) == false){
		SquareNode* oldNode = m_currentNode;
		m_currentNode = m_currentNode->GetNewStandingNode(currentPosition);
		SetCurrentNode(m_currentNode);
		m_currentNode->GenerateNeighbours(oldNode, conf_numNeighbours);
	}
	

}

void TerrainMng::Render(){

	//m_sceneGraph->Render();
	//m_terrainRenderingShader->Enable();
	m_currentNode->Render();
	//m_terrainRenderingShader->Disable();
	m_gui->Render();

}

/*
void TerrainMng::AddNode(Node* node){
	m_sceneGraph->AddNode(node);

}
*/

void TerrainMng::SetCurrentNode(SquareNode* node){
	m_currentNode = node;
	
}