#ifndef MESHER
#define MESHER

#include "primitives3d/Object3d.hpp"
#include "Mesh.hpp"
#include <vector>

class Mesher {
    using MeshPointer = std::unique_ptr<Mesh>;

    public:
        Mesher() = default;
        Mesh& create_mesh(Object3d& geometry, double elementSizeX, double elementSizeY, double elementSizeZ);

    private:
        std::vector<MeshPointer> meshes;

};


#endif