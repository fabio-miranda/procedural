// main.cpp : Defines the entry point for the console application.
//

#include "TerrainMng.h"
#include "WindowMng.h"
#include "CubeSphere.h"
#include "Camera.h"


int main( int argc, char **argv ){
	
	//The WindowMng is responsable for opening and setting the window (something that the game would do, not the TerrainMng)
	WindowMng window = WindowMng(1280,720);
	window.GLInit();


	//Create the terrain
	TerrainMng terrain = TerrainMng();
	terrain.m_sceneGraph->AddNode(new CubeSphere(Vector3<float>(0,0,0),1.0f, 1));


	

	while(window.isRunning()){
		window.GLConfig();
		window.UpdateCamera();
		
		
		//===The important stuff
		terrain.Update();
		terrain.Render();
		//===

		glfwSwapBuffers();

	}
}

