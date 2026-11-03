#ifndef VTKSCENERENDERER
#define VTKSCENERENDERER

#include "primitives3d/Object3d.hpp"
#include "ViewerAPI.hpp"
#include <vector>
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkNew.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>

class VtkSceneRenderer : public ViewerAPI {
public:
    VtkSceneRenderer();
    std::vector<vtkSmartPointer<vtkPolyData>> render_scene() const;


private:
    std::vector<Object3d*> sceneObjects;
    void add_objects(const std::vector<RuntimeValue>& args);
};

#endif