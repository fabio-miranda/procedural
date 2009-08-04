#ifndef WINDOWMNG_H
#define WINDOWMNG_H



//#include "GL/glew.h"
#include "GL/glfw.h"
#include "Camera.h"
#include "ProcTerrain/Config.h"
#include <FTGL/ftgl.h>



class WindowMng{

	int m_width;
	int m_height;
	Camera* m_camera;
	bool m_pressingKey;

public:
	WindowMng(int, int);
	void GLInit();
	void GLConfig();
	void UpdateKeyboard();
	void UpdateMouse();
	Vector3<float> GetCameraPosition();
	bool isRunning();
	void keyboardCallback(int key, int action);
};

#endif