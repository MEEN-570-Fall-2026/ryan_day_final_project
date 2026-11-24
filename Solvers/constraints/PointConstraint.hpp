#ifndef CONSTRAINT
#define CONSTRAINT

#include "Point.hpp"
#include <memory>

class PointConstraint {
    public:
        explicit PointConstraint(Point point);
        virtual ~PointConstraint() = default;

        const Point get_constraint_location() const;

        virtual std::unique_ptr<PointConstraint> clone() const = 0;

        void update_location(std::shared_ptr<Point> newLocation);

    private:
        std::shared_ptr<Point> constraintLocation;

        

};

#endif