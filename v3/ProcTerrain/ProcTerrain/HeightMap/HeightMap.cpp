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


//TODO: calculate the normal of the heightmap on the generation shader (instead of calculating it each frame on the rendering shader)
void HeightMap::GenerateGPU(GenerationShader* ptrGenerationShader, Vector3<float> globalPosition){

	#ifdef DEBUG_PRINT
	float time = glfwGetTime();
	#endif


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

	FinishGeneration();

	#ifdef DEBUG_PRINT
	time = glfwGetTime() - time;
	cout << "OpenGL calls time (not really the GPU generation time):" << time;
	cout << "\n";
	#endif
	

}

void* HeightMap::CreateThread(void* ptr){
	
	


	HeightMapThreadData* threadData = (HeightMapThreadData*)ptr;

	
	threadData->ptrThis->GenerateCPU(threadData->ptrPermArray, threadData->globalPosition);

	return NULL;

}

void HeightMap::GenerateCPU(char* ptrPermArray, Vector3<float> globalPosition){
	

	SetThreadAffinityMask(GetCurrentThread(), 1);

	BeginGeneration();

	#ifdef DEBUG_PRINT
	float time = glfwGetTime();
	#endif
	
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
			
			//TODO: improve that, there is no need to store the same info three times
			m_heightMapArray[cont] = height;
			m_heightMapArray[cont+1] =height;
			m_heightMapArray[cont+2] = height;
			m_heightMapArray[cont+3] = 1;

			cont+=4;

		}
	}

	#ifdef DEBUG_PRINT
	time = glfwGetTime() - time;
	cout << "CPU Generation time:" << time;
	cout << "\n";
	#endif

	TransferToTexture();

	#ifdef DEBUG_PRINT
	time = glfwGetTime() - time;
	cout << "CPU Transfer to Texture time:" << time;
	cout << "\n";
	#endif

	
	
	FinishGeneration();
	

}

void HeightMap::BeginGeneration(){
	
	pthread_mutex_lock(&m_mutex);
	m_generated = false;
	m_beingGenerated = true;
	pthread_mutex_unlock(&m_mutex); 

}

void HeightMap::FinishGeneration(){

	pthread_mutex_lock(&m_mutex);
	m_generated = true;
	m_beingGenerated = false;
	pthread_mutex_unlock(&m_mutex); 

}

void HeightMap::TransferToTexture(){
	
	//if(glIsTexture(m_heightMapId)) return;


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
