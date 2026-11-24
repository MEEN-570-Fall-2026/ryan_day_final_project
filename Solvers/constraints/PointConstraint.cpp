#include "PointConstraint.hpp"

PointConstraint::PointConstraint(Point point) : constraintLocation{std::make_shared<Point>(point)}
{
}

const Point PointConstraint::get_constraint_location() const
{
    return *constraintLocation;
}

void PointConstraint::update_location(std::shared_ptr<Point> newLocation)
{
    constraintLocation = newLocation;
}
