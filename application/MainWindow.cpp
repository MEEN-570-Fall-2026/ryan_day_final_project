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
  mConeSource = vtkSmartPointer<vtkConeSource>::New();
  mConeSource->SetHeight(3.0);
  mConeSource->SetRadius(1.0);
  mConeSource->SetResolution(50);

  vtkSmartPointer<vtkPolyDataMapper> mapper =vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(mConeSource->GetOutputPort());

  vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  mRenderer = vtkSmartPointer<vtkRenderer>::New();
  mRenderer->AddActor(actor);


  vtkSmartPointer<vtkGenericOpenGLRenderWindow> window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
  window->AddRenderer(mRenderer);

  mQVtkWidget->setRenderWindow(window);

  mRenderer->ResetCamera();
}

