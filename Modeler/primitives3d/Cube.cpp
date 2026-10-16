#include "Cube.hpp"

Cube::Cube(double x_length, double y_length, double z_length): 
    x_length{x_length}, 
    y_length{y_length}, 
    z_length{z_length}
{
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
                vertices.insert(
                    Point(
                        x_length / 2 * i,
                        y_length / 2 * j,
                        z_length / 2 * k
                    )
                );
            };
        }
    }
}
