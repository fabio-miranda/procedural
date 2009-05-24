#include "GUI.h"


GUI::GUI(){
	m_frameRate = 0;
	m_startTime = 0;
	m_currentTime = 0;
	m_frameCount = 0;

	int width = 0;
	int height = 0;
	glfwGetWindowSize(&width, &height);
	m_position = FTPoint(width-200, height-100, 0);

	m_fps = new FTTextureFont("../../ProcTerrain/Data/verdana.ttf");
	
	m_fps->FaceSize(12);



}

GUI::~GUI(){
	delete m_fps;
}

void GUI::Render(){

	int width = 0;
	int height = 0;
	glfwGetWindowSize(&width, &height);

	glDisable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, (int)width, 0.0f, (int)height, 0.0f, 10.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	//Render fps
	RenderFPS();

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);

}

void GUI::RenderFPS(){
	m_currentTime = glfwGetTime();

	if(m_currentTime - m_startTime > 1){
		m_frameRate = m_frameCount / (m_currentTime - m_startTime);

		m_startTime = m_currentTime;
		m_frameCount = 0;


		
		

		
	}
	
	stringstream ss;
	ss << "FPS: " << m_frameRate;
	m_fps->Render(ss.str().c_str(), -1, m_position);
	

	m_frameCount++;

}