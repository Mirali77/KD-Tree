#ifndef NODE_H
#define NODE_H

#include <point.h>

class Node
{
public:
    Node();
    void upd(Point p);
    void set_left(int ind);
    void set_right(int ind);
    bool is_in(Node nd);
    bool no_intersection(Node nd);
    double distance(Point p);
    double mn_x, mn_y, mx_x, mx_y;
    int cnt, l, r;
};

#endif // NODE_H
