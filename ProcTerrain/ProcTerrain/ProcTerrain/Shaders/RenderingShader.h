#ifndef RenderingShader_H
#define RenderingShader_H

#include "Shader.h"


class RenderingShader : public Shader{
	
	
public:
	RenderingShader(bool complex);
	~RenderingShader();
	GLuint m_locTexture;
	GLuint m_locTime;
	GLuint m_locGPUGenerated;
	GLuint m_locShowBlendTexture;
	GLuint m_locShowLight;
	GLuint m_locShowHeightMap;
	GLuint m_locShowVerticesDisplacement;
	GLuint *m_locBlendTextures;
	

};


#endif