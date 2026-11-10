#include "gtest/gtest.h"
#include "primitives3d/Cube.hpp"
#include "Mesher.hpp"
#include "Point.hpp"
#include "Tetrahedron.hpp"
#include "TetrahedraCube.hpp"
#include <unordered_set>
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


bool tet_vertices_match_expected_vertex_indices(std::vector<std::shared_ptr<Point>>& vertices, std::unordered_set<int> tetVertexIndices, std::vector<Tetrahedron> tetrahedra)
{
    for (Tetrahedron tet : tetrahedra)
    {
        bool equalVertices = true;
        for (auto tetVertexPointer : tet.get_vertices())
        {
            bool vertexFound = false;
            for (int index : tetVertexIndices)
            {
                if (tetVertexPointer == vertices[index])
                {
                    vertexFound = true;
                }
            }
            if (!vertexFound)
            {
                equalVertices = false;
            }
        }
        if (equalVertices)
        {
            return true;
        }
    }
    return false;
}


TEST(Mesher, GivenCubeVertices_WhenCreatingTetrahedraCube_ExpectSixTetrahedraCreatedCorrectly)
{
    std::vector<std::shared_ptr<Point>> vertices = {
        std::make_shared<Point>(Point{0, 0, 0}),
        std::make_shared<Point>(Point{1, 0, 0}),
        std::make_shared<Point>(Point{0, 1, 0}),
        std::make_shared<Point>(Point{1, 1, 0}),
        std::make_shared<Point>(Point{0, 0, 1}),
        std::make_shared<Point>(Point{1, 0, 1}),
        std::make_shared<Point>(Point{0, 1, 1}),
        std::make_shared<Point>(Point{1, 1, 1})
    };
    std::vector<std::unordered_set<int>> expectedTetsVertexIndices {
        {0, 1, 3, 7},
        {0, 1, 5, 7},
        {0, 2, 3, 7},
        {0, 2, 6, 7},
        {0, 4, 5, 7},
        {0, 4, 6, 7}
    };
    TetrahedraCube tetCube{vertices};
    std::vector<Tetrahedron> tetrahedra = tetCube.get_tetrahedra();
    for (auto tetVertexIndices : expectedTetsVertexIndices)
    {
        ASSERT_TRUE(tet_vertices_match_expected_vertex_indices(vertices, tetVertexIndices, tetrahedra));
    }
}


TEST(Mesher, GivenRectangularCubeVertices_WhenCreatingTetrahedraCube_ExpectSixTetrahedraCreatedCorrectly)
{
    std::vector<std::shared_ptr<Point>> vertices = {
        std::make_shared<Point>(Point{0, 0, 0}),
        std::make_shared<Point>(Point{2.2, 0, 0}),
        std::make_shared<Point>(Point{0, 7.8, 0}),
        std::make_shared<Point>(Point{2.2, 7.8, 0}),
        std::make_shared<Point>(Point{0, 0, 10}),
        std::make_shared<Point>(Point{2.2, 0, 10}),
        std::make_shared<Point>(Point{0, 7.8, 10}),
        std::make_shared<Point>(Point{2.2, 7.8, 10})
    };
    std::vector<std::unordered_set<int>> expectedTetsVertexIndices {
        {0, 1, 3, 7},
        {0, 1, 5, 7},
        {0, 2, 3, 7},
        {0, 2, 6, 7},
        {0, 4, 5, 7},
        {0, 4, 6, 7}
    };
    TetrahedraCube tetCube{vertices};
    std::vector<Tetrahedron> tetrahedra = tetCube.get_tetrahedra();
    for (auto tetVertexIndices : expectedTetsVertexIndices)
    {
        ASSERT_TRUE(tet_vertices_match_expected_vertex_indices(vertices, tetVertexIndices, tetrahedra));
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