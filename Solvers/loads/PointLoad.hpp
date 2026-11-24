#ifndef POINTLOAD
#define POINTLOAD

#include "Point.hpp"
#include <vector>

class PointLoad {
    public:
        PointLoad(Point point, double xLoad, double yLoad, double zLoad);

        const Point get_load_location() const;
        std::vector<double> get_load_vector();

    private:
        Point loadLocation;
        std::vector<double> loadVector;

};

#endif