#include "Cube.hpp"

Cube::Cube(double xLength, double yLength, double zLength): 
    xLength{xLength}, 
    yLength{yLength}, 
    zLength{zLength}
{
    set_vertices();
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
                double xOffset = centroid.x() + xLength / 2 * i;
                double yOffset = centroid.y() + yLength / 2 * j;
                double zOffset = centroid.z() + zLength / 2 * k;
                vertices.insert(Point(xOffset, yOffset, zOffset));
            };
        }
    }
}
