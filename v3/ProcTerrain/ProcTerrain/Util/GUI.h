#ifndef GUI_H
#define GUI_H

#include "GL/glfw.h"
#include <FTGL/ftgl.h>
#include <sstream>
#include <string>
using namespace std;


class GUI{

private:

	FTTextureFont* m_text;
	int m_width;
	int m_height;
	int m_frameCount;
	double m_startTime;
	double m_currentTime;
	double m_frameRate;
	


public:

	GUI();
	~GUI();
	void Render();
	void RenderFPS();
	void RenderPolyCount();
	void RenderInfo();
	
	

};

#endif