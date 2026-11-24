#ifndef STRUCTURALPOINTCONSTRAINT
#define STRUCTURALPOINTCONSTRAINT

#include "constraints/PointConstraint.hpp"
#include <optional>

class StructuralPointConstraint : public PointConstraint {
    public:
        StructuralPointConstraint(Point point, std::optional<double> xDisplacement, std::optional<double> yDisplacement, std::optional<double> zDisplacement);
        
        double get_x_displacement() const;
        double get_y_displacement() const;
        double get_z_displacement() const;

    private:
        std::optional<double> xDisplacement;
        std::optional<double> yDisplacement;
        std::optional<double> zDisplacement;

        std::unique_ptr<PointConstraint> clone() const;
        
};

#endif