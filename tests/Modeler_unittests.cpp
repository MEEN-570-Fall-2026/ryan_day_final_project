#include "gtest/gtest.h"
#include "Point.hpp"
#include "primitives3d/Cube.hpp"
#include <stdexcept>
#include <set>


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

    std::set<Point> expectedVertices = {
        Point(-1, -1.5, -2),
        Point(-1, 1.5, -2),
        Point(-1, 1.5, 2),
        Point(-1, -1.5, 2),
        Point(1, -1.5, -2),
        Point(1, 1.5, -2),
        Point(1, 1.5, 2),
        Point(1, -1.5, 2),
    };

    for (Point point : expectedVertices)
    {
        ASSERT_TRUE(cube.get_vertices().contains(point));
    }
}

TEST(Cube, GivenOriginPointAndXYZLengths_WhenCreatingCube_ExpectVerticesInCorrectLocation)
{
    Point centroid{1, 1, 1};
    double xLength{2};
    double yLength{3};
    double zLength{4};
    Cube cube{centroid, xLength, yLength, zLength};

    std::set<Point> expectedVertices = {
        Point(0, -0.5, -1),
        Point(0, 2.5, -1),
        Point(0, 2.5, 3),
        Point(0, -0.5, 3),
        Point(2, -0.5, -1),
        Point(2, 2.5, -1),
        Point(2, 2.5, 3),
        Point(2, -0.5, 3),
    };

    for (Point point : expectedVertices)
    {
        ASSERT_TRUE(cube.get_vertices().contains(point));
    }
}