#include "gtest/gtest.h"
#include "primitives3d/Cube.hpp"
#include "Mesher.hpp"

TEST(Mesher, GivenASingleElementMeshGrid_WhenCreatingTetsInGrid_ExpectSixTetsCreated)
{
    Cube cube{1.0, 1.0, 1.0};
    Mesher mesher;
    Mesh mesh = mesher.create_mesh(cube, 1, 1, 1);

    EXPECT_EQ(mesh.nodes.size(), 8);
    EXPECT_EQ(mesh.tetrahedra.size(), 6);
}