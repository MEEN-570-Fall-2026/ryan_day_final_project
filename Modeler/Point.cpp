#include "Point.hpp"
#include <tuple>
#include <stdexcept>

Point::Point(double x, double y, double z): x_coordinate{x}, y_coordinate{y}, z_coordinate{z}
{
}

Point::Point()
{
}

double Point::x() const
{
    return x_coordinate;
}

double Point::y() const
{
    return y_coordinate;
}

double Point::z() const
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

RuntimeValue Point::invoke(const std::string& method, const std::vector<RuntimeValue>& args)
{
    if (args.size() > 0)
    {
        throw std::runtime_error("Point methods do not accept arguments!");
    }
    if (method == "x")
    {
        return RuntimeValue{x()};
    }
    else if (method == "y")
    {
        return RuntimeValue{y()};
    }
    else if (method == "z")
    {
        return RuntimeValue{z()};
    }
    throw std::runtime_error("Unknown method " + method + " on point!");
}
