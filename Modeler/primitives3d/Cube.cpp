#include "Cube.hpp"

Cube::Cube(double xLength, double yLength, double zLength): 
    xLength{xLength}, 
    yLength{yLength}, 
    zLength{zLength}
{
    set_vertices();
    Cube::surfaceTriangleIndices = {
        {0, 2, 6}, {0, 6, 4},
        {1, 5, 7}, {1, 7, 3},
        {0, 1, 5}, {0, 5, 4},
        {2, 3, 7}, {2, 7, 6},
        {0, 3, 2}, {0, 1, 3},
        {4, 6, 7}, {4, 7, 5}
    };
}

Cube::Cube(Point centroidLocation, double xLength, double yLength, double zLength) :
    xLength{xLength}, 
    yLength{yLength}, 
    zLength{zLength}
{
    centroid = centroidLocation;
    set_vertices();
}

void Cube::set_vertices()
{
    for (int i = -1; i <= 1; i += 2)
    {
        for (int j = -1; j <= 1; j += 2)
        {
            for (int k = -1; k <= 1; k += 2)
            {
                double xOffvector = centroid.x() + xLength / 2 * i;
                double yOffvector = centroid.y() + yLength / 2 * j;
                double zOffvector = centroid.z() + zLength / 2 * k;
                vertices.push_back(Point(xOffvector, yOffvector, zOffvector));
            };
        }
    }
}

