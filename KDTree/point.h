#ifndef POINT_H
#define POINT_H

using namespace std;
#include <cmath>
#include <algorithm>
#include <QPoint>

const double dinf = 1e15;

struct Point
{
    Point();
    Point(double x, double y);
    Point(QPoint p);
    double x, y;

};

double pdistance(Point p1, Point p2);

#endif // POINT_H
