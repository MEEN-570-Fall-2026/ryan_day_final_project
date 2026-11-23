#ifndef MESHER
#define MESHER

#include "primitives3d/Object3d.hpp"
#include "Mesh.hpp"
#include <vector>
#include "RuntimeValue.hpp"

class Mesher {
    using MeshPointer = std::shared_ptr<Mesh>;

    public:
        Mesher() = default;
        std::shared_ptr<Mesh> create_mesh(Object3d& geometry, double elementSizeX, double elementSizeY, double elementSizeZ);
        RuntimeValue invoke(const std::string& method, const std::vector<RuntimeValue>& args);
        const std::vector<MeshPointer>& get_meshes() const;

    private:
        std::vector<MeshPointer> meshes;

};


#endif