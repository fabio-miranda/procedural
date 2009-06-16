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
	//m_fbo = new FBO();

	//Permutation noise
	initPermTexture(&m_permTextureID);



	//Shaders
	//SetUpShaders();
	FBO* m_fbo = new FBO(50, 50);
	m_terrainGenerationShader = new GenerationShader(5132, m_permTextureID);
	m_terrainRenderingShader = new RenderingShader();

	SquareNode* node = new SquareNode(m_terrainGenerationShader, m_terrainRenderingShader, m_fbo, Vector3<float>(0,0,0),50.0f, 128, conf_numDivisions);
	node->GenerateNeighbours(NULL, conf_numNeighbours, -1);
	SetCurrentNode(node);
	

}



void TerrainMng::Update(Vector3<float> currentPosition){
	
	//See if the camera is on another node. If so, we have to generate its neighbours
	
	//TODO: mix IsWithin with GetNewStandingNode
	//TODO: remove conf_numNeighbours
	if(conf_numNeighbours > 0 && m_currentNode->IsWithin(currentPosition) == false){


		SquareNode* oldNode = m_currentNode;
		m_currentNode = m_currentNode->GetNewStandingNode(currentPosition);
		SetCurrentNode(m_currentNode);
		m_currentNode->GenerateNeighbours(oldNode, conf_numNeighbours, -1);
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

//(http://www.sci.utah.edu/~leenak/IndStudy_reportfall/MarbleCode.txt)
void TerrainMng::initPermTexture(GLuint *texID)
{
  char *pixels;
  int i,j;
  
  glGenTextures(1, texID); // Generate a unique texture ID
  glBindTexture(GL_TEXTURE_2D, *texID); // Bind the texture to texture unit 0

  pixels = (char*)malloc( 256*256*4 );

  int perm[256]= {151,160,137,91,90,15,
				  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
				  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
				  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
				  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
				  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
				  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
				  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
				  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
				  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
				  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
				  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
				  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};
  int grad3[16][3] = {{0,1,1},{0,1,-1},{0,-1,1},{0,-1,-1},
                   {1,0,1},{1,0,-1},{-1,0,1},{-1,0,-1},
                   {1,1,0},{1,-1,0},{-1,1,0},{-1,-1,0},
                   {1,0,-1},{-1,0,-1},{0,-1,1},{0,1,1}};


  for(i = 0; i<256; i++)
    for(j = 0; j<256; j++) {
      int offset = (i*256+j)*4;
      char value = perm[(j+perm[i]) & 0xFF];
      pixels[offset] = grad3[value & 0x0F][0] * 64 + 64;   // Gradient x
      pixels[offset+1] = grad3[value & 0x0F][1] * 64 + 64; // Gradient y
      pixels[offset+2] = grad3[value & 0x0F][2] * 64 + 64; // Gradient z
      pixels[offset+3] = value;                     // Permuted index
    }
  
  
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
}
