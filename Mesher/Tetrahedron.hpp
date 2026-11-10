#ifndef TETRAHEDRON
#define TETRAHEDRON

#include <vector>
#include <unordered_map>
#include <memory>
#include "Point.hpp"

class Tetrahedron
{
    using PointPtr = std::shared_ptr<Point>;

    public:
        Tetrahedron(std::vector<PointPtr> vertices);

    private:
        std::vector<PointPtr> vertices;
        void set_point_connections();
        std::unordered_map<int, std::vector<int>> pointConnections;

};

#endif