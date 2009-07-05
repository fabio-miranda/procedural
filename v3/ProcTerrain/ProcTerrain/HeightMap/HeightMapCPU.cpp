#include "HeightMapCPU.h"


HeightMapCPU::HeightMapCPU(RenderingShader* renderingShader, char* ptrPermArray,
						   Vector3<float> relativePosition, Vector3<float> globalPosition, 
						   float geomSize, short numDivisions, short textureSize,
						   int octaves, float lacunarity, float gain, float offset)
						   : HeightMap(renderingShader, relativePosition, globalPosition, geomSize, numDivisions, textureSize, octaves,lacunarity,gain,offset){

	m_gpuOrCpu = GPU;
	m_ptrPermArray = ptrPermArray;
	m_heightMap = (char*)malloc(4 * m_textureSize * m_textureSize);
	
}

//TODO: delete properly
HeightMapCPU::~HeightMapCPU(){

}

float HeightMapCPU::ridgedmf(Vector3<float> position)
{
	float sum = 0.0;
	float freq = 1.0, amp = 0.5;
	float prev = 1.0;

	for(int i=0; i<m_octaves; i++) {
		position.Mult(freq);
		float n = ridge(noise(position), m_offset);
		sum += n*amp*prev;
		prev = n;
		freq *= m_lacunarity;
		amp *= m_gain;
	}
	return sum;
}

float HeightMapCPU::ridge(float h, float offset)
{
    h = abs(h);
    h = offset - h;
    h = h * h;
    return h;
}

float HeightMapCPU::fade(float t) {
	//return t*t*(3.0-2.0*t); // Old fade
	return t*t*t*(t*(t*6.0-15.0)+10.0); // Improved fade
}

#define ONE 0.00390625
#define ONEHALF 0.001953125

//http://mrl.nyu.edu/~perlin/noise/
float HeightMapCPU::noise(Vector3<float> P)
{
	Vector3<int> Pint = Vector3<int>((int)floor(P.GetX()) & 255, (int)floor(P.GetY()) & 255, (int)floor(P.GetZ()) & 255);
	Vector3<float> Pfloat = Vector3<float>(P);
	Vector3<float> Pfloor = Vector3<float>(floor(P.GetX()), floor(P.GetY()), floor(P.GetZ()));

	Pfloat.Sub(Pfloor);
	Vector3<float> faded = Vector3<float>(fade(Pfloat.GetX()), fade(Pfloat.GetY()), fade(Pfloat.GetZ()));

	int A = m_ptrPermArray[Pint.GetX()  ]+Pint.GetY();
	int AA = m_ptrPermArray[A]+Pint.GetZ();
	int AB = m_ptrPermArray[A+1]+Pint.GetZ();
	int B = m_ptrPermArray[Pint.GetX()+1]+Pint.GetY();
	int BA = m_ptrPermArray[B]+Pint.GetZ();
	int BB = m_ptrPermArray[B+1]+Pint.GetZ();
	


	return mix(faded.GetZ(),  
					mix(faded.GetY(), 
						mix( faded.GetX(),grad(m_ptrPermArray[AA], Pfloat.GetX()  , Pfloat.GetY()  , Pfloat.GetZ() ), grad(m_ptrPermArray[BA], Pfloat.GetX()-1  , Pfloat.GetY()  , Pfloat.GetZ() )),
						mix( faded.GetX(), grad(m_ptrPermArray[AB], Pfloat.GetX()  , Pfloat.GetY()-1  , Pfloat.GetZ() ), grad(m_ptrPermArray[BB], Pfloat.GetX()-1  , Pfloat.GetY()-1  , Pfloat.GetZ() ))),
					mix(faded.GetY(), 
						mix( faded.GetX(),grad(m_ptrPermArray[AA+1], Pfloat.GetX()  , Pfloat.GetY()  , Pfloat.GetZ()-1 ), grad(m_ptrPermArray[BA+1], Pfloat.GetX()-1  , Pfloat.GetY()  , Pfloat.GetZ()-1 )),
						mix( faded.GetX(), grad(m_ptrPermArray[AB+1], Pfloat.GetX()  , Pfloat.GetY()-1  , Pfloat.GetZ()-1 ), grad(m_ptrPermArray[BB+1], Pfloat.GetX()-1  , Pfloat.GetY()-1  , Pfloat.GetZ()-1 )))
				);




	
	
}

double HeightMapCPU::grad(int hash, float x, float y, float z) {
	/*
	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	double u = h<8 ? x : y,                 // INTO 12 GRADIENT DIRECTIONS.
		 v = h<4 ? y : h==12||h==14 ? x : z;
	return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
	*/
	return hash;
}



float HeightMapCPU::mix(float weight, float a, float b){

	return a + weight*(b - a);

}



void HeightMapCPU::Generate(){
	if(m_generated) return;


	float time = glfwGetTime();
	float height = 0;
	int cont = 0;
	Vector3<float> position;
	for(float i=0; i<m_textureSize ; i++){
		for(float j=0; j<m_textureSize; j++){
			
			position = Vector3<float>(i / 5.0, j / 5.0, 0);
			//m_face->m_vertices[cont].z = ridgedmf(position) / 100000.0;
			height = ridgedmf(position) * 250.0f;
			//m_face->m_vertices[cont].z = (i + j) / 100.0;
			
			//TODO: improve that
			m_heightMap[cont] = height;
			m_heightMap[cont+1] =height;
			m_heightMap[cont+2] = height;
			m_heightMap[cont+3] = 1;

			cont+=4;

		}
	}
	time = glfwGetTime() - time;
	cout << time * 1000.0f;
	cout << "\n";




	m_generated = true;
	InitTexture();
}


void HeightMapCPU::InitTexture(){

	glGenTextures(1, &m_textureId);
	glGenBuffersARB(1, &m_pboId);

	/*
	glBindTexture (GL_TEXTURE,m_textureId);
	glTexParameteri (GL_TEXTURE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri (GL_TEXTURE, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri (GL_TEXTURE, GL_TEXTURE_WRAP_T, GL_CLAMP); 
	glTexImage2D (GL_TEXTURE, 0, GL_RGBA, m_textureSize, m_textureSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0); 

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, m_pboId);
	glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB,m_textureSize*m_textureSize* 4 * sizeof(float), NULL, GL_STREAM_DRAW);
	void* ioMem = glMapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, GL_WRITE_ONLY);

	memcpy(ioMem, m_heightMap, m_textureSize * m_textureSize * 4 * sizeof(float));

	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER_ARB);
	glTexSubImage2D(GL_TEXTURE, 0, 0, 0, m_textureSize, m_textureSize, GL_BGRA, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
	glBindBufferARB(GL_PIXEL_UNPACK_BUFFER_ARB,0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER_ARB, 0);
	*/

	//TODO: use PBO
	/*
	glBindTexture( GL_TEXTURE_2D, m_textureId );
	glTexSubImage2D( GL_TEXTURE_2D,0,0,0, m_textureSize, m_textureSize, GL_BGRA, GL_UNSIGNED_BYTE, m_heightMap);
	glBindTexture( GL_TEXTURE_2D, 0 );
	*/
	glBindTexture( GL_TEXTURE_2D, m_textureId );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_textureSize, m_textureSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_heightMap );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glBindTexture( GL_TEXTURE_2D, 0 );




}

void HeightMapCPU::Render(double elapsedTime){
	if(m_time > 1) m_time -= elapsedTime;


	glEnable(GL_TEXTURE_2D);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_textureId);
	
	glUniform1f(m_ptrRenderingShader->m_locTime, m_time);
	glUniform1f(m_ptrRenderingShader->m_locGPUGenerated, 1.0);
	glUniform1f(m_ptrRenderingShader->m_locShowHeightMap, conf_showHeightMap);
	glUniform1f(m_ptrRenderingShader->m_locShowLight, conf_showLight);
	glUniform1f(m_ptrRenderingShader->m_locShowBlendTexture, conf_showBlendTexture);
	glUniform1f(m_ptrRenderingShader->m_locShowVerticesDisplacement, conf_showVerticesDisplacement);
	
	m_face->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);

}

