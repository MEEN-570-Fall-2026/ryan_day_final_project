#include "loads/PointLoad.hpp"

PointLoad::PointLoad(Point point, double xLoad, double yLoad, double zLoad) : 
    loadLocation{point},
    loadVector{xLoad, yLoad, zLoad}
{
}

const Point PointLoad::get_load_location() const
{
    return loadLocation;
}

std::vector<double> PointLoad::get_load_vector()
{
    return loadVector;
}
