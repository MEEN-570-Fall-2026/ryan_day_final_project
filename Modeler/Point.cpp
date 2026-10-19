#include "Point.hpp"
#include <tuple>

Point::Point(double x, double y, double z): x_coordinate{x}, y_coordinate{y}, z_coordinate{z}
{
}

Point::Point()
{
}

double Point::x()
{
    return x_coordinate;
}

double Point::y()
{
    return y_coordinate;
}

double Point::z()
{
    return z_coordinate;
}

bool Point::operator<(const Point &other) const
{
    return std::tie(x_coordinate, y_coordinate, z_coordinate) 
    < 
    std::tie(other.x_coordinate, other.y_coordinate, other.z_coordinate);
}

bool Point::operator==(const Point &other) const
{
    return x_coordinate == other.x_coordinate && y_coordinate == other.y_coordinate && z_coordinate == other.z_coordinate;
}
