#include "point.h"

Point::Point()
{
    x = -dinf, y = -dinf;
}

Point::Point(double x, double y): x(x), y(y) {}

Point::Point(QPoint p) {
    x = p.x(), y = p.y();
}

double pdistance(Point p1, Point p2) {
    double dx = p1.x - p2.x, dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}
