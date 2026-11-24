#ifndef CONSTRAINT
#define CONSTRAINT

#include "Point.hpp"

class PointConstraint {
    public:
        explicit PointConstraint(Point point);
        virtual ~PointConstraint() = default;

        const Point get_constraint_location() const;

        virtual std::unique_ptr<PointConstraint> clone() const = 0;

    private:
        Point constraintLocation;

        

};

#endif