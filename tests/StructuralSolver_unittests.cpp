#include "gtest/gtest.h"
#include <memory>
#include "materials/IsotropicMaterial.hpp"
#include "Mesher.hpp"
#include "Mesh.cpp"
#include "StructuralSolver.hpp"
#include "primitives3d/Cube.hpp"
#include "UnassignedMaterialException.hpp"
#include "constraints/structural/StructuralPointConstraint.hpp"


std::shared_ptr<Mesh> load_unit_cube_mesh_into_mesher(Mesher& mesher, double elementX, double elementY, double elementZ)
{
    Cube cube{1, 1, 1};
    return mesher.create_mesh(cube, elementX, elementY, elementZ);
}


TEST(StructuralSolver, GivenAMesh_WhenCreatingAnIsotropicMaterial_ExpectMaterialAppliedToMesh) 
{
    double poissons = 0.25;
    double modulus = 5000;

    IsotropicMaterial material;
    material.set_poissons_ratio(poissons);
    material.set_modulus_of_elasticity(modulus);

    Mesher mesher;
    std::shared_ptr<Mesh> mesh = load_unit_cube_mesh_into_mesher(mesher, 1, 1, 1);

    StructuralSolver solver{mesher};

    solver.assign_material_to_mesh(mesh, material);
    IsotropicMaterial retrievedMaterial = solver.get_mesh_material(mesh);

    ASSERT_EQ(poissons, retrievedMaterial.get_poissons_ratio());
    ASSERT_EQ(modulus, retrievedMaterial.get_modulus_of_elasticity());
}

TEST(StructuralSolver, GivenAMesh_WhenNoMaterialAssinged_ExpectGettingMaterialThrowsUnassignedMaterialException)
{
    Mesher mesher;
    std::shared_ptr<Mesh> mesh = load_unit_cube_mesh_into_mesher(mesher, 1, 1, 1);

    StructuralSolver solver{mesher};

    ASSERT_THROW(solver.get_mesh_material(mesh), UnassignedMaterialException);
}

TEST(StructuralSolver, GivenAMesh_WhenAssigningConstraint_ExpectConstraintCorrectlyApplied)
{
    Mesher mesher;
    std::shared_ptr<Mesh> mesh = load_unit_cube_mesh_into_mesher(mesher, 1, 1, 1);

    StructuralSolver solver{mesher};

    Point constraintPoint{-0.5, -0.5, -0.5};

    StructuralPointConstraint constraint{constraintPoint, 0, 0, 0};
    solver.add_constraint(constraint);
    std::vector<Constraint> constraints = solver.get_constraints();

    ASSERT_EQ(constraints.size(), 1);
    ASSERT_EQ(constraints[0].get_constraint_location(), constraintPoint);
    ASSERT_EQ(constraints[0].get_x_displacement(), 0);
    ASSERT_EQ(constraints[0].get_y_displacement(), 0);
    ASSERT_EQ(constraints[0].get_z_displacement(), 0);
}