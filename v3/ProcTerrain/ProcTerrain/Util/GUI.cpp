#include "GUI.h"


GUI::GUI(){
	m_frameRate = 0;
	m_startTime = 0;
	m_currentTime = 0;
	m_lastTime = 0;
	m_frameCount = 0;
	m_cont = 0;
	m_framesToCount = 500;
	m_avgRenderTime = 0;
	

	m_width = 0;
	m_height = 0;
	glfwGetWindowSize(&m_width, &m_height);

	m_text = new FTTextureFont("Data/verdana.ttf");
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

	//Render text
	glColor3f(1, 0.5, 0);
	RenderFPS();
	//RenderPolyCount();
	RenderInfo();

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
	
	
	
	
	if(m_listRenderTimes.size() < m_framesToCount){
		m_listRenderTimes.push_back((m_currentTime - m_lastTime));
	}
	else{
		m_listRenderTimes.pop_front();
		m_listRenderTimes.push_back((m_currentTime - m_lastTime));
	}
	m_lastTime = m_currentTime;
	m_cont++;

	m_avgRenderTime = 0;
	for (list<double>::iterator it = m_listRenderTimes.begin(); it != m_listRenderTimes.end(); it++){
		m_avgRenderTime += *it;
	}
	m_avgRenderTime = m_avgRenderTime / m_framesToCount;
		
	
	stringstream ss1;
	ss1 << "FPS: " << m_frameRate;
	m_text->Render(ss1.str().c_str(), -1, FTPoint(m_width-200, m_height-100, 0));
	
	stringstream ss2;
	ss2 << "Render time (avg): " << m_avgRenderTime;
	m_text->Render(ss2.str().c_str(), -1, FTPoint(m_width-200, m_height-115, 0));
	

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

void GUI::RenderInfo(){
	
	//TODO: clean this up
	stringstream ss1;
	ss1 << "Info: ";
	m_text->Render(ss1.str().c_str(), -1, FTPoint(m_width-200, m_height-600, 0));
	
	stringstream ss2;
	ss2 << "1: Wireframe";
	m_text->Render(ss2.str().c_str(), -1, FTPoint(m_width-200, m_height-615, 0));

	stringstream ss3;
	ss3 << "2: HeightMap";
	m_text->Render(ss3.str().c_str(), -1, FTPoint(m_width-200, m_height-630, 0));

	stringstream ss4;
	ss4 << "3: Vertices Displacement";
	m_text->Render(ss4.str().c_str(), -1, FTPoint(m_width-200, m_height-645, 0));

	stringstream ss5;
	ss5 << "4: Blend";
	m_text->Render(ss5.str().c_str(), -1, FTPoint(m_width-200, m_height-660, 0));

	stringstream ss6;
	ss6 << "5: Light";
	m_text->Render(ss6.str().c_str(), -1, FTPoint(m_width-200, m_height-675, 0));



}