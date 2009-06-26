#include "HeightMapCPU.h"


HeightMapCPU::HeightMapCPU(RenderingShader* renderingShader, char* ptrPermArray,
						   Vector3<float> relativePosition, Vector3<float> globalPosition, 
						   float geomSize, short numDivisions, 
						   int octaves, float lacunarity, float gain, float offset)
						   : HeightMap(renderingShader, relativePosition, globalPosition, geomSize, numDivisions,octaves,lacunarity,gain,offset){

	m_gpuOrCpu = GPU;
	m_ptrPermArray = ptrPermArray;
	
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
float HeightMapCPU::noise(Vector3<float> P)
{
	Vector3<float> aux;

	Vector3<float> Pfloor = Vector3<float>(P);
	Pfloor.Floor();

	Vector3<float> Pi = Vector3<float>(Pfloor);
	Pi.Mult(ONE);
	Pi.Add(ONEHALF);


	                             
	Vector3<float> Pf = Vector3<float>(P);
	Pf.Sub(Pfloor);

	// Noise contributions from (x=0, y=0), z=0 and z=1
	//float perm00 = texture2D(permTexture, Pi.xy).a;
	int perm00 = m_ptrPermArray[(int)(Pi.GetX()*256 + Pi.GetY() + 3)];
	//vec3  grad000 = texture2D(permTexture, vec2(perm00, Pi.z)).rgb * 4.0 - 1.0;
	//vec3  grad000 = m_ptrPermArray[perm00*256 + Pi.GetZ] * 4.0 - 1.0;
	Vector3<float> grad000 = Vector3<float>(m_ptrPermArray[(int)(perm00*256 + Pi.GetZ())] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm00*256 + Pi.GetZ() + 1)] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm00*256 + Pi.GetZ() + 2)] * 4.0 - 1.0);

	//float n000 = dot(grad000, Pf);
	float n000 = grad000.Dot(Pf);

	// Noise contributions from (x=0, y=1), z=0 and z=1
	//float perm01 = texture2D(permTexture, Pi.xy + vec2(0.0, ONE)).a ;
	//vec3  grad010 = texture2D(permTexture, vec2(perm01, Pi.z)).rgb * 4.0 - 1.0;
	//float n010 = dot(grad010, Pf - vec3(0.0, 1.0, 0.0));
	aux = Vector3<float>(Pi.GetX(), Pi.GetY() + ONE, 0);
	int perm01 = m_ptrPermArray[(int)(aux.GetX()*256 + aux.GetY() + 3)];
	Vector3<float> grad010 = Vector3<float>(m_ptrPermArray[(int)(perm01*256 + Pi.GetZ())] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm01*256 + Pi.GetZ() + 1)] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm01*256 + Pi.GetZ() + 2)] * 4.0 - 1.0);
	aux = Vector3<float>(Pf.GetX(), Pf.GetY() - 1.0, Pf.GetZ());
	float n010 = grad010.Dot(aux);

	// Noise contributions from (x=1, y=0), z=0 and z=1
	//float perm10 = texture2D(permTexture, Pi.xy + vec2(ONE, 0.0)).a ;
	//vec3  grad100 = texture2D(permTexture, vec2(perm10, Pi.z)).rgb * 4.0 - 1.0;
	//float n100 = dot(grad100, Pf - vec3(1.0, 0.0, 0.0));
	aux = Vector3<float>(Pi.GetX() + ONE, Pi.GetY(), 0);
	int perm10 = m_ptrPermArray[(int)(aux.GetX()*256 + aux.GetY() + 3)];
	Vector3<float> grad100 = Vector3<float>(m_ptrPermArray[(int)(perm10*256 + Pi.GetZ())] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm10*256 + Pi.GetZ() + 1)] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm10*256 + Pi.GetZ() + 2)] * 4.0 - 1.0);
	aux = Vector3<float>(Pf.GetX() - 1.0, Pf.GetY(), Pf.GetZ());
	float n100 = grad100.Dot(aux);

	// Noise contributions from (x=1, y=1), z=0 and z=1
	//float perm11 = texture2D(permTexture, Pi.xy + vec2(ONE, ONE)).a ;
	//vec3  grad110 = texture2D(permTexture, vec2(perm11, Pi.z)).rgb * 4.0 - 1.0;
	//float n110 = dot(grad110, Pf - vec3(1.0, 1.0, 0.0));
	aux = Vector3<float>(Pi.GetX() + ONE, Pi.GetY() + ONE, 0);
	int perm11 = m_ptrPermArray[(int)(aux.GetX()*256 + aux.GetY() + 3)];
	Vector3<float> grad110 = Vector3<float>(m_ptrPermArray[(int)(perm11*256 + Pi.GetZ())] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm11*256 + Pi.GetZ() + 1)] * 4.0 - 1.0,
											m_ptrPermArray[(int)(perm11*256 + Pi.GetZ() + 2)] * 4.0 - 1.0);
	aux = Vector3<float>(Pf.GetX() - 1.0, Pf.GetY() - 1.0, Pf.GetZ());
	float n110 = grad110.Dot(aux);

	// Blend contributions along x
	Vector2<float> n_x = mix(Vector2<float>(n000, n010), Vector2<float>(n100, n110), fade(Pf.GetX()));

	// Blend contributions along y
	float n_xy = mix(n_x.GetX(), n_x.GetY(), fade(Pf.GetY()));


	return n_xy;
}

Vector2<float> HeightMapCPU::mix(Vector2<float> a, Vector2<float> b, float weight){
	
	//TODO: improve that. Substitute Mult with * operator
	a.Mult(1.0 - weight);
	b.Mult(weight);

	a.Add(b);
	return a;
}

float HeightMapCPU::mix(float a, float b, float weight){

	return a * (1.0 - weight) + b * weight;

}



void HeightMapCPU::Generate(){
	if(m_generated) return;


	float time = glfwGetTime();
	int cont = 0;
	Vector3<float> position;
	for(float i=0; i<=m_geomSize ; i+=m_face->m_divisionSize){
		for(float j=0; j<=m_geomSize; j+=m_face->m_divisionSize){
			
			position = Vector3<float>(0,
									  0,
										0);
			m_face->m_vertices[cont].z = ridgedmf(position) / 100000.0;
			cont++;

		}
	}
	time = glfwGetTime() - time;
	cout << time * 1000.0f;
	cout << "\n";




	m_generated = true;
}

void HeightMapCPU::Render(double elapsedTime){
	if(m_time > 1) m_time -= elapsedTime;

	glUniform1f(m_ptrRenderingShader->m_locGPUGenerated, 0.0);
	m_face->Render();

}

