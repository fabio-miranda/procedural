#include "HeightMapCPU.h"


HeightMapCPU::HeightMapCPU(RenderingShader* renderingShader, 
						   Vector3<float> relativePosition, Vector3<float> globalPosition, 
						   float geomSize, short numDivisions)
						   : HeightMap(renderingShader, relativePosition, globalPosition, geomSize, numDivisions){

	m_gpuOrCpu = GPU;
	
}

//TODO: delete properly
HeightMapCPU::~HeightMapCPU(){

}

float HeightMapCPU::ridgedmf(Vector3<float> position)
{
	float sum = 0.0;
	float freq = 1.0, amp = 0.5;
	float prev = 1.0;

	//temp:
	m_offset = 0;
	m_octaves = 10;
	m_lacunarity = 0.5;
	m_gain = 0.5;
	m_seed = 353;

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

float HeightMapCPU::noise(Vector3<float> P){
	
	//xf = ((float)x_pixel + m_position.GetX()) / (float)m_width;
	//zf = ((float)y_pixel + m_position.GetZ()) / (float)m_height;
	float xf = P.GetX();
	float zf = P.GetZ();


	//Calculate frequency and amplitude
	//freq = pow(2.0, i);
	//amp = pow(m_persistence, i);

	//Calculate x, z noise coordinates
	//tx = xf * freq;
	//tz = zf * freq;

	//Calculate the fractions of x and z
	//fracx = tx - (int)tx;
	float fracx = xf - (int)xf;
	//fracz = tz - (int)tz;
	float fracz = zf - (int)zf;

	//Get noise per octave for the four points
	float v1 = GetNoise((int)xf + (int)zf * 57 + m_seed);
	float v2 = GetNoise((int)xf + 1 + (int)zf * 57 + m_seed);
	float v3 = GetNoise((int)xf + ((int)zf + 1) * 57 + m_seed);
	float v4 = GetNoise((int)xf + 1 + ((int)zf + 1) * 57 + m_seed);

	//Smooth noise in the x axis
	float i1 = CosineInterpolation(v1, v2, fracx);
	float i2 = CosineInterpolation(v3, v4, fracx);

	//Smooth in the z axis
	return CosineInterpolation(i1, i2, fracz);


}

float HeightMapCPU::ridge(float h, float offset)
{
    h = abs(h);
    h = offset - h;
    h = h * h;
    return h;
}

float HeightMapCPU::CosineInterpolation(float a, float b, float x){
        float ft = x * 3.1415927;
        float f = (1 - cos(ft)) * 0.5f;

        return a * (1 - f) + b * f;
}

float HeightMapCPU::GetNoise(int i){
        i = (i << 13) ^ i;
        return (1.0f - ((i * (i * i * 15731 + 789221) + 1376312589) & 0x7FFFFFFF) / 1073741824.0f);
}





void HeightMapCPU::Generate(){
	if(m_generated) return;



	int cont = 0;
	Vector3<float> position;
	for(float i=0; i<=m_geomSize ; i+=m_face->m_divisionSize){
		for(float j=0; j<=m_geomSize; j+=m_face->m_divisionSize){
			
			position = Vector3<float>(m_face->m_vertices[cont].x, m_face->m_vertices[cont].y, m_face->m_vertices[cont].z);
			m_face->m_vertices[cont].z = ridgedmf(position);
			cont++;

		}
	}



	m_generated = true;
}

void HeightMapCPU::Render(double elapsedTime){
	if(m_time > 1) m_time -= elapsedTime;

	glUniform1f(m_ptrRenderingShader->m_locGPUGenerated, 0.0);
	m_face->Render();

}

