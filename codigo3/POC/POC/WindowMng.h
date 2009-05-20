#ifndef WINDOWMNG_H
#define WINDOWMNG_H



//#include "GL/glew.h"
#include "GL/glfw.h"
#include "Camera.h"



class WindowMng{

	int m_width;
	int m_height;
	Camera* m_camera;

public:
	WindowMng(int, int);
	void GLInit();
	void GLConfig();
	void UpdateCamera();
	Vector3<float> GetCameraPosition();
	bool isRunning();
};

#endif