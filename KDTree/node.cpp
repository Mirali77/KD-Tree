#include "node.h"

Node::Node()
{
    mn_x = mn_y = dinf;
    mx_x = mx_y = -dinf;
    cnt = 0, l = -1, r = -1;
}

void Node::upd(Point p) {
    mn_x = min(mn_x, p.x);
    mn_y = min(mn_y, p.y);
    mx_x = max(mx_x, p.x);
    mx_y = max(mx_y, p.y);
    cnt++;
}

bool Node::is_in(Node nd) {
    return nd.mn_x <= mn_x && nd.mx_x >= mx_x &&
            nd.mn_y <= mn_y && nd.mx_y >= mx_y;
}

bool Node::no_intersection(Node nd) {
    return nd.mx_x < mn_x || nd.mn_x > mx_x ||
            nd.mx_y < mn_y || nd.mn_y > mx_y;
}

double Node::distance(Point p) {
    bool f1 = p.x >= mn_x && p.x <= mx_x, f2 = p.y >= mn_y && p.y <= mx_y;
    if (f1 && f2) return (double)0;
    Point p1(mn_x, mn_y), p2(mn_x, mx_y), p3(mx_x, mn_y), p4(mx_x, mx_y);
    double res = min({pdistance(p, p1), pdistance(p, p2), pdistance(p, p3), pdistance(p, p4)});
    if (f1) res = min({res, abs(p.y - mn_y), abs(p.y - mx_y)});
    if (f2) res = min({res, abs(p.x - mn_x), abs(p.x - mx_x)});
    return res;
}

void Node::set_left(int ind) {
    l = ind;
}

void Node::set_right(int ind) {
    r = ind;
}
