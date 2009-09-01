#ifndef GLCANVAS_H
#define GLCANVAS_H

#include "GL/glew.h"
#include <QGLWidget>
#include "WindowMng.h"
#include "ProcTerrain/TerrainMng.h"
#include "ProcCity/CityMng.h"

class GLCanvas : public QGLWidget
{
public:
	GLCanvas( QWidget* parent );
	GLCanvas();

	~GLCanvas();
	void initializeGL();
	void paintGL();
	void resizeGL();

private:
	WindowMng m_window;
	TerrainMng* m_terrain;


	

};

#endif
