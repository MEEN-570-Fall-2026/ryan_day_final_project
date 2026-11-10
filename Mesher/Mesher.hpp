#ifndef MESHER
#define MESHER

#include "primitives3d/Object3d.hpp"
#include "Mesh.hpp"
#include <vector>
#include "RuntimeValue.hpp"

class Mesher {
    using MeshPointer = std::unique_ptr<Mesh>;

    public:
        Mesher() = default;
        Mesh& create_mesh(Object3d& geometry, double elementSizeX, double elementSizeY, double elementSizeZ);
        RuntimeValue invoke(const std::string& method, const std::vector<RuntimeValue>& args);

    private:
        std::vector<MeshPointer> meshes;

};


#endif