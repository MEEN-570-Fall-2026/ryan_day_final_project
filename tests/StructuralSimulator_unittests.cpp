#include "gtest/gtest.h"
#include "IsotropicMaterial.hpp"
#include "Mesher.hpp"
#include "Mesh.cpp"
#include "primitives3d/Cube.hpp"


Mesh load_unit_cube_mesh_into_mesher(Mesher& mesher, double elementX, double elementY, double elementZ)
{
    Cube cube{1, 1, 1};
    return mesher.create_mesh(cube, elementX, elementY, elementZ);
}


TEST(StructuralSolver, GivenAMesh_WhenCreatingAMaterial_ExpectMaterialAppliedToMesh) 
{
    double poissons = 0.25;
    double modulus = 5000;

    IsotropicMaterial material;
    material.set_poissons_ratio(poissons);
    material.set_modulus_of_elasticity(modulus);

    Mesher mesher;
    Mesh mesh = load_unit_cube_mesh_into_mesher(mesher, 1, 1, 1);

    Solver solver{mesher};

    solver.assign_material_to_mesh(mesh, material);
    retrievedMaterial = retrieved_properties = solver.get_mesh_material_properties(mesh);

    ASSERT_EQ(poissons, retrievedMaterial.get_poissons_ratio());
    ASSERT_EQ(modulus, retrievedMaterial.get_modulus_of_elasticity());
}