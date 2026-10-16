#ifndef POINT
#define POINT


class Point
{
public:
    Point(double x, double y, double z);
    Point();

    double x();
    double y();
    double z();

    bool operator<(const Point& other) const;

private:
    double x_coordinate{0};
    double y_coordinate{0};
    double z_coordinate{0};
};

#endif