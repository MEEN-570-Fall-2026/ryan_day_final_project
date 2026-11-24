#include "Solver.hpp"

#include <memory>
#include "UnassignedMaterialException.hpp"

Solver::Solver(Mesher mesher)
{
    for (std::shared_ptr<Mesh> meshPtr : mesher.get_meshes()) {
        meshMaterials[meshPtr] = std::nullopt;
        meshConstraints[meshPtr] = std::vector<std::shared_ptr<PointConstraint>>();
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

void Solver::add_constraint_to_mesh(std::shared_ptr<Mesh> mesh, const PointConstraint& constraint)
{
    auto copy = constraint.clone();
    meshConstraints[mesh].push_back(std::shared_ptr<PointConstraint>(std::move(copy)));
}

std::vector<std::shared_ptr<PointConstraint>> Solver::get_mesh_constraints(std::shared_ptr<Mesh> meshSharedPtr)
{
    return meshConstraints[meshSharedPtr];
}

void Solver::allign_constraints()
{
    for (auto& [mesh, constraints] : meshConstraints)
    {
        for (int i = 0; i < constraints.size(); i++)
        {
            Point constraintLocation = constraints[i]->get_constraint_location();
            std::shared_ptr<Point> newLocation = mesh->get_closest_node(constraintLocation);
            constraints[i]->update_location(newLocation);
        }
    }
}
