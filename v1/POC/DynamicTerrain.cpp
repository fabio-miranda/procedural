#include "stdafx.h"
#include "DynamicTerrain.h"
#include "Heightmask.h"
#include "Vector3.h"
#include <IL/il.h>
#include <string>
#include <iostream>
using namespace std;



DynamicTerrain::DynamicTerrain(int renderStepSize, Vector3<float> color, Vector3<float> position, int width, int height) : Terrain(renderStepSize, color, position, width, height){


}

void DynamicTerrain::Render(bool wireFrame, int colorToRender){

	Terrain::Render(wireFrame,colorToRender);
}


