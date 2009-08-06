#ifndef GUI_H
#define GUI_H

#include "GL/glfw.h"
#include <FTGL/ftgl.h>
#include <sstream>
#include <string>
#include <list>
using namespace std;


class GUI{

private:

	FTTextureFont* m_text;
	int m_width;
	int m_height;
	int m_frameCount;
	double m_startTime;
	double m_lastTime;
	double m_currentTime;
	double m_frameRate;
	int m_framesToCount;
	int m_cont;
	double m_avgRenderTime;

	list<double> m_listRenderTimes;
	


public:

	GUI();
	~GUI();
	void Render();
	void RenderFPS();
	void RenderPolyCount();
	void RenderInfo();
	
	

};

#endif