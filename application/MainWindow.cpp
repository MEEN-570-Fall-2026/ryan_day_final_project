#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkExtractEdges.h>
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
  ui->consoleLog->setReadOnly(true);
  logger = std::make_unique<ConsoleLogger>(*ui->consoleLog);

  mQVtkWidget = new QVTKOpenGLNativeWidget(ui->viewerFrame);
  mQVtkWidget->setEnableTouchEventProcessing(false);

  auto* layout = new QGridLayout(ui->viewerFrame);
  layout->setContentsMargins(0, 0, 0, 0);
  layout->addWidget(mQVtkWidget);

  setup_menu_bar();
  setup_connections();

  logger->log("Launched FeCad!");
}

MainWindow::~MainWindow()
{
  delete ui;
  delete context;
}

void MainWindow::setup_vtk_pipeline(VtkSceneRenderer* viewer)
{
    auto sceneData = viewer->render_scene();
    if (!sceneData.empty())
    {
        logger->log(std::format(
            "Viewer displaying {} objects!", sceneData.size()));
    }
    auto window = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    window->AddRenderer(mRenderer);
    for (const auto& scene : sceneData)
    {
        auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
        mapper->SetInputData(scene);
        auto actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        if (auto* grid = vtkUnstructuredGrid::SafeDownCast(scene.GetPointer()))
        {
          auto edges = vtkSmartPointer<vtkExtractEdges>::New();
          edges->SetInputData(grid);

          auto edgeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
          edgeMapper->SetInputConnection(edges->GetOutputPort());

          auto edgeActor = vtkSmartPointer<vtkActor>::New();
          edgeActor->SetMapper(edgeMapper);
          edgeActor->GetProperty()->SetColor(1.0, 1.0, 1.0);
          edgeActor->GetProperty()->SetLineWidth(1.0);

          mRenderer->AddActor(edgeActor);
        }
        else
        {
          auto mapper = vtkSmartPointer<vtkDataSetMapper>::New();
          mapper->SetInputData(scene);

          auto actor = vtkSmartPointer<vtkActor>::New();
          actor->SetMapper(mapper);
          mRenderer->AddActor(actor);
        }
        mRenderer->AddActor(actor);
        actor->GetProperty()->SetOpacity(0.5);
    }
    mQVtkWidget->setRenderWindow(window);
    mRenderer->ResetCamera();
    window->Render();
}

void MainWindow::setup_menu_bar()
{
  auto* fileMenu = menuBar()->addMenu("File");
  auto* sampleCodeMenu = menuBar()->addMenu("Sample Code");
  auto* basicCubeSampleAction = sampleCodeMenu->addAction("Basic Cubes");
  connect(basicCubeSampleAction, &QAction::triggered, this, [this] {open_sample(QStringLiteral("BasicCubes.fecad"));});
  auto* simpleMeshingSampleAction = sampleCodeMenu->addAction("Basic Meshing");
  connect(simpleMeshingSampleAction, &QAction::triggered, this, [this] {open_sample(QStringLiteral("BasicMeshing.fecad"));});
  auto* openAction = fileMenu->addAction("Open");
  connect(openAction, &QAction::triggered, this, &MainWindow::open_file);
  auto* newFileAction = fileMenu->addAction("New");
  connect(newFileAction, &QAction::triggered, this, &MainWindow::new_file);
  auto* saveFileAction = fileMenu->addAction("Save");
  connect(saveFileAction, &QAction::triggered, this, &MainWindow::save_file);
  auto* saveAsFileAction = fileMenu->addAction("Save As");
  connect(saveAsFileAction, &QAction::triggered, this, &MainWindow::save_as);
}

void MainWindow::setup_connections()
{
  connect(ui->runCodeButton, &QPushButton::clicked, this, &MainWindow::run_code);
  connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::save_file);
}

void MainWindow::open_sample(const QString& filename)
{
  const QString filepath = QDir(QCoreApplication::applicationDirPath()).filePath("SampleFiles/" + filename);
  openedFile.clear();
  display_file(filepath);
  logger->log("Opened sample " + filename.toStdString());
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
  logger->log("Opened File " + filePath.toStdString());
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
  logger->log("Created new file!");
}

void MainWindow::run_code()
{
  delete context;
  context = new Context(std::make_shared<VtkSceneRenderer>(), std::make_shared<Mesher>());
  interpreter = Interpreter(context);
  try {
    std::string text = ui->codeEditor->toPlainText().toStdString();
    logger->log("Parsing code...");
    auto parseTrees = parser.parse_from_string(text);
    logger->log("Interpreting code...");
    interpreter.interpret_trees(parseTrees);
    RuntimeValue viewerRuntime = context->get("Viewer");
    auto viewerAPI = viewerRuntime.as<RuntimeValue::ViewerAPIPointer>();
    VtkSceneRenderer* viewer = std::dynamic_pointer_cast<VtkSceneRenderer>(viewerAPI).get();
    setup_vtk_pipeline(viewer);
    logger->log("Done!");
  }
  catch (const std::exception& e) {
    logger->logError(e);
  }
}

void MainWindow::save_as()
{
  openedFile = QFileDialog::getSaveFileName(this, tr("Save As"), QString{}, tr("FeCAD files (*.fecad)"));
  if (openedFile.isEmpty())
  {
    logger->log("No output file selectd. Failed to save as.");
    return;
  }
  save_file();
}

void MainWindow::save_file()
{
  if (openedFile.isEmpty())
  {
    save_as();
    return;
  }
  std::ofstream outputFile{openedFile.toStdString()};
  if (!outputFile)
  {
    logger->log("Failed to save. Could not open file: " + openedFile.toStdString());
    return;
  }
  std::string codeText = ui->codeEditor->toPlainText().toStdString();
  outputFile << codeText;
  outputFile.close();
  logger->log("Saved to " + openedFile.toStdString());
}
