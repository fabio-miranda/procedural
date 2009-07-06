#include "HeightMap.h"


HeightMap::HeightMap(Vector3<float> relativePosition, float geomSize, short numDivisions, short textureSize,
					 int octaves, float lacunarity, float gain, float offset){
	


	m_relativePosition = relativePosition;
	//m_globalPosition = relativePosition;
	//m_globalPosition.Add(translation);

	m_textureSize = textureSize;
	m_geomSize = geomSize;
	m_numDivisions = numDivisions;
	m_generated = false;
	m_beingGenerated = false;
	pthread_mutex_init(&m_mutex, NULL);

	m_time = 5.0f; //time since the generation of the heightmap

	m_face = new VBOSquare(m_relativePosition, m_geomSize + 0.1f, m_numDivisions);

	
	//m_ptrFBO = new FBO(m_heightMapId, textureSize, textureSize);
	
	//
	m_octaves = octaves;
	m_lacunarity = lacunarity;
	m_gain = gain;
	m_offset = offset;


	
	
}

//TODO: delete properly
HeightMap::~HeightMap(){

}

void HeightMap::SwapHeightMap(HeightMap* heightMap){

	//glDeleteTextures( 1, &m_heightMapId );
	m_heightMapId = heightMap->m_heightMapId;

}

void HeightMap::Render(double elapsedTime, RenderingShader* ptrRenderingShader){
	if(m_time > 1) m_time -= elapsedTime;


	//m_ptrRenderingShader->Enable();

	glEnable(GL_TEXTURE_2D);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_heightMapId);
	
	glUniform1f(ptrRenderingShader->m_locTime, m_time);
	glUniform1f(ptrRenderingShader->m_locGPUGenerated, 1.0);
	glUniform1f(ptrRenderingShader->m_locShowHeightMap, conf_showHeightMap);
	glUniform1f(ptrRenderingShader->m_locShowLight, conf_showLight);
	glUniform1f(ptrRenderingShader->m_locShowBlendTexture, conf_showBlendTexture);
	glUniform1f(ptrRenderingShader->m_locShowVerticesDisplacement, conf_showVerticesDisplacement);
	
	/*
	for(int i=0; i<4; i++)
	{
		glUniform1i(m_ptrRenderingShader->m_locBlendTextures[i], 0);
		glActiveTexture(GL_TEXTURE1+i);
		glBindTexture(GL_TEXTURE_2D, m_ptrBlendTextures[i]);
		
	}
	*/
	
	
	

	
	//TODO: do it only once, after generating the heightmap
	//there is no need to do it every frame: http://www.gamedev.net/community/forums/mod/journal/journal.asp?jn=530427&reply_id=3450696
	//glUniform1i(m_ptrTerrainRenderingShader->m_locTexture, 0);
	

	m_face->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

	//m_ptrRenderingShader->Disable();

}

//TODO: calculate the normal of the heightmap on the generation shader (instead of calculating it each frame on the rendering shader)
void HeightMap::GenerateGPU(GenerationShader* ptrGenerationShader, Vector3<float> globalPosition){


	float time = glfwGetTime();


	//Simple square has to have the same size as the FBO
	
	SimpleSquare* simpleSquare = new SimpleSquare(globalPosition, m_textureSize, m_geomSize);

	//TODO: re-use the fbo?
	glGenTextures(1, &m_heightMapId);
	FBO ptrFBO = FBO(m_heightMapId, m_textureSize, m_textureSize);


	
	ptrFBO.Enable(globalPosition);
	ptrGenerationShader->Enable();
	
	//Uniform variables
	glUniform1i(ptrGenerationShader->m_locOctaves, m_octaves);
	glUniform1f(ptrGenerationShader->m_locLacunarity, m_lacunarity);
	glUniform1f(ptrGenerationShader->m_locGain, m_gain);
	glUniform1f(ptrGenerationShader->m_locOffset, m_offset);
	
	simpleSquare->Render();
	

	ptrGenerationShader->Disable();
	ptrFBO.Disable();

	/*
	m_currentIteration++;
	if(m_currentIteration >= m_maxIterations){
		m_generated = true;
	}
	*/

	//glFinish();

	m_generated = true;

	time = glfwGetTime() - time;
	cout << time * 1000.0f;
	cout << "\n";
	

}

void* HeightMap::CreateThread(void* ptr){
	

	HeightMapThreadData* threadData = (HeightMapThreadData*)ptr;
	
	threadData->ptrThis->GenerateCPU(threadData->ptrPermArray, threadData->globalPosition);

	return NULL;

}

void HeightMap::GenerateCPU(char* ptrPermArray, Vector3<float> globalPosition){

	

	float time = glfwGetTime();
	float height = 0;
	int cont = 0;
	Vector3<float> position;
	m_heightMapArray = (char*)malloc(4 * m_textureSize * m_textureSize);
	for(float i=0; i<m_textureSize ; i++){
		for(float j=0; j<m_textureSize; j++){
			
			position = Vector3<float>(i / 5.0, j / 5.0, 0);
			//m_face->m_vertices[cont].z = ridgedmf(position) / 100000.0;
			height = HeightMap::ridgedmf(ptrPermArray, position, m_octaves, m_gain, m_lacunarity, m_offset) * 250.0f;
			//m_face->m_vertices[cont].z = (i + j) / 100.0;
			
			//TODO: improve that
			m_heightMapArray[cont] = height;
			m_heightMapArray[cont+1] =height;
			m_heightMapArray[cont+2] = height;
			m_heightMapArray[cont+3] = 1;

			cont+=4;

		}
	}
	time = glfwGetTime() - time;
	cout << time * 1000.0f;
	cout << "\n";

	
	pthread_mutex_lock(&m_mutex);
	m_generated = true;
	pthread_mutex_unlock(&m_mutex); 

}

void HeightMap::TransferToTexture(){
	
	if(glIsTexture(m_heightMapId)) return;


	glGenTextures(1, &m_heightMapId);
	glBindTexture( GL_TEXTURE_2D, m_heightMapId );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_textureSize, m_textureSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_heightMapArray );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glBindTexture( GL_TEXTURE_2D, 0 );

	delete[] m_heightMapArray;

}


void HeightMap::Delete(){
	glDeleteTextures( 1, &m_heightMapId );
}

float HeightMap::ridgedmf(char* ptrPermArray, Vector3<float> position, int octaves, float gain, float lacunarity, float offset)
{
	float sum = 0.0;
	float freq = 1.0, amp = 0.5;
	float prev = 1.0;

	for(int i=0; i<octaves; i++) {
		position.Mult(freq);
		float n = HeightMap::ridge(HeightMap::noise(ptrPermArray, position), offset);
		sum += n*amp*prev;
		prev = n;
		freq *= lacunarity;
		amp *= gain;
	}
	return sum;
}

float HeightMap::ridge(float h, float offset)
{
    h = abs(h);
    h = offset - h;
    h = h * h;
    return h;
}

float HeightMap::fade(float t) {
	//return t*t*(3.0-2.0*t); // Old fade
	return t*t*t*(t*(t*6.0-15.0)+10.0); // Improved fade
}

//http://mrl.nyu.edu/~perlin/noise/
float HeightMap::noise(char* ptrPermArray, Vector3<float> P)
{
	Vector3<int> Pint = Vector3<int>((int)floor(P.GetX()) & 255, (int)floor(P.GetY()) & 255, (int)floor(P.GetZ()) & 255);
	Vector3<float> Pfloat = Vector3<float>(P);
	Vector3<float> Pfloor = Vector3<float>(floor(P.GetX()), floor(P.GetY()), floor(P.GetZ()));

	Pfloat.Sub(Pfloor);
	Vector3<float> faded = Vector3<float>(fade(Pfloat.GetX()), fade(Pfloat.GetY()), fade(Pfloat.GetZ()));

	int A = ptrPermArray[Pint.GetX()  ]+Pint.GetY();
	int AA = ptrPermArray[A]+Pint.GetZ();
	int AB = ptrPermArray[A+1]+Pint.GetZ();
	int B = ptrPermArray[Pint.GetX()+1]+Pint.GetY();
	int BA = ptrPermArray[B]+Pint.GetZ();
	int BB = ptrPermArray[B+1]+Pint.GetZ();
	


	return HeightMap::mix(faded.GetZ(),  
							HeightMap::mix(faded.GetY(), 
								HeightMap::mix( faded.GetX(),HeightMap::grad(ptrPermArray[AA], Pfloat.GetX()  , Pfloat.GetY()  , Pfloat.GetZ() ), HeightMap::grad(ptrPermArray[BA], Pfloat.GetX()-1  , Pfloat.GetY()  , Pfloat.GetZ() )),
								HeightMap::mix( faded.GetX(), HeightMap::grad(ptrPermArray[AB], Pfloat.GetX()  , Pfloat.GetY()-1  , Pfloat.GetZ() ), HeightMap::grad(ptrPermArray[BB], Pfloat.GetX()-1  , Pfloat.GetY()-1  , Pfloat.GetZ() ))),
							HeightMap::mix(faded.GetY(), 
								HeightMap::mix( faded.GetX(),HeightMap::grad(ptrPermArray[AA+1], Pfloat.GetX()  , Pfloat.GetY()  , Pfloat.GetZ()-1 ), HeightMap::grad(ptrPermArray[BA+1], Pfloat.GetX()-1  , Pfloat.GetY()  , Pfloat.GetZ()-1 )),
								HeightMap::mix( faded.GetX(), HeightMap::grad(ptrPermArray[AB+1], Pfloat.GetX()  , Pfloat.GetY()-1  , Pfloat.GetZ()-1 ), HeightMap::grad(ptrPermArray[BB+1], Pfloat.GetX()-1  , Pfloat.GetY()-1  , Pfloat.GetZ()-1 )))
				);
	
	
}

double HeightMap::grad(int hash, float x, float y, float z) {
	/*
	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
		 v = h<4 ? y : h==12||h==14 ? x : z;
	return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
	*/
	return hash;
}



float HeightMap::mix(float weight, float a, float b){

	return a + weight*(b - a);

}
