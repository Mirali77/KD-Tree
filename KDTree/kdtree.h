#ifndef KDTREE_H
#define KDTREE_H

#include <vector>
#include <node.h>
#include <functional>
#include <random>

class KdTree
{
public:
    KdTree();
    int node_init();
    pair<vector<Point>, vector<Point>> split(vector<Point> pnts, bool type);
    int build(vector<Point> pnts, bool f = true, int d = 0);
    void clear();
    pair<int, pair<vector<Node>, int>> examine_region(Node nd);
    int examine_region(int tnum, Node nd, vector<Node>& nodes_included, int& nodes_visited);
    pair<pair<Point, double>, int> closest_neighbor(Point p);
    void closest_neighbor(int tnum, Point& best_neighbor, double& best_dist, Point p, int& nodes_visited);
    int get_depth();
    long double calc_expected_value(Point p);
private:
    vector<Node> tr;
    int depth;
};

#endif // KDTREE_H
