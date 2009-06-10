#include "GUI.h"


GUI::GUI(){
	m_frameRate = 0;
	m_startTime = 0;
	m_currentTime = 0;
	m_frameCount = 0;

	m_width = 0;
	m_height = 0;
	glfwGetWindowSize(&m_width, &m_height);

	m_text = new FTTextureFont("../../ProcTerrain/Data/verdana.ttf");
	m_text->FaceSize(11);





}

GUI::~GUI(){
	delete m_text;
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
	RenderPolyCount();

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
	m_text->Render(ss.str().c_str(), -1, FTPoint(m_width-200, m_height-100, 0));
	

	m_frameCount++;

}

void GUI::RenderPolyCount(){
	
	//TODO: clean this up
	stringstream ss1;
	ss1 << "Quads: " << "10";
	m_text->Render(ss1.str().c_str(), -1, FTPoint(m_width-200, m_height-115, 0));
	
	stringstream ss2;
	ss2 << "Tri: " << "20";
	m_text->Render(ss2.str().c_str(), -1, FTPoint(m_width-200, m_height-130, 0));

	stringstream ss3;
	ss3 << "Vertices: " << "10";
	m_text->Render(ss3.str().c_str(), -1, FTPoint(m_width-200, m_height-145, 0));

}