#include "gtest/gtest.h"
#include "Point.hpp"
#include "primitives3d/Cube.hpp"
#include <stdexcept>
#include <vector>
#include "primitives3d/Object3d.hpp"
#include <concepts>
#include <algorithm>


bool vectorContainsVertex(std::vector<Point> vertices, Point point)
{
    return std::find(vertices.begin(), vertices.end(), point) != vertices.end();
}


void assertContainsAllVertices(std::vector<Point>& expectedVertices, Object3d& object3d)
{
    for (Point point : expectedVertices)
    {
        ASSERT_TRUE(vectorContainsVertex(object3d.get_vertices(), point));
    }
}

TEST(Point, GivenXYZCoordiantes_WhenCreatingPoint_ExpectPointGivesCorrectXYZCoordinates)
{
    double x{1};
    double y{2};
    double z{3};
    Point point{x,y,z};

    ASSERT_EQ(point.x(), x);
    ASSERT_EQ(point.y(), y);
    ASSERT_EQ(point.z(), z);
}

TEST(Point, GivenNoCoordiantes_WhenCreatingPoint_ExpectInitializesAtOrigin)
{
    Point point;

    ASSERT_EQ(point.x(), 0);
    ASSERT_EQ(point.y(), 0);
    ASSERT_EQ(point.z(), 0);
}

TEST(Cube, GivenXYZLengths_WhenCreatingCube_ExpectVerticesInCorrectLocation)
{
    double xLength{2};
    double yLength{3};
    double zLength{4};
    Cube cube{xLength, yLength, zLength};

    std::vector<Point> expectedVertices = {
        Point(-1, -1.5, -2),
        Point(-1, 1.5, -2),
        Point(-1, 1.5, 2),
        Point(-1, -1.5, 2),
        Point(1, -1.5, -2),
        Point(1, 1.5, -2),
        Point(1, 1.5, 2),
        Point(1, -1.5, 2),
    };

    assertContainsAllVertices(expectedVertices, cube);
}

TEST(Cube, GivenOriginPointAndXYZLengths_WhenCreatingCube_ExpectVerticesInCorrectLocation)
{
    Point centroid{1, 1.5, 2};
    double xLength{2};
    double yLength{3};
    double zLength{4};
    Cube cube{centroid, xLength, yLength, zLength};

    std::vector<Point> expectedVertices = {
        Point(0, 0, 0),
        Point(0, 3, 0),
        Point(0, 3, 4),
        Point(0, 0, 4),
        Point(2, 0, 0),
        Point(2, 3, 0),
        Point(2, 3, 4),
        Point(2, 0, 4),
    };

    assertContainsAllVertices(expectedVertices, cube);
}

TEST(Primative3D, GivenA3DPrimative_WhenTranslating_Expect_VerticesAndCentroidTranslateCorrectly)
{
    double xLength{2};
    double yLength{3};
    double zLength{4};
    Cube cube{xLength, yLength, zLength};

    cube.translate(1, 1.5, 2);

    std::vector<Point> expectedVertices = {
        Point(0, 0, 0),
        Point(0, 3, 0),
        Point(0, 3, 4),
        Point(0, 0, 4),
        Point(2, 0, 0),
        Point(2, 3, 0),
        Point(2, 3, 4),
        Point(2, 0, 4),
    };
    
    assertContainsAllVertices(expectedVertices, cube);
}

TEST(Primitive3D, GivenA3DPrimative_WhenGettingCentroid_ExpectCentriodInCorrectLocation)
{
    Cube cube(1, 1, 1);
    cube.translate(1, 1, 1);
    Point centroid = cube.get_centroid();

    Point expected = Point(1, 1, 1);

    ASSERT_EQ(centroid, expected);
}