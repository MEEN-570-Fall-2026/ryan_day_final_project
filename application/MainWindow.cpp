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
    Cube cube{2.0, 0.3, 2.0};
    VtkSceneRenderer sceneRenderer;
    sceneRenderer.add_object(cube);
    auto sceneData = sceneRenderer.render_scene();
    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(sceneData);
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    mRenderer->AddActor(actor);
    auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    window->AddRenderer(mRenderer);
    mQVtkWidget->setRenderWindow(window);
    mRenderer->ResetCamera();
}

