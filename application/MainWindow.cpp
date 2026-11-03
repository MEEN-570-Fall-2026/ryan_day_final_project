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
#include <QFileDialog>
#include <fstream>
#include <QFile>
#include <QIODevice>
#include <QDebug>

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

  setup_menu_bar();
  setup_connections();

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

void MainWindow::setup_menu_bar()
{
  auto* fileMenu = menuBar()->addMenu("File");
  auto* sampleCodeMenu = menuBar()->addMenu("Sample Code");
  auto* basicCubeSampleAction = sampleCodeMenu->addAction("BasicCubes");
  connect(basicCubeSampleAction, &QAction::triggered, this, [this] {open_sample(QStringLiteral("BasicCubes.fecad"));});
  auto* openAction = fileMenu->addAction("Open");
  connect(openAction, &QAction::triggered, this, &MainWindow::open_file);
  auto* newFileAction = fileMenu->addAction("New");
  connect(newFileAction, &QAction::triggered, this, &MainWindow::new_file);
}

void MainWindow::setup_connections()
{
}

void MainWindow::open_sample(const QString& filename)
{
  const QString filepath = QDir(QCoreApplication::applicationDirPath()).filePath("SampleFiles/" + filename);
  openedFile.clear();
  display_file(filepath);
}

void MainWindow::open_file()
{
  const QString filePath = QFileDialog::getOpenFileName(this, tr("Open FeCAD file"), QString(), tr("FeCAD files (*.fecad)"));
  if (filePath.isEmpty())
  {
    return;
  }
  openedFile = filePath;
  display_file(filePath);
}


void MainWindow::display_file(QString filepath)
{
  QFile file(filepath);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qWarning() << "Could not open" << filepath << file.errorString();
      return;
  }

  const QString contents = QString::fromUtf8(file.readAll());
  ui->codeEditor->setPlainText(contents);
}

void MainWindow::new_file()
{
  ui->codeEditor->clear();
  openedFile.clear();
}
