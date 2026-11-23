#include "gtest/gtest.h"
#include <memory>
#include "IsotropicMaterial.hpp"
#include "Mesher.hpp"
#include "Mesh.cpp"
#include "StructuralSimulator.hpp"
#include "primitives3d/Cube.hpp"


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

    StructuralSimulator solver{mesher};

    solver.assign_material_to_mesh(mesh, material);
    IsotropicMaterial retrievedMaterial = solver.get_mesh_material(mesh);

    ASSERT_EQ(poissons, retrievedMaterial.get_poissons_ratio());
    ASSERT_EQ(modulus, retrievedMaterial.get_modulus_of_elasticity());
}