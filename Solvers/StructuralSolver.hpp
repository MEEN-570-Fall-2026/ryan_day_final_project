#ifndef STRUCTURALSOLVER
#define STRUCTURALSOLVER

#include "Solver.hpp"
#include "Mesher.hpp"
#include "loads/PointLoad.hpp"

class StructuralSolver : public Solver {
    public:
        StructuralSolver(Mesher mesher);

        void add_load_to_mesh(std::shared_ptr<Mesh> meshSharedPtr, PointLoad& load);
        std::vector<PointLoad> get_loads_from_mesh(std::shared_ptr<Mesh> meshSharedPtr);

    private:
        std::map<std::shared_ptr<Mesh>, std::vector<PointLoad>> meshLoads;


};

#endif