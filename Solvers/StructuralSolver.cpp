#include "StructuralSolver.hpp"

StructuralSolver::StructuralSolver(Mesher mesher) : Solver{mesher}
{
    for (std::shared_ptr<Mesh> meshPtr : mesher.get_meshes()) {
        meshLoads[meshPtr] = std::vector<PointLoad>();
    }
}

void StructuralSolver::add_load_to_mesh(std::shared_ptr<Mesh> meshSharedPtr, PointLoad& load)
{
    meshLoads[meshSharedPtr].push_back(load);
}

std::vector<PointLoad> StructuralSolver::get_loads_from_mesh(std::shared_ptr<Mesh> meshSharedPtr)
{
    return meshLoads[meshSharedPtr];
}
