#include "Solver.hpp"

#include <memory>
#include "UnassignedMaterialException.hpp"

Solver::Solver(Mesher mesher)
{
    for (std::shared_ptr<Mesh> meshPtr : mesher.get_meshes()) {
        meshMaterials[meshPtr] = std::nullopt;
    }
}

void Solver::assign_material_to_mesh(std::shared_ptr<Mesh> meshSharedPtr, IsotropicMaterial& material)
{
    meshMaterials[meshSharedPtr] = material;
}

IsotropicMaterial Solver::get_mesh_material(std::shared_ptr<Mesh> meshSharedPtr)
{
    if (!meshMaterials[meshSharedPtr].has_value())
    {
        throw UnassignedMaterialException("No material assigned to requested mesh!");
    }
    return *meshMaterials[meshSharedPtr];
}
