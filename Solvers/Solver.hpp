#ifndef SOLVER
#define SOLVER

#include <map>
#include <memory>
#include "Mesher.hpp"
#include "materials/IsotropicMaterial.hpp"
#include "constraints/PointConstraint.hpp"

class Solver {
    public:
        explicit Solver(Mesher mesher);

        void assign_material_to_mesh(std::shared_ptr<Mesh> meshSharedPtr, IsotropicMaterial& material);
        IsotropicMaterial get_mesh_material(std::shared_ptr<Mesh> meshSharedPtr);

        void add_constraint_to_mesh(std::shared_ptr<Mesh> mesh, const PointConstraint& constraint);
        std::vector<std::shared_ptr<PointConstraint>> get_mesh_constraints(std::shared_ptr<Mesh> meshSharedPtr);

        // virtual void solve() = 0;

    protected:
        std::map<std::shared_ptr<Mesh>, std::optional<IsotropicMaterial>> meshMaterials;
        std::map<std::shared_ptr<Mesh>, std::vector<std::shared_ptr<PointConstraint>>> meshConstraints;
};

#endif