#ifndef VTKSCENERENDERER
#define VTKSCENERENDERER

#include "primitives3d/Object3d.hpp"
#include <vector>
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

class VtkSceneRenderer {
public:
    VtkSceneRenderer();
    void add_object(Object3d& object3d);
    std::vector<vtkSmartPointer<vtkPolyData>> render_scene() const;


private:
    std::vector<Object3d*> sceneObjects;
};

#endif