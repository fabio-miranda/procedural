#include "stdafx.h"
#include "Skybox.h"
#include "Vector3.h"
#include "GL/glfw.h"
#include <IL/il.h>
#include <iostream>
using namespace std;


Skybox::Skybox(){
	LoadTexture("../POC/Content/Textures/Skybox/PositiveY.png", m_texture0, GL_TEXTURE0_ARB);
	LoadTexture("../POC/Content/Textures/Skybox/NegativeY.png", m_texture1, GL_TEXTURE1_ARB);
	LoadTexture("../POC/Content/Textures/Skybox/NegativeZ.png", m_texture5, GL_TEXTURE2_ARB);
	LoadTexture("../POC/Content/Textures/Skybox/PositiveZ.png", m_texture4, GL_TEXTURE2_ARB);
	LoadTexture("../POC/Content/Textures/Skybox/NegativeX.png", m_texture2, GL_TEXTURE2_ARB);
	LoadTexture("../POC/Content/Textures/Skybox/PositiveX.png", m_texture3, GL_TEXTURE2_ARB);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(1, -1, -1, 1, 1, 10000.0);
	glMatrixMode(GL_MODELVIEW);

}


void Skybox::LoadTexture(char* end, GLuint& texture, GLuint textureIndex){
	//Load textures
	ILuint image_name;
	
	ilGenImages(1, &image_name); /* Generation of one image name */
	ilBindImage(image_name); /* Binding of image name */
	if(!ilLoadImage(end)){ /* Loading of image "image.jpg" */
		glfwTerminate();
		cout << "Error loading texture ";
		cout << end;
		cout << "\n";

	}

	//glActiveTextureARB(textureIndex);
	glGenTextures(1, &texture); /* Texture name generation */
    glBindTexture(GL_TEXTURE_2D, texture); /* Binding of texture name */

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), 
					ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());



	/*
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	*/
	
	ilDeleteImages(1, &image_name); /* Because we have already copied image data into texture data
    we can release memory used by image. */
	
}

void Skybox::RenderSkybox(Vector3<float> camera_position){

	//Skybox
	glDisable(GL_CULL_FACE);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
    


	// Begin DrawSkybox
	glColor4f(1.0, 1.0, 1.0,1.0f);
 
	// Save Current Matrix
	glPushMatrix();
 
	// Second Move the render space to the correct position (Translate)
	glTranslatef(camera_position.GetX(),camera_position.GetY(),camera_position.GetZ());
	//glTranslatef(0,0,0);
 
	// First apply scale matrix
	glScalef(10,10,10);
 
	float cz = -0.0f,cx = 1.0f;
	float r = -1.0f; // If you have border issues change this to 1.005f
	// Common Axis Z - FRONT Side
	glBindTexture(GL_TEXTURE_2D,m_texture0);
	glBegin(GL_QUADS);	
		glTexCoord2f(cx, cz); glVertex3f(-r ,1.0f,-r);
		glTexCoord2f(cx,  cx); glVertex3f(-r,1.0f,r);
		glTexCoord2f(cz,  cx); glVertex3f( r,1.0f,r); 
		glTexCoord2f(cz, cz); glVertex3f( r ,1.0f,-r);
	glEnd();
 
	// Common Axis Z - BACK side
	glBindTexture(GL_TEXTURE_2D,m_texture1);
	glBegin(GL_QUADS);		
		glTexCoord2f(cx,cz);  glVertex3f(-r,-1.0f,-r);
		glTexCoord2f(cx,cx);  glVertex3f(-r,-1.0f, r);
		glTexCoord2f(cz,cx);  glVertex3f( r,-1.0f, r); 
		glTexCoord2f(cz,cz);  glVertex3f( r,-1.0f,-r);
	glEnd();
 
	// Common Axis X - Left side
	glBindTexture(GL_TEXTURE_2D,m_texture2);
	glBegin(GL_QUADS);		
		glTexCoord2f(cx,cx); glVertex3f(-1.0f, -r, r);	
		glTexCoord2f(cz,cx); glVertex3f(-1.0f,  r, r); 
		glTexCoord2f(cz,cz); glVertex3f(-1.0f,  r,-r);
		glTexCoord2f(cx,cz); glVertex3f(-1.0f, -r,-r);		
	glEnd();
 
	// Common Axis X - Right side
	glBindTexture(GL_TEXTURE_2D,m_texture3);
	glBegin(GL_QUADS);		
		glTexCoord2f( cx,cx); glVertex3f(1.0f, -r, r);	
		glTexCoord2f(cz, cx); glVertex3f(1.0f,  r, r); 
		glTexCoord2f(cz, cz); glVertex3f(1.0f,  r,-r);
		glTexCoord2f(cx, cz); glVertex3f(1.0f, -r,-r);
	glEnd();
 
	// Common Axis Y - Draw Up side
	glBindTexture(GL_TEXTURE_2D,m_texture4);
	glBegin(GL_QUADS);		
		glTexCoord2f(cz, cz); glVertex3f( r, -r,1.0f);
		glTexCoord2f(cx, cz); glVertex3f( r,  r,1.0f); 
		glTexCoord2f(cx, cx); glVertex3f(-r,  r,1.0f);
		glTexCoord2f(cz, cx); glVertex3f(-r, -r,1.0f);
	glEnd();
 
	// Common Axis Y - Down side
	glBindTexture(GL_TEXTURE_2D,m_texture5);
	glBegin(GL_QUADS);		
		glTexCoord2f(cz,cz);  glVertex3f( r, -r,-1.0f);
		glTexCoord2f( cx,cz); glVertex3f( r,  r,-1.0f); 
		glTexCoord2f( cx,cx); glVertex3f(-r,  r,-1.0f);
		glTexCoord2f(cz, cx); glVertex3f(-r, -r,-1.0f);
	glEnd();
 
	// Load Saved Matrix
	glPopMatrix();



	//glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glCullFace(GL_BACK);
	glDisable(GL_TEXTURE_2D);



}