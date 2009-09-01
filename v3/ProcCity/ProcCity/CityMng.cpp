#include "CityMng.h"
#include "voro++.cc"


CityMng::CityMng()
{


	//Init glew
	int err=glewInit();
	if(err!=GLEW_OK)
	{
		//exit();
	}

	//m_sceneGraph = new Node(Vector3<float>(0, 0, 0));
	
	m_gui = new GUI();
	m_translation = Vector3<float>(0,0,0);
	m_size = 0;

	m_parentNode = new Node();


	//Light
	initLight();

	//Nodes
	initNodes();
}

double rnd() {return double(rand())/RAND_MAX;}

void CityMng::initNodes(){
	
	
	const double x_min=-100,x_max=100;
	const double y_min=-100,y_max=100;
	const double z_min=-1,z_max=1;

	const int particles=20;

	const int n_x=1,n_y=1,n_z=1;

	container* con = new container(x_min,x_max,y_min,y_max,z_min,z_max,n_x,n_y,n_z,true,true,true,8);


	int i;
	double x,y,z;
	for(i=0;i<particles;i++) {
		x=x_min+rnd()*(x_max-x_min);
		y=y_min+rnd()*(y_max-y_min);
		z=0;
		con->put(i,x,y,z);
	}
	//con->print_facet_information();
	//con->draw_cells_gnuplot("gnuplot.dat");

	
	for(int i=0; i<particles; i++){
		CellInfo* cellInfo = con->get_cell_vertices(i);
		
		CellNode* cellNode = new CellNode();
		cellNode->SetVertices(cellInfo->size, cellInfo->vertices, cellInfo->center);

		m_parentNode->AddNode(cellNode);

		/*
		for(int j=0; j<cellInfo->size; i+=6){
			
			Segment<double>* segment = new Segment<double>(cellInfo->vertices[i], cellInfo->vertices[i+1], cellInfo->vertices[i+2],
														   cellInfo->vertices[i+3], cellInfo->vertices[i+4], cellInfo->vertices[i+5]);
			
		}
		*/
	}
}


void CityMng::Update(Vector3<float> currentPosition){
	
	m_parentNode->Update();
}

void CityMng::Render(double elapsedTime){
	
	m_parentNode->Render();
	
}

void CityMng::initLight(){
	
	GLfloat LightPosition[] = { 2.0, 2.0, 1.0, 1.0};

	GLfloat DiffuseLight[] = {1.0, 1.0, 1.0};
	GLfloat AmbientLight[] = {0.2, 0.2, 0.2};
	GLfloat SpecularLight[] = {1.0, 1.0, 1.0};

	glLightfv (GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv (GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv (GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	GLfloat mShininess[] = {8};

	GLfloat DiffuseMaterial[] = {1.0, 1.0, 1.0};
	GLfloat AmbientMaterial[] = {0.2, 0.2, 0.2};
	GLfloat SpecularMaterial[] = {1.0, 1.0, 1.0};

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, DiffuseMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, AmbientMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess); 


}