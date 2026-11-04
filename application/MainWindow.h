#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <QGridLayout>
#include "Parser.hpp"
#include "Interpreter.hpp"
#include "Context.hpp"
#include "VtkSceneRenderer.hpp"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  void setup_vtk_pipeline(VtkSceneRenderer* viewer);
  void setup_menu_bar();
  void setup_connections();
  void open_sample(const QString& filename);
  void open_file();
  void display_file(QString filename);
  void new_file();
  void run_code();
  Ui::MainWindow* ui;
  QVTKOpenGLNativeWidget* mQVtkWidget;

  vtkSmartPointer<vtkPolyData> mConeSource;
  vtkSmartPointer<vtkRenderer> mRenderer;
  QString openedFile;

  Parser parser;
  Context* context = new Context{std::make_shared<VtkSceneRenderer>()};
  Interpreter interpreter{context};
};

#endif // MAINWINDOW_H
