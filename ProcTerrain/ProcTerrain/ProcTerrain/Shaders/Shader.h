#ifndef Shader_H
#define Shader_H

#include "GL/glew.h"
#include "../Util/textfile.h"


class Shader{
	
	
public:
	Shader(char*, char*);
	~Shader();
	virtual void Enable();
	virtual void Disable();


private:
	GLhandleARB m_shaderVert;
	GLhandleARB m_shaderFrag;
	GLhandleARB m_shaderProg;


};


#endif