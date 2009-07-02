// main.cpp : Defines the entry point for the console application.
//

#include "ProcTerrain/TerrainMng.h"
#include "ProcTerrain/Scene/SquareNode.h"
#include "WindowMng.h"
#include "Camera.h"


int main( int argc, char **argv ){
	
	//The WindowMng is responsable for opening and setting the window (something that the game would do, not the TerrainMng)
	WindowMng window = WindowMng(1280,720);
	window.GLInit();


	//Create the terrain
	TerrainMng* terrain = new TerrainMng();
	


	
	double currentTime = 0;
	double elapsedTime = 0;
	double oldTime = 0;
	while(window.isRunning()){
		currentTime = glfwGetTime();
		elapsedTime = currentTime - oldTime;
		oldTime = currentTime;

		window.GLConfig();
		window.UpdateKeyboard();
		window.UpdateMouse();
		
		
		//===The important stuff
		terrain->Update(window.GetCameraPosition());
		terrain->Render(elapsedTime);
		//===

		glfwSwapBuffers();

	}
}

