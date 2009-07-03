#include "stdafx.h"
#include "Menu.h"
#include "GL/glfw.h"
//#include "AntTweakBar.h"

Menu::Menu(){
	TwBar* bar = TwNewBar("Menu");

	float aux;

    //TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.


	TwAddVarRW(bar, "TerrainColor", TW_TYPE_COLOR3F, &aux, 
               " label='Terrain Color' group='Terrains'");

	TwAddVarRW(bar, "BgColor", TW_TYPE_COLOR3F, &aux, 
               " label='Background Color' group='Terrains'");

	TwAddVarRW(bar, "Neighbours", TW_TYPE_FLOAT, &aux, 
               " label='Neighbours' group='Terrains' min=0 max=1 step=0.001 keyIncr=a keyDecr=A help='Change scene ambient.' ");
	
	
	TwAddVarRW(bar, "Perlin Noise", TW_TYPE_FLOAT, &aux, 
               " label='Seed' group='FractalTerrain' min=0 max=1 step=0.001 keyIncr=a keyDecr=A help='Change scene ambient.' ");

	TwAddVarRW(bar, "Perlin Noise", TW_TYPE_FLOAT, &aux, 
               " label='Octaves' group='FractalTerrain' min=0 max=1 step=0.001 keyIncr=a keyDecr=A help='Change scene ambient.' ");



	
	//glfwSetMouseButtonCallback((GLFWmousebuttonfun)TwEventMouseButtonGLFW);
	//glfwSetMousePosCallback((GLFWmouseposfun)TwEventMousePosGLFW);
	//glfwSetMouseWheelCallback((GLFWmousewheelfun)TwEventMouseWheelGLFW);
	//glfwSetKeyCallback((GLFWkeyfun)TwEventKeyGLFW);
	//glfwSetCharCallback((GLFWcharfun)TwEventCharGLFW);

	



}
