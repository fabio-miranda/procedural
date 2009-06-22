#ifndef RenderingShader_H
#define RenderingShader_H

#include "Shader.h"


class RenderingShader : public Shader{
	
	
public:
	RenderingShader();
	~RenderingShader();
	GLuint m_locTexture;
	GLuint m_locTime;
	GLuint m_locGPUGenerated;
	

};


#endif