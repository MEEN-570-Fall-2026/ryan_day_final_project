#include "VtkSceneRenderer.hpp"
#include "Point.hpp"
#include "SurfaceTriangle.hpp"

VtkSceneRenderer::VtkSceneRenderer()
{
}

void VtkSceneRenderer::add_object(Object3d& object3d){
    sceneObjects.push_back(&object3d);
}

std::vector<vtkSmartPointer<vtkPolyData>> VtkSceneRenderer::render_scene() const
{
    std::vector<vtkSmartPointer<vtkPolyData>> sceneVector;
    for (Object3d* sceneObject : sceneObjects)
    {
        vtkNew<vtkPoints> vtkPoints;
        vtkNew<vtkCellArray> vtkTriangles;
        for (Point vertex : sceneObject->get_vertices())
        {
            vtkPoints->InsertNextPoint(vertex.x(), vertex.y(), vertex.z());
        }
        for (auto triangleIndices : sceneObject->getSurfaceTriangleIndices())
        {
            vtkTriangles->InsertNextCell(3);
            vtkTriangles->InsertCellPoint(static_cast<vtkIdType>(triangleIndices[0]));
            vtkTriangles->InsertCellPoint(static_cast<vtkIdType>(triangleIndices[1]));
            vtkTriangles->InsertCellPoint(static_cast<vtkIdType>(triangleIndices[2]));
        }
        auto polyData = vtkSmartPointer<vtkPolyData>::New();
        polyData->SetPoints(vtkPoints);
        polyData->SetPolys(vtkTriangles);
        sceneVector.push_back(polyData);
    }
    return sceneVector;
}
