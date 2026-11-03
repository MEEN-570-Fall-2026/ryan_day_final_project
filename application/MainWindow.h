#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>
#include <vtkSmartPointer.h>
#include <vtkConeSource.h>
#include <QGridLayout>

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
  void setup_vtk_pipeline();
  void setup_menu_bar();
  void setup_connections();
  void open_sample(const QString& filename);
  void open_file();
  void display_file(QString filename);
  void new_file();
  Ui::MainWindow *ui;
  QVTKOpenGLNativeWidget* mQVtkWidget;

  vtkSmartPointer<vtkPolyData> mConeSource;
  vtkSmartPointer<vtkRenderer> mRenderer;
  QString openedFile;
};

#endif // MAINWINDOW_H
