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
#include <vtkUnstructuredGrid.h>
#include <vtkDataSetMapper.h>

class VtkSceneRenderer : public ViewerAPI {
public:
    VtkSceneRenderer();
    std::vector<vtkSmartPointer<vtkDataSet>> render_scene() const;


private:
    std::vector<std::shared_ptr<Object3d>> sceneObjects;
    std::vector<std::shared_ptr<Mesh>> meshObjects;
    void add_objects(const std::vector<RuntimeValue>& args) override;
    void renderObject3d(Object3d* sceneObject, std::vector<vtkSmartPointer<vtkDataSet>>& sceneVector) const;
    vtkSmartPointer<vtkUnstructuredGrid> convert_mesh(const Mesh& mesh) const;
};

#endif