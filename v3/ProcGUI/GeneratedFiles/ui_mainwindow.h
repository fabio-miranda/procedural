/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Tue 1. Sep 00:17:36 2009
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTabWidget>
#include <QtGui/QWidget>
#include "GLCanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionWireframe;
    GLCanvas *canvas;
    QTabWidget *Select;
    QWidget *Terrain;
    QGroupBox *terrainParametersBox;
    QLabel *seed;
    QLabel *neighbours;
    QLabel *fboSize;
    QLineEdit *seedBox;
    QLineEdit *neighboursBox;
    QLineEdit *fboSizeBox;
    QPushButton *generateTerrain;
    QGroupBox *renderingOptionsBox;
    QCheckBox *Wireframe;
    QCheckBox *blendTexture;
    QCheckBox *heightMap;
    QCheckBox *light;
    QCheckBox *verticesDisplacement;
    QGroupBox *gpuCPUBox;
    QSlider *alfaSlider;
    QLabel *alfaLabel;
    QLabel *alfaLabel_2;
    QSlider *alfaSlider_2;
    QWidget *City;
    QGroupBox *cityParametersBox;
    QLabel *citySeedLabel;
    QLabel *voronoiCellsLabel;
    QLineEdit *seedCity;
    QLineEdit *numVoronoiCells;
    QPushButton *generateCity;

    void setupUi(QWidget *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(1024, 768);
        actionWireframe = new QAction(MainWindowClass);
        actionWireframe->setObjectName(QString::fromUtf8("actionWireframe"));
        canvas = new GLCanvas(MainWindowClass);
        canvas->setObjectName(QString::fromUtf8("canvas"));
        canvas->setGeometry(QRect(190, 0, 831, 768));
        canvas->setFocusPolicy(Qt::StrongFocus);
        Select = new QTabWidget(MainWindowClass);
        Select->setObjectName(QString::fromUtf8("Select"));
        Select->setGeometry(QRect(10, 10, 171, 621));
        Terrain = new QWidget();
        Terrain->setObjectName(QString::fromUtf8("Terrain"));
        terrainParametersBox = new QGroupBox(Terrain);
        terrainParametersBox->setObjectName(QString::fromUtf8("terrainParametersBox"));
        terrainParametersBox->setGeometry(QRect(10, 10, 151, 201));
        seed = new QLabel(terrainParametersBox);
        seed->setObjectName(QString::fromUtf8("seed"));
        seed->setGeometry(QRect(20, 20, 71, 16));
        neighbours = new QLabel(terrainParametersBox);
        neighbours->setObjectName(QString::fromUtf8("neighbours"));
        neighbours->setGeometry(QRect(20, 70, 111, 16));
        fboSize = new QLabel(terrainParametersBox);
        fboSize->setObjectName(QString::fromUtf8("fboSize"));
        fboSize->setGeometry(QRect(20, 120, 61, 16));
        seedBox = new QLineEdit(terrainParametersBox);
        seedBox->setObjectName(QString::fromUtf8("seedBox"));
        seedBox->setGeometry(QRect(20, 40, 113, 20));
        neighboursBox = new QLineEdit(terrainParametersBox);
        neighboursBox->setObjectName(QString::fromUtf8("neighboursBox"));
        neighboursBox->setGeometry(QRect(20, 90, 113, 20));
        fboSizeBox = new QLineEdit(terrainParametersBox);
        fboSizeBox->setObjectName(QString::fromUtf8("fboSizeBox"));
        fboSizeBox->setGeometry(QRect(20, 140, 113, 20));
        generateTerrain = new QPushButton(terrainParametersBox);
        generateTerrain->setObjectName(QString::fromUtf8("generateTerrain"));
        generateTerrain->setGeometry(QRect(30, 170, 75, 23));
        renderingOptionsBox = new QGroupBox(Terrain);
        renderingOptionsBox->setObjectName(QString::fromUtf8("renderingOptionsBox"));
        renderingOptionsBox->setGeometry(QRect(10, 430, 151, 141));
        Wireframe = new QCheckBox(renderingOptionsBox);
        Wireframe->setObjectName(QString::fromUtf8("Wireframe"));
        Wireframe->setGeometry(QRect(20, 20, 81, 18));
        blendTexture = new QCheckBox(renderingOptionsBox);
        blendTexture->setObjectName(QString::fromUtf8("blendTexture"));
        blendTexture->setGeometry(QRect(20, 40, 121, 18));
        heightMap = new QCheckBox(renderingOptionsBox);
        heightMap->setObjectName(QString::fromUtf8("heightMap"));
        heightMap->setGeometry(QRect(20, 80, 111, 18));
        light = new QCheckBox(renderingOptionsBox);
        light->setObjectName(QString::fromUtf8("light"));
        light->setGeometry(QRect(20, 60, 72, 18));
        verticesDisplacement = new QCheckBox(renderingOptionsBox);
        verticesDisplacement->setObjectName(QString::fromUtf8("verticesDisplacement"));
        verticesDisplacement->setGeometry(QRect(20, 100, 131, 18));
        gpuCPUBox = new QGroupBox(Terrain);
        gpuCPUBox->setObjectName(QString::fromUtf8("gpuCPUBox"));
        gpuCPUBox->setGeometry(QRect(10, 220, 151, 201));
        alfaSlider = new QSlider(gpuCPUBox);
        alfaSlider->setObjectName(QString::fromUtf8("alfaSlider"));
        alfaSlider->setGeometry(QRect(20, 70, 111, 21));
        alfaSlider->setMaximum(100);
        alfaSlider->setOrientation(Qt::Horizontal);
        alfaLabel = new QLabel(gpuCPUBox);
        alfaLabel->setObjectName(QString::fromUtf8("alfaLabel"));
        alfaLabel->setGeometry(QRect(10, 10, 151, 61));
        alfaLabel_2 = new QLabel(gpuCPUBox);
        alfaLabel_2->setObjectName(QString::fromUtf8("alfaLabel_2"));
        alfaLabel_2->setGeometry(QRect(10, 100, 151, 61));
        alfaSlider_2 = new QSlider(gpuCPUBox);
        alfaSlider_2->setObjectName(QString::fromUtf8("alfaSlider_2"));
        alfaSlider_2->setGeometry(QRect(20, 160, 111, 21));
        alfaSlider_2->setMaximum(10);
        alfaSlider_2->setOrientation(Qt::Horizontal);
        Select->addTab(Terrain, QString());
        City = new QWidget();
        City->setObjectName(QString::fromUtf8("City"));
        cityParametersBox = new QGroupBox(City);
        cityParametersBox->setObjectName(QString::fromUtf8("cityParametersBox"));
        cityParametersBox->setGeometry(QRect(10, 10, 151, 161));
        citySeedLabel = new QLabel(cityParametersBox);
        citySeedLabel->setObjectName(QString::fromUtf8("citySeedLabel"));
        citySeedLabel->setGeometry(QRect(20, 20, 51, 16));
        voronoiCellsLabel = new QLabel(cityParametersBox);
        voronoiCellsLabel->setObjectName(QString::fromUtf8("voronoiCellsLabel"));
        voronoiCellsLabel->setGeometry(QRect(20, 70, 121, 16));
        seedCity = new QLineEdit(cityParametersBox);
        seedCity->setObjectName(QString::fromUtf8("seedCity"));
        seedCity->setGeometry(QRect(20, 40, 113, 20));
        numVoronoiCells = new QLineEdit(cityParametersBox);
        numVoronoiCells->setObjectName(QString::fromUtf8("numVoronoiCells"));
        numVoronoiCells->setGeometry(QRect(20, 90, 113, 20));
        generateCity = new QPushButton(cityParametersBox);
        generateCity->setObjectName(QString::fromUtf8("generateCity"));
        generateCity->setGeometry(QRect(30, 120, 75, 23));
        Select->addTab(City, QString());

        retranslateUi(MainWindowClass);
        QObject::connect(Wireframe, SIGNAL(toggled(bool)), actionWireframe, SLOT(toggle()));

        Select->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Procedural", 0, QApplication::UnicodeUTF8));
        actionWireframe->setText(QApplication::translate("MainWindowClass", "Wireframe", 0, QApplication::UnicodeUTF8));
        terrainParametersBox->setTitle(QApplication::translate("MainWindowClass", "Procedural parameters", 0, QApplication::UnicodeUTF8));
        seed->setText(QApplication::translate("MainWindowClass", "Terrain Seed:", 0, QApplication::UnicodeUTF8));
        neighbours->setText(QApplication::translate("MainWindowClass", "Number of neighbours:", 0, QApplication::UnicodeUTF8));
        fboSize->setText(QApplication::translate("MainWindowClass", "FBO size:", 0, QApplication::UnicodeUTF8));
        generateTerrain->setText(QApplication::translate("MainWindowClass", "Generate", 0, QApplication::UnicodeUTF8));
        renderingOptionsBox->setTitle(QApplication::translate("MainWindowClass", "Rendering options", 0, QApplication::UnicodeUTF8));
        Wireframe->setText(QApplication::translate("MainWindowClass", "Wire frame", 0, QApplication::UnicodeUTF8));
        blendTexture->setText(QApplication::translate("MainWindowClass", "Blend texture", 0, QApplication::UnicodeUTF8));
        heightMap->setText(QApplication::translate("MainWindowClass", "Heightmap", 0, QApplication::UnicodeUTF8));
        light->setText(QApplication::translate("MainWindowClass", "Light", 0, QApplication::UnicodeUTF8));
        verticesDisplacement->setText(QApplication::translate("MainWindowClass", "Vertices displacement", 0, QApplication::UnicodeUTF8));
        gpuCPUBox->setTitle(QApplication::translate("MainWindowClass", "GPU/CPU", 0, QApplication::UnicodeUTF8));
        alfaLabel->setText(QApplication::translate("MainWindowClass", "% of the procedural\n"
" generation occuring\n"
" on the GPU:", 0, QApplication::UnicodeUTF8));
        alfaLabel_2->setText(QApplication::translate("MainWindowClass", "Numbers of\n"
"threads on the CPU:", 0, QApplication::UnicodeUTF8));
        Select->setTabText(Select->indexOf(Terrain), QApplication::translate("MainWindowClass", "Terrain", 0, QApplication::UnicodeUTF8));
        cityParametersBox->setTitle(QApplication::translate("MainWindowClass", "Procedural parameters", 0, QApplication::UnicodeUTF8));
        citySeedLabel->setText(QApplication::translate("MainWindowClass", "City Seed:", 0, QApplication::UnicodeUTF8));
        voronoiCellsLabel->setText(QApplication::translate("MainWindowClass", "Number of voronoi cells:", 0, QApplication::UnicodeUTF8));
        generateCity->setText(QApplication::translate("MainWindowClass", "Generate", 0, QApplication::UnicodeUTF8));
        Select->setTabText(Select->indexOf(City), QApplication::translate("MainWindowClass", "City", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindowClass);
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
