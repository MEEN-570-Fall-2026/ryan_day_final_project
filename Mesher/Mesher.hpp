#ifndef MESHER
#define MESHER

#include "primitives3d/Object3d.hpp"
#include "Mesh.hpp"
#include <vector>

class Mesher {
    using MeshPointer = std::unique_ptr<Mesh>;

    public:
        Mesher() = default;
        Mesh& create_mesh(Object3d& geometry, int element_length, int element_width, int element_height);

    private:
        std::vector<MeshPointer> meshes;

};


#endif