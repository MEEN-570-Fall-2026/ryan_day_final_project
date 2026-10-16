#include "gtest/gtest.h"
#include "Point.hpp"
#include <stdexcept>
#include <vector>
#include <string>


TEST(Point, GivenXYZCoordiantes_WhenCreatingPoint_ExpectPointGivesCorrectXYZCoordinates)
{
    int x{1};
    int y{2};
    int z{3};
    Point point{1,2,3};

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