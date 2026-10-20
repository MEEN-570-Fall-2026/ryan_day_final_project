#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkPolyDataMapper.h>
#include <QGridLayout>
#include "VtkSceneRenderer.hpp"
#include "primitives3d/Cube.hpp"
#include <iostream>
#include <vtkProperty.h>

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  mQVtkWidget = new QVTKOpenGLNativeWidget(ui->viewerFrame);

  auto* layout = new QGridLayout(ui->viewerFrame);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(mQVtkWidget);

  setup_vtk_pipeline();

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setup_vtk_pipeline()
{
    Cube cube{1, 1, 1};
    Point cube2Centroid{0.5, 0.5, 0.5};
    Cube cube2{cube2Centroid, 1, 1, 1};
    VtkSceneRenderer sceneRenderer;
    sceneRenderer.add_object(cube);
    sceneRenderer.add_object(cube2);
    auto sceneData = sceneRenderer.render_scene();
    auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    window->AddRenderer(mRenderer);
    for (const auto& scene : sceneData)
    {
        auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(scene);
        auto actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        mRenderer->AddActor(actor);
    }
    mQVtkWidget->setRenderWindow(window);
    mRenderer->ResetCamera();
}

