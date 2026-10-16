#include "Point.hpp"

Point::Point(double x, double y, double z): x_coordinate{x}, y_coordinate{y}, z_coordinate{z}
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