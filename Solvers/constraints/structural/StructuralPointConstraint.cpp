#include "StructuralPointConstraint.hpp"
#include "UnassignedConstraintException.hpp"

StructuralPointConstraint::StructuralPointConstraint(Point point, std::optional<double> xDisplacement, std::optional<double> yDisplacement, std::optional<double> zDisplacement) : 
    PointConstraint{point},
    xDisplacement{xDisplacement},
    yDisplacement{yDisplacement},
    zDisplacement{zDisplacement}
{
}

double StructuralPointConstraint::get_x_displacement() const
{
    if (!xDisplacement.has_value())
    {
        throw UnassignedConstraintException("No x displacement assigned for given constraint!");
    }
    return *xDisplacement;
}

double StructuralPointConstraint::get_y_displacement() const
{
    if (!yDisplacement.has_value())
    {
        throw UnassignedConstraintException("No y displacement assigned for given constraint!");
    }
    return *yDisplacement;
}

double StructuralPointConstraint::get_z_displacement() const
{
    if (!zDisplacement.has_value())
    {
        throw UnassignedConstraintException("No x displacement assigned for given constraint!");
    }
    return *zDisplacement;
}

std::unique_ptr<PointConstraint> StructuralPointConstraint::clone() const
{
    return std::make_unique<StructuralPointConstraint>(*this);
}
