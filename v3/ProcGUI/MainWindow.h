#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	Ui::MainWindowClass ui;


public slots:
	void toggle();

private slots:

	//Procedutal terrains widgets
	void on_generateTerrain_triggered();
	void on_actionWireframe_toggled(bool checked);
	void on_actionBlendTexture_toggled();
	void on_actionLight_toggled();
	void on_actionHeightmap_toggled();
	void on_actionVerticesDisplacement_toggled();

	//Procedural city widgets
	void on_generateCity_triggered();
	
};

#endif // MAINWINDOW_H
