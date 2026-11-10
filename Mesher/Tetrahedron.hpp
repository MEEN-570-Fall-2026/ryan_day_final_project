#ifndef TETRAHEDRON
#define TETRAHEDRON

#include <vector>
#include <unordered_map>
#include "Point.hpp"

class Tetrahedron
{
    public:
        Tetrahedron(std::vector<Point> vertices);

    private:
        std::vector<Point> vertices;
        void set_point_connections();
        std::unordered_map<int, std::vector<int>> pointConnections;

};

#endif