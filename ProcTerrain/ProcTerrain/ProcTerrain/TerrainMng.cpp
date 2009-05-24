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
	
	//Shader
	SetUpShaders();	

	m_gui = new GUI();

	

}

void TerrainMng::SetUpShaders(){
	char *vs = NULL,*fs = NULL;
	GLhandleARB vertexShader, fragmentShader;
	
	vertexShader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	fragmentShader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);	

	vs = textFileRead("../../ProcTerrain/Shaders/generate.vert");
	fs = textFileRead("../../ProcTerrain/Shaders/generate.frag");

	if(vs != NULL && fs != NULL){
		const char * vv = vs;
		const char * ff = fs;

		glShaderSourceARB(vertexShader, 1, &vv,NULL);
		glShaderSourceARB(fragmentShader, 1, &ff,NULL);

		free(vs);free(fs);

		glCompileShaderARB(vertexShader);
		glCompileShaderARB(fragmentShader);

		printInfoLog(vertexShader);
		printInfoLog(fragmentShader);

		m_shaderGenerate = glCreateProgramObjectARB();
		
		glAttachObjectARB(m_shaderGenerate,vertexShader);
		glAttachObjectARB(m_shaderGenerate,fragmentShader);

		glLinkProgramARB(m_shaderGenerate);
		printInfoLog(m_shaderGenerate);

		glUseProgramObjectARB(m_shaderGenerate);

	}

	



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
	m_currentNode->Render();
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