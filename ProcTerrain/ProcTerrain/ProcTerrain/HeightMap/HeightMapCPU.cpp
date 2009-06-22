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

void HeightMapCPU::Generate(){


}

void HeightMapCPU::Render(double elapsedTime){
	if(m_time > 1) m_time -= elapsedTime;


}

