// POC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "POC.h"
#include "FileHeightmap.h"
#include "FaultFormation.h"
#include "FractalTerrain.h"
#include "Heightmask.h"
#include "Framework.h"
#include "Random.h"
#include "Vector3.h"

POC::POC(int p_width, int p_height) : Framework(p_width, p_height)
{

}


void POC::Init(){
	Framework::Init();
	Random::Init();

	//Temp
	/*
	FileHeightmap* aux = new FileHeightmap(1, Vector3<float>(0,0,0), 257, 257, "../POC/Content/Heightmaps/3.bmp");
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	/*
	Heightmask* mask = new Heightmask("../POC/Content/Heightmaps/mascara.bmp");
	aux->SetHeightMask(*mask);
	
	
	Random::Init();

	FaultFormation* aux = new FaultFormation(16, Vector3<float>(0,0,0), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/

	/*
	aux = new FaultFormation(16, Vector3<float>(512,0,512), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);

	aux = new FaultFormation(16, Vector3<float>(0,0,512), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	/*
	Random::Init();
	FaultFormation* aux = new FaultFormation(16, Vector3<float>(0,0,0), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	aux->m_mesh->CopyVertexFromHeightMap();
	aux->m_mesh->BuildVBOs();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	
	/*
	FractalTerrain* aux = new FractalTerrain(1, Vector3<float>(0,0,0), 100, 100, 31, 8, 0.5);
	aux->FillHeightMap();
	//aux->Normalize(255, 0);
	aux->m_mesh->CopyVertexFromHeightMap();
	aux->m_mesh->BuildVBOs();
	//aux->SetShader();
	m_sceneGraph.insert(m_sceneGraph.end(), aux);
	*/
	/*

	FractalTerrain* aux;
	int tamanho_terreno = 100;
	int num_terrenos_x = 1;
	int num_terrenos_y = 1;
	
	for(int i=0; i<num_terrenos_x * tamanho_terreno; i+=tamanho_terreno){
		for(int j=0; j<num_terrenos_y * tamanho_terreno; j+=tamanho_terreno){
			aux = new FractalTerrain(1, Vector3<float>(0,0,0), tamanho_terreno, tamanho_terreno, 13, 1, 0.5);
			aux->FillHeightMap();
			aux->m_mesh->CopyVertexFromHeightMap();
			aux->m_mesh->BuildVBOs();
			//aux->SetShader();
			aux->GenerateNeighbours(NULL);
			//m_sceneGraph.insert(m_sceneGraph.end(), aux);
			
			
			cout << "&aux->m_children: ";
			cout << &(aux->m_children);
			cout << " aux: ";
			cout << &(*aux);
			cout << " &aux: ";
			cout << &(aux);
			cout << " Size: ";
			cout << aux->m_children.size();
			cout << "\n";

			//cout << " tamanho_terreno: ";
			//cout << tamanho_terreno;
			//cout << " &tamanho_terreno: ";
			//cout << &tamanho_terreno;
			//cout << "\n";
			
			cout << "&m_sceneGraph[0]->m_children: ";
			cout << &(m_sceneGraph[0]->m_children);
			cout << " m_sceneGraph[0]: ";
			cout << &(*m_sceneGraph[0]);
			cout << " &m_sceneGraph[0]: ";
			cout << &(m_sceneGraph[0]);
			cout << " Size: ";
			cout << m_sceneGraph[0]->m_children.size();
			cout << "\n";
			
			m_currentNode = aux;

		}
	}
	*/

	
	
	/*
	FaultFormation* aux;
	aux = new FaultFormation(16, Vector3<float>(0,0,0), 512, 512, 16, 64, 8, 2, 0.5f);
	aux->FillHeightMap();
	aux->m_mesh->CopyVertexFromHeightMap();
	aux->m_mesh->BuildVBOs();
	*/
	/*
	FileHeightmap* file = new FileHeightmap(1, Vector3<float>(0.5,0.5,0.5), Vector3<float>(0,100,0), 100, 100, "../POC/Content/Heightmaps/3.bmp");
	file->FillHeightMap();
	file->m_mesh->CopyVertexFromHeightMap();
	file->m_mesh->BuildVBOs();

	perlin->InsertNode(file);
	*/
	//Redirect output
	
	freopen( "tests3.csv", "w", stdout );

	double time = 0;
	double total = 0;
	FractalTerrain* perlin;
	cout << "Size=100x100, Seed: 343, Octaves: 32";
	cout << "\n";
	cout << "FillHeightMap(); CopyVertexFromHeightMap(); BuildVBOs(); Total;";
	cout << "\n";
	for(int i=0; i<1; i++){
		

		
		perlin = new FractalTerrain(1, Vector3<float>(1.0,1.0,1.0), Vector3<float>(0,0,0), 25, 25, 13, 3, 0.5);


		time = glfwGetTime();
		total = time;
		perlin->FillHeightMap();
		time = glfwGetTime() - time;
		cout << time;
		cout << "; ";

		
		time = glfwGetTime();
		perlin->m_mesh->CopyVertexFromHeightMap();
		time = glfwGetTime() - time;
		cout << time;
		cout << "; ";
		
	
		time = glfwGetTime();
		perlin->m_mesh->BuildVBOs();
		time = glfwGetTime() - time;
		cout << time;
		cout << "; ";
		
		total = glfwGetTime() - total;
		cout << total;
		cout<< "; ";

		cout << "\n";

		//aux->SetShader();
		perlin->GenerateNeighbours(NULL);

		m_currentNode = perlin;


	}
	/*
	FileHeightmap* file = new FileHeightmap(1, Vector3<float>(0.5,0.5,0.5), Vector3<float>(200,100,200), 100, 100, "../POC/Content/Heightmaps/3.bmp");
	file->FillHeightMap();
	file->m_mesh->CopyVertexFromHeightMap();
	file->m_mesh->BuildVBOs();

	perlin->InsertNode(file);
	*/
	
	
	


}



