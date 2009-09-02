#include "GLCanvas.h"

GLCanvas::GLCanvas( QWidget *parent )
: QGLWidget(parent)
{
	m_window = WindowMng(1280,720);
	//m_terrainMng = new TerrainMng();
	m_cityMng = new CityMng();

}

GLCanvas::~GLCanvas()
{}

void GLCanvas::initializeGL()
{
	m_window.GLInit();
}

void GLCanvas::paintGL()
{
	m_window.GLConfig();
	m_window.UpdateKeyboard();
	m_window.UpdateMouse();

	m_cityMng->Update(m_window.GetCameraPosition());
	m_cityMng->Render(0);
}

void GLCanvas::resizeGL()
{
	paintGL();
}


