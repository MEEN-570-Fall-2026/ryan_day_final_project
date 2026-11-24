#include "PointConstraint.hpp"

PointConstraint::PointConstraint(Point point) : constraintLocation{point}
{
}

const Point PointConstraint::get_constraint_location() const
{
    return constraintLocation;
}
