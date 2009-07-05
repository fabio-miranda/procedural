#include "FBO.h"


FBO::FBO(GLuint textureId, short width, short height){
	m_width = width;
	m_height = height;
	//GLint maxbuffers;
	//glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxbuffers);
	

	
	glGenFramebuffersEXT(1, &m_fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	

	//TODO: Change the FBOs, so that one FBO can render more than one texture
	//Generate texture
	//glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	//TODO: GL_LINEAR ?
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // automatic mipmap
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
				 GL_RGBA, GL_UNSIGNED_BYTE, 0);
	//glEnable(GL_TEXTURE_2D);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Generate render buffer
	glGenRenderbuffersEXT(1, &m_renderBufferId);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, m_renderBufferId);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, m_width, m_height);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	//Attach texture to the fbo
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, textureId, 0);
	//Attach render buffer to the fbo
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, m_renderBufferId);


	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);



	//TODO: Change the FBOs, so that one FBO can render more than one texture
	/*
	//Init the array to see if a current attachment is being used or not, because OpenGL can only render to 16 textures using the same FBO
	m_usedAttachments[0].beingUsed = false; m_usedAttachments[0].attachment = GL_COLOR_ATTACHMENT0_EXT;
	m_usedAttachments[1].beingUsed = false; m_usedAttachments[1].attachment = GL_COLOR_ATTACHMENT1_EXT;
	m_usedAttachments[2].beingUsed = false; m_usedAttachments[2].attachment = GL_COLOR_ATTACHMENT2_EXT;
	m_usedAttachments[3].beingUsed = false; m_usedAttachments[3].attachment = GL_COLOR_ATTACHMENT3_EXT;
	m_usedAttachments[4].beingUsed = false; m_usedAttachments[4].attachment = GL_COLOR_ATTACHMENT4_EXT;
	m_usedAttachments[5].beingUsed = false; m_usedAttachments[5].attachment = GL_COLOR_ATTACHMENT5_EXT;
	m_usedAttachments[6].beingUsed = false; m_usedAttachments[6].attachment = GL_COLOR_ATTACHMENT6_EXT;
	m_usedAttachments[7].beingUsed = false; m_usedAttachments[7].attachment = GL_COLOR_ATTACHMENT7_EXT;
	m_usedAttachments[8].beingUsed = false; m_usedAttachments[8].attachment = GL_COLOR_ATTACHMENT8_EXT;
	m_usedAttachments[9].beingUsed = false; m_usedAttachments[9].attachment = GL_COLOR_ATTACHMENT9_EXT;
	m_usedAttachments[10].beingUsed = false; m_usedAttachments[10].attachment = GL_COLOR_ATTACHMENT10_EXT;
	m_usedAttachments[11].beingUsed = false; m_usedAttachments[11].attachment = GL_COLOR_ATTACHMENT11_EXT;
	m_usedAttachments[12].beingUsed = false; m_usedAttachments[12].attachment = GL_COLOR_ATTACHMENT12_EXT;
	m_usedAttachments[13].beingUsed = false; m_usedAttachments[13].attachment = GL_COLOR_ATTACHMENT13_EXT;
	m_usedAttachments[14].beingUsed = false; m_usedAttachments[14].attachment = GL_COLOR_ATTACHMENT14_EXT;
	m_usedAttachments[15].beingUsed = false; m_usedAttachments[15].attachment = GL_COLOR_ATTACHMENT15_EXT;
	*/

}

FBO::~FBO(){
	DeleteBuffer();

}
/*
void FBO::BindTexture(GLuint m_textureId){
	
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_textureId, 0);


}
*/

void FBO::Enable(Vector3<float> position){
	//position = Vector3<float>(0,0,0);

	glPushAttrib(GL_ENABLE_BIT | GL_POLYGON_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
	glOrtho(position.GetX(), position.GetX() + m_width, position.GetY() + m_height, position.GetY(), -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glViewport(0, 0, m_width, m_height);
	

	//glEnable(GL_TEXTURE_2D);
	

	//TODO: change to glDrawBuffer (http://www.mathematik.uni-dortmund.de/~goeddeke/gpgpu/tutorial.html#feedback2)
	//glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	//glBindTexture(GL_TEXTURE_2D, m_textureId);

	glClearColor (0.1f, 0.1f, 0.1f, 1.0f);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glPopAttrib();

}

void FBO::Disable(){
	glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glViewport(0, 0, 1280, 720);

    glPopAttrib();



	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);


}



void FBO::DeleteBuffer(){
	glDeleteFramebuffersEXT(1, &m_fbo);
	//glDeleteTextures( 1, &m_textureId );

}
