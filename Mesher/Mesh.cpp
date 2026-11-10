#include "Mesh.hpp"

Mesh::Mesh(std::vector<PointPointers> objectVertices, double elementXSize, double elementYSize, double elementZSize) :
    objectVertices{objectVertices},
    elementXSize{elementXSize},
    elementYSize{elementYSize},
    elementZSize{elementZSize}
{
    set_tet_cube_counts();
    create_point_cloud();
    create_tetrahedra_cubes();
}

std::vector<std::shared_ptr<TetrahedraCube>> Mesh::get_tetrahedra_cubes()
{
    return tetCubes;
}

void Mesh::set_tet_cube_counts()
{
    set_object_bounds();
    set_x_tet_cube_count();
    set_y_tet_cube_count();
    set_z_tet_cube_count();
}

void Mesh::set_object_bounds()
{
    Point* intitialVertex = objectVertices[0].get();
    objectMinX = intitialVertex->x();
    objectMaxX = intitialVertex->x();
    objectMinY = intitialVertex->y();
    objectMaxY = intitialVertex->y();
    objectMinZ = intitialVertex->z();
    objectMaxZ = intitialVertex->z();
    for (auto vertexPointer : objectVertices)
    {
        Point* currentVertex = vertexPointer.get();
        double x = currentVertex->x();
        double y = currentVertex->y();
        double z = currentVertex->z();
        if (x < objectMinX) {
            objectMinX = x;
        }
        else if (x > objectMaxX) {
            objectMaxX = x;
        }
        if (y < objectMinY) {
            objectMinY = y;
        }
        else if (y > objectMaxY) {
            objectMaxY = y;
        }
        if (z < objectMinZ) {
            objectMinZ = z;
        }
        else if (z > objectMaxZ) {
            objectMaxZ = z;
        }
    }
}

void Mesh::set_x_tet_cube_count()
{
    const double length = objectMaxX - objectMinX;
    xTetCubeCount = static_cast<int>(std::ceil(length / elementXSize));
    elementXSize = length / xTetCubeCount;
}

void Mesh::set_y_tet_cube_count()
{
    const double length = objectMaxY - objectMinY;
    yTetCubeCount = static_cast<int>(std::ceil(length / elementYSize));
    elementYSize = length / yTetCubeCount;
}

void Mesh::set_z_tet_cube_count()
{
    const double length = objectMaxZ - objectMinZ;
    zTetCubeCount = static_cast<int>(std::ceil(length / elementZSize));
    elementZSize = length / zTetCubeCount;
}

void Mesh::create_point_cloud()
{
    pointGrid.clear();
    pointGrid.reserve((xTetCubeCount + 1) * (yTetCubeCount + 1) * (zTetCubeCount + 1));
    for (int k = 0; k <= zTetCubeCount; ++k)
    {
        for (int j = 0; j <= yTetCubeCount; ++j)
        {
            for (int i = 0; i <= xTetCubeCount; ++i)
            {
                const double x = objectMinX + i * elementXSize;
                const double y = objectMinY + j * elementYSize;
                const double z = objectMinZ + k * elementZSize;
                pointGrid.push_back(std::make_shared<Point>(x, y, z));
            }
        }
    }
}

std::size_t Mesh::get_point_cloud_index(int i, int j, int k) const
{
    const std::size_t pointsX = xTetCubeCount + 1;
    const std::size_t pointsY = yTetCubeCount + 1;
    return i + pointsX * (j + pointsY * k);
}

void Mesh::create_tetrahedra_cubes()
{
    for (int k = 0; k < zTetCubeCount; ++k)
    {
        for (int j = 0; j < yTetCubeCount; ++j)
        {
            for (int i = 0; i < xTetCubeCount; ++i)
            {
                std::vector<PointPointers> corners{
                    pointGrid[get_point_cloud_index(i, j, k)],
                    pointGrid[get_point_cloud_index(i + 1, j, k)],
                    pointGrid[get_point_cloud_index(i, j + 1, k)],
                    pointGrid[get_point_cloud_index(i + 1, j + 1, k)],
                    pointGrid[get_point_cloud_index(i, j, k + 1)],
                    pointGrid[get_point_cloud_index(i + 1, j, k + 1)],
                    pointGrid[get_point_cloud_index(i, j + 1, k + 1)],
                    pointGrid[get_point_cloud_index(i + 1, j + 1, k + 1)]
                };

                tetCubes.push_back(
                    std::make_shared<TetrahedraCube>(std::move(corners)));
            }
        }
    }
}
