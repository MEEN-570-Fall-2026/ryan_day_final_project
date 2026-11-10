#include "VtkSceneRenderer.hpp"
#include "Point.hpp"
#include "SurfaceTriangle.hpp"
#include "Mesh.hpp"
#include "Point.hpp"
#include "TetrahedraCube.hpp"

VtkSceneRenderer::VtkSceneRenderer()
{
}

std::vector<vtkSmartPointer<vtkDataSet>> VtkSceneRenderer::render_scene() const
{
    std::vector<vtkSmartPointer<vtkDataSet>> sceneVector;
    for (const auto& sceneObject : sceneObjects)
    {
        renderObject3d(sceneObject.get(), sceneVector);
    }
    for (const auto& meshPtr : meshObjects)
    {
        if (meshPtr)
        {
            sceneVector.push_back(convert_mesh(*meshPtr));
        }
    }
    return sceneVector;
}

void VtkSceneRenderer::add_objects(const std::vector<RuntimeValue> &args)
{
    for (auto arg : args)
    {
        if (arg.is<RuntimeValue::CADObjectPointer>())
        {
            auto retrieved = arg.as<RuntimeValue::CADObjectPointer>();
            auto storedObject = std::dynamic_pointer_cast<Object3d>(retrieved);
            if (storedObject)
            {
                sceneObjects.push_back(storedObject);
            }
        }
        else if (arg.is<RuntimeValue::MeshPointer>())
        {
            auto retrieved = arg.as<RuntimeValue::MeshPointer>();
            meshObjects.push_back(retrieved);
        }
    }
}

void VtkSceneRenderer::renderObject3d(Object3d* sceneObject, std::vector<vtkSmartPointer<vtkDataSet>>& sceneVector) const
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

vtkSmartPointer<vtkUnstructuredGrid> VtkSceneRenderer::convert_mesh(const Mesh& mesh) const
{
    auto grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
    vtkNew<vtkPoints> vtkPoints;
    std::unordered_map<const Point*, vtkIdType> pointIds;
    for (const auto& point : mesh.get_point_cloud())
    {
        const vtkIdType id =
            vtkPoints->InsertNextPoint(point->x(), point->y(), point->z());
        pointIds.emplace(point.get(), id);
    }
    grid->SetPoints(vtkPoints);
    for (const auto& cube : mesh.get_tetrahedra_cubes())
    {
        for (const auto& tet : cube->get_tetrahedra())
        {
            const auto tetPoints = tet.get_vertices();
            vtkIdType ids[4];
            for (int i = 0; i < 4; ++i)
            {
                ids[i] = pointIds.at(tetPoints[i].get());
            }
            grid->InsertNextCell(VTK_TETRA, 4, ids);
        }
    }
    return grid;
}

