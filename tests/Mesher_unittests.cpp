#include "gtest/gtest.h"
#include "primitives3d/Cube.hpp"
#include "Mesher.hpp"
#include "Point.hpp"
#include "Tetrahedron.hpp"
#include <memory>


bool tet_vertex_links_to_other_vertices(Tetrahedron& tet, std::vector<std::shared_ptr<Point>>& vertices, int vertex_index)
{
    std::vector<std::shared_ptr<Point>> vertexConnections = tet.get_vertex_connections(vertex_index);
    for (int i = 0; i < vertices.size(); i++)
    {
        if (i == vertex_index)
        {
            continue;
        }
        bool containsVertex = false;
        for (auto vertexConnection : vertexConnections)
        {
            if (vertexConnection == vertices[i])
            {
                containsVertex = true;
                break;
            }
        }
        if (containsVertex == false)
        {
            return false;
        }
    }
    return true;
}


TEST(Mesher, GivenFourPoints_WhenCreatingTetrahedron_ExpectPointsLinkedCorrectly)
{
    std::vector<std::shared_ptr<Point>> vertices = {
        std::make_shared<Point>(Point{0, 0, 0}),
        std::make_shared<Point>(Point{1, 0, 0}),
        std::make_shared<Point>(Point{1, 1, 0}),
        std::make_shared<Point>(Point{1, 1, 1})
    };
    Tetrahedron tet{vertices};
    for (int i = 0; i < vertices.size(); i++)
    {
        ASSERT_TRUE(tet_vertex_links_to_other_vertices(tet, vertices, i));
    }
}

// TEST(Mesher, GivenASingleElementMeshGrid_WhenCreatingTetsInGrid_ExpectSixTetsCreated)
// {
//     Cube cube{1.0, 1.0, 1.0};
//     Mesher mesher;
//     Mesh mesh = mesher.create_mesh(cube, 1, 1, 1);

//     EXPECT_EQ(mesh.nodes.size(), 8);
//     EXPECT_EQ(mesh.tetrahedra.size(), 6);
// }