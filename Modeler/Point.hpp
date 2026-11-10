#ifndef POINTMODELER
#define POINTMODELER

#include "CADObject.hpp"
#include "RuntimeValue.hpp"

class Point : public CADObject
{
public:
    Point(double x, double y, double z);
    Point();

    double x() const;
    double y() const;
    double z() const;

    bool operator<(const Point& other) const;
    bool operator==(const Point& other) const;

    RuntimeValue invoke(const std::string& method, const std::vector<RuntimeValue>& args);

private:
    double x_coordinate{0};
    double y_coordinate{0};
    double z_coordinate{0};
};

#endif