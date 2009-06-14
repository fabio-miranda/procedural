#ifndef FBO_H
#define FBO_H


#include "GL/glew.h"
//#include "GL/glfw.h"
#include "Vertex.h"
#include "Vector3.h"
#include "../Config.h"

/*
typedef struct{
	bool beingUsed;
	GLenum attachment;
} FBOAttachment;
*/

class FBO{

private:
	GLuint m_fbo;
	short m_width;
	short m_height;
	
	//FBOAttachment m_usedAttachments[16];


public:

	FBO(short, short);
	~FBO();
	void DeleteBuffer();
	//void BindTexture(GLuint);
	void Enable(Vector3<float>);
	void Disable();

	GLuint m_textureId;
	GLuint m_renderBufferId;
	
	

};

#endif