#ifndef OBJECT3D
#define OBJECT3D

#include "Point.hpp"
#include <vector>
#include "SurfaceTriangle.hpp"
#include "CADObject.hpp"

class Object3d : public CADObject {
public:
    std::vector<Point> get_vertices();
    void translate(double xDistance, double yDistance, double zDistance);
    std::vector<SurfaceTriangle> getSurfaceTriangles();
    std::vector<std::array<int, 3>> getSurfaceTriangleIndices();
    Point get_centroid();

    virtual ~Object3d() = default;

    bool operator==(const Object3d& other) const;

    RuntimeValue invoke(const std::string& method, const std::vector<RuntimeValue>& args);

    
protected:
    Point centroid;
    std::vector<Point> vertices;
    std::vector<std::array<int, 3>> surfaceTriangleIndices;
    std::vector<SurfaceTriangle> surfaceTriangles;
    void set_surface_triangles();
    virtual void set_vertices() = 0;
    
};

#endif