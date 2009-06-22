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
	m_translation = Vector3<float>(0,0,0);
	m_size = 0;
	//m_fbo = new FBO();

	//Permutation noise
	initPermAndGradTextures();



	//Shaders
	//SetUpShaders();
	m_terrainGenerationShader = new GenerationShader(5132, m_permTextureID);
	m_terrainRenderingShader = new RenderingShader();

	


	//Light
	initLight();

	//Nodes
	initNodes();
	

}

void TerrainMng::initNodes(){
	
	//TODO: make sure this allocation is working
	m_size = (2*conf_numNeighbours+1);
	m_ptrNodes = (SquareNode**) malloc(m_size*m_size * sizeof(void *));

	float pos_x = -conf_geomSize*conf_numNeighbours;
	float pos_y = -conf_geomSize*conf_numNeighbours;
	int cont = 0;
	SquareNode* neighbLeft;
	SquareNode* neighbDown;
	int center = (m_size*m_size - 1)/2;
	int center_xy = (m_size - 1)/2;
	int distanceFromCenter = 0;
	short numDivisions = conf_numDivisions;
	for(int i=0; i<m_size; i++){
		pos_y = -conf_geomSize*conf_numNeighbours;
		neighbLeft = NULL;
		neighbDown = NULL;
		for(int j=0; j<m_size; j++){
			
			if(cont % m_size > 0)
				neighbDown = m_ptrNodes[cont-1];
			if(cont >= m_size)
				neighbLeft = m_ptrNodes[cont-m_size];

			//Calculate lod factor
			numDivisions = conf_numDivisions;
			if(i != center_xy || j != center_xy){
				distanceFromCenter = floor(sqrt(pow((float)center_xy - i, 2) + pow((float)center_xy - j, 2)));
				numDivisions = conf_numDivisions / (distanceFromCenter * conf_lodFactor);
			}


			m_ptrNodes[i*m_size+j] = new SquareNode(cont, m_terrainGenerationShader, m_terrainRenderingShader, 
													Vector3<float>(pos_x,pos_y,0), Vector3<float>(0,0,0), 
													conf_geomSize, conf_textureSize, numDivisions,
													neighbLeft, neighbDown);
			m_ptrNodes[i*m_size+j]->Generate(Vector3<float>(pos_x,pos_y,0), Vector3<float>(0,0,0));


			
			pos_y+=conf_geomSize;
			cont++;

		}
		pos_x+=conf_geomSize;
	}

	m_currentNode = m_ptrNodes[center];

	

}


void TerrainMng::Update(Vector3<float> currentPosition){
	
	

	//See if the camera is on another node. If so, we have to generate its neighbours
	
	//TODO: mix IsWithin with GetNewStandingNode
	//TODO: remove conf_numNeighbours
	if(conf_numNeighbours > 0 && m_currentNode->IsWithin(currentPosition) == false){
		

		int oldIndex = m_currentNode->m_gridIndex;
		int newIndex = m_currentNode->GetNewStandingNodePosition(currentPosition, m_size);

		m_translation.Add(m_ptrNodes[newIndex]->m_relativePosition);
		m_currentNode->m_globalPosition = Vector3<float>(m_translation.GetX(), m_translation.GetY(), 0);
		GenerateNeighbours(oldIndex, newIndex);
	}
}

void TerrainMng::Render(double elapsedTime){
	
	glTranslatef(m_translation.GetX(),m_translation.GetY(), 0);

	//m_sceneGraph->Render();
	//m_terrainRenderingShader->Enable();
	
	//Enable light
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//m_currentNode->Render(elapsedTime);

	m_terrainRenderingShader->Enable();
	for(int i=0; i<m_size; i++){
		for(int j=0; j<m_size; j++){
			m_ptrNodes[i*m_size+j]->Render(elapsedTime);
		}
	}
	m_terrainRenderingShader->Disable();

	glDisable(GL_LIGHTING);

	//m_terrainRenderingShader->Disable();
	m_gui->Render();



}

void TerrainMng::initLight(){
	
	GLfloat LightPosition[] = { 0.0, 0.0, 5.0, 1.0};

	GLfloat DiffuseLight[] = {1.0, 0.0, 0.0};
	GLfloat AmbientLight[] = {0.2, 0.2, 0.2};
	GLfloat SpecularLight[] = {1.0, 1.0, 1.0};

	glLightfv (GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv (GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	GLfloat mShininess[] = {8};

	GLfloat DiffuseMaterial[] = {1.0, 0.0, 0.0};
	GLfloat AmbientMaterial[] = {0.2, 0.2, 0.2};
	GLfloat SpecularMaterial[] = {1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess); 


}

void TerrainMng::GenerateNeighbours(short oldIndex, short newIndex){

	short difference = newIndex - oldIndex;
	//Moving up
	if(difference == 1){
		//Delete lower row
		for(int i=0; i<m_size*m_size; i+=m_size){
			//delete ((HeightMapGPU*)(m_ptrNodes[i]->m_heightMap))->m_ptrFBO;
			m_ptrNodes[i]->m_heightMap->Delete();
			
		}

		//Move intermidiate rows one line down
		for(int i=0; i<m_size-1;i++){
			for(int cont=0; cont<m_size; cont++){
				int j = i + cont*m_size;

				if(m_ptrNodes[j]->m_heightMap->m_gpuOrCpu == GPU)
					((HeightMapGPU*)(m_ptrNodes[j]->m_heightMap))->SwapFBOs(((HeightMapGPU*)(m_ptrNodes[j+1]->m_heightMap))->m_ptrFBO);
			}
		}
		

		//Create upper row
		Vector3<float> position;
		float pos_x = -conf_geomSize*conf_numNeighbours;
		for(int i=m_size-1; i<m_size*m_size; i+=m_size){
			position = Vector3<float>(m_currentNode->m_globalPosition.GetX() + pos_x, m_currentNode->m_globalPosition.GetY() + conf_geomSize*conf_numNeighbours, 0);
			//m_ptrNodes[i]->m_heightMap = new HeightMap(m_terrainGenerationShader, position, conf_geomSize, conf_textureSize, 1);
			m_ptrNodes[i]->ReGenerate(position);

			pos_x+=conf_geomSize;

		}

	}
	//Moving down
	else if(difference == -1){
		//Delete upper row
		for(int i=m_size-1; i<m_size*m_size; i+=m_size){
			//delete m_ptrNodes[i]->m_heightMap;
			m_ptrNodes[i]->m_heightMap->Delete();
			
		}

		//Move intermidiate rows one line up
		for(int i=m_size-1; i>0;i--){
			for(int cont=0; cont<m_size; cont++){
				int j = i + cont*m_size;;
				//m_ptrNodes[j]->m_heightMap = m_ptrNodes[j-1]->m_heightMap;
				if(m_ptrNodes[j]->m_heightMap->m_gpuOrCpu == GPU)
					((HeightMapGPU*)(m_ptrNodes[j]->m_heightMap))->SwapFBOs(((HeightMapGPU*)(m_ptrNodes[j-1]->m_heightMap))->m_ptrFBO);
			}
			
		}
		

		//Create lower row
		Vector3<float> position;
		float pos_x = -conf_geomSize*conf_numNeighbours;
		for(int i=0; i<m_size*m_size; i+=m_size){
			position = Vector3<float>(m_currentNode->m_globalPosition.GetX() + pos_x, m_currentNode->m_globalPosition.GetY() - conf_geomSize*conf_numNeighbours, 0);
			//m_ptrNodes[i]->m_heightMap = new HeightMap(m_terrainGenerationShader, position, conf_geomSize, conf_textureSize, 1);
			m_ptrNodes[i]->ReGenerate(position);

			pos_x+=conf_geomSize;

		}

	}
	//Moving right
	else if(difference == m_size){
		//Delete left colum
		for(int j=0; j<m_size; j++){
			//delete m_ptrNodes[j]->m_heightMap;
			m_ptrNodes[j]->m_heightMap->Delete();
			
		}

		//Move intermidiate colums one colum right
		for(int j=0; j<m_size;j++){
			for(int cont=0; cont<m_size-1; cont++){
				int i = j + cont*m_size;
				//m_ptrNodes[i]->m_heightMap = m_ptrNodes[i+m_size]->m_heightMap;
				if(m_ptrNodes[i]->m_heightMap->m_gpuOrCpu == GPU)
					((HeightMapGPU*)(m_ptrNodes[i]->m_heightMap))->SwapFBOs(((HeightMapGPU*)(m_ptrNodes[i+m_size]->m_heightMap))->m_ptrFBO);
			}	
		}
		

		//Create right colum
		Vector3<float> position;
		float pos_y = -conf_geomSize*conf_numNeighbours;
		for(int i=m_size*(m_size-1); i<m_size*m_size; i++){
			position = Vector3<float>(m_currentNode->m_globalPosition.GetX() + conf_geomSize*conf_numNeighbours, m_currentNode->m_globalPosition.GetY() + pos_y, 0);
			//m_ptrNodes[i]->m_heightMap = new HeightMap(m_terrainGenerationShader, position, conf_geomSize, conf_textureSize, 1);
			m_ptrNodes[i]->ReGenerate(position);

			pos_y+=conf_geomSize;

		}
	}
	//Moving left
	else if(difference == -m_size){
		//Delete right colum
		for(int j=(m_size-1)*m_size; j<m_size*m_size; j++){
			//delete m_ptrNodes[j]->m_heightMap;
			m_ptrNodes[j]->m_heightMap->Delete();
		}

		//Move intermidiate colums one colum left
		for(int j=m_size*(m_size-1); j>0;j-=m_size){
			for(int cont=0; cont<m_size; cont++){
				int i = j + cont;
				//m_ptrNodes[i]->m_heightMap = m_ptrNodes[i-m_size]->m_heightMap;

				if(m_ptrNodes[i]->m_heightMap->m_gpuOrCpu == GPU)
					((HeightMapGPU*)(m_ptrNodes[j]->m_heightMap))->SwapFBOs(((HeightMapGPU*)(m_ptrNodes[i-m_size]->m_heightMap))->m_ptrFBO);
			}	
		}
		

		//Create left colum
		Vector3<float> position;
		float pos_y = -conf_geomSize*conf_numNeighbours;
		for(int i=0; i<m_size; i++){
			position = Vector3<float>(m_currentNode->m_globalPosition.GetX() - conf_geomSize*conf_numNeighbours, m_currentNode->m_globalPosition.GetY() + pos_y, 0);
			//m_ptrNodes[i]->m_heightMap = new HeightMap(m_terrainGenerationShader, position, conf_geomSize, conf_textureSize, 1);
			m_ptrNodes[i]->ReGenerate(position);

			pos_y+=conf_geomSize;

		}

	}
}

//(http://www.sci.utah.edu/~leenak/IndStudy_reportfall/MarbleCode.txt)
void TerrainMng::initPermAndGradTextures()
{
  char *pixels;
  int i,j;
  
  

  

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
	int grad3[16][3] = {
		{1,1,0},
		{-1,1,0},
		{1,-1,0},
		{-1,-1,0},
		{1,0,1},
		{-1,0,1},
		{1,0,-1},
		{-1,0,-1}, 
		{0,1,1},
		{0,-1,1},
		{0,1,-1},
		{0,-1,-1},
		{1,1,0},
		{0,-1,1},
		{-1,1,0},
		{0,-1,-1}
};

	pixels = (char*)malloc( 256*256*4 );
	for(i = 0; i<256; i++)
	for(j = 0; j<256; j++) {
		int offset = (i*256+j)*4;
		char value = perm[(j+perm[i]) & 0xFF];
		pixels[offset] = grad3[value & 0x0F][0] * 64 + 64;   // Gradient x
		pixels[offset+1] = grad3[value & 0x0F][1] * 64 + 64; // Gradient y
		pixels[offset+2] = grad3[value & 0x0F][2] * 64 + 64; // Gradient z
		pixels[offset+3] = value;                     // Permuted index
	}

	glGenTextures(1, &m_permTextureID); // Generate a unique texture ID
	glBindTexture(GL_TEXTURE_2D, m_permTextureID); // Bind the texture to texture unit 0
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
}
