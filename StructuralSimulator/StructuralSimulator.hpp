#ifndef STRUCTURALSIMULATOR
#define STRUCTURALSIMULATOR

#include "Mesher.hpp"
#include "Mesh.hpp"
#include "IsotropicMaterial.hpp"
#include <map>
#include <optional>
#include <memory>

class StructuralSimulator {
    public:
        StructuralSimulator(Mesher mesher);

        void assign_material_to_mesh(std::shared_ptr<Mesh> meshSharedPtr, IsotropicMaterial& material);
        IsotropicMaterial get_mesh_material(std::shared_ptr<Mesh> meshSharedPtr);

    private:
        std::map<std::shared_ptr<Mesh>, std::optional<IsotropicMaterial>> meshMaterials;


};

#endif