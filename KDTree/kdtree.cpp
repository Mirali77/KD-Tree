#include "kdtree.h"

random_device rd;
mt19937 gen(rd());

KdTree::KdTree()
{
    depth = 0;
}

int KdTree::node_init() {
    tr.push_back(Node());
    return tr.size() - 1;
}

pair<vector<Point>, vector<Point>> KdTree::split(vector<Point> pnts, bool f) {
    auto calc_leq = [&](vector<Point>& pnts, vector<Point>& less, vector<Point>& eq, vector<Point>& greater, Point cp) {
        for(auto& p: pnts) {
            double pc = f ? p.x : p.y, hc = f ? cp.x : cp.y;
            if (pc < hc) less.push_back(p);
            else if (pc > hc) greater.push_back(p);
            else eq.push_back(p);
        }
    };
    function<Point(vector<Point>, int)> kth_ord_point = [&](vector<Point> pnts, int k) {
        int ind = gen() % pnts.size();
        vector<Point> less, eq, greater;
        calc_leq(pnts, less, eq, greater, pnts[ind]);
        int lsz = less.size(), esz = eq.size();
        if (lsz + esz < k) return kth_ord_point(greater, k - lsz - esz);
        if (lsz >= k) return kth_ord_point(less, k);
        return eq[0];
    };
    int nh = (pnts.size() + 1) / 2;
    Point median = kth_ord_point(pnts, nh);
    vector<Point> less, eq, greater;
    calc_leq(pnts, less, eq, greater, median);
    pair<vector<Point>, vector<Point>> res = {less, greater};
    for(auto& p: eq)
        if (res.first.size() < nh) res.first.push_back(p);
        else res.second.push_back(p);
    return res;
}

int KdTree::build(vector<Point> pnts, bool f, int d) {
    int node_num = node_init();
    depth = max(depth, d);
    for(auto& p: pnts) tr[node_num].upd(p);
    if (pnts.size() > 1) {
        pair<vector<Point>, vector<Point>> splitted_pnts = split(pnts, f);
        int l = build(splitted_pnts.first, !f, d + 1), r = build(splitted_pnts.second, !f, d + 1);
        tr[node_num].set_left(l);
        tr[node_num].set_right(r);
    }
    return node_num;
}

void KdTree::clear() {
    tr.clear();
    depth = 0;
}

pair<int, pair<vector<Node>, int>> KdTree::examine_region(Node nd) {
    pair<int, pair<vector<Node>, int>> res = {0, {vector<Node>(), 0}};
    res.first = examine_region(0, nd, res.second.first, res.second.second);
    return res;
}

pair<pair<Point, double>, int> KdTree::closest_neighbor(Point p) {
    Point resp(-dinf, -dinf); double dist = dinf; int nodes_visited = 0;
    closest_neighbor(0, resp, dist, p, nodes_visited);
    return {{resp, dist}, nodes_visited};
}

int KdTree::examine_region(int tnum, Node nd, vector<Node>& nodes_included, int& nodes_visited) {
    nodes_visited++;
    if (tr[tnum].is_in(nd)) {
        nodes_included.push_back(tr[tnum]);
        return tr[tnum].cnt;
    }
    if (tr[tnum].no_intersection(nd)) return 0;
    return examine_region(tr[tnum].l, nd, nodes_included, nodes_visited) +
            examine_region(tr[tnum].r, nd, nodes_included, nodes_visited);
}

void KdTree::closest_neighbor(int tnum, Point& best_neighbor, double& best_dist, Point p, int& nodes_visited) {
    nodes_visited++;
    double cand = tr[tnum].distance(p);
    if (cand >= best_dist) return;
    if (tr[tnum].cnt == 1) {
        best_neighbor = Point(tr[tnum].mn_x, tr[tnum].mn_y);
        best_dist = cand;
        return;
    }
    if (gen() & 1) {
        closest_neighbor(tr[tnum].l, best_neighbor, best_dist, p, nodes_visited);
        closest_neighbor(tr[tnum].r, best_neighbor, best_dist, p, nodes_visited);
    }
    else {
        closest_neighbor(tr[tnum].r, best_neighbor, best_dist, p, nodes_visited);
        closest_neighbor(tr[tnum].l, best_neighbor, best_dist, p, nodes_visited);
    }
}

int KdTree::get_depth() {
    return depth;
}

long double KdTree::calc_expected_value(Point p) {
    int n = tr.size();
    vector<vector<long double>> dp(n, vector<long double>(n + 1, -1));
    vector<int> mn(n);
    auto dist = [&](int j) {
        if (j == n) return dinf;
        return tr[j].distance(p);
    };
    for(int i = n - 1; i >= 0; i--) {
        if (tr[i].l == -1 && tr[i].r == -1) mn[i] = i;
        else if (tr[i].l == -1) mn[i] = mn[tr[i].r];
        else if (tr[i].r == -1) mn[i] = mn[tr[i].l];
        else if (dist(mn[tr[i].l]) < dist(mn[tr[i].r])) mn[i] = mn[tr[i].l];
        else mn[i] = mn[tr[i].r];
    }
    function<long double(int, int)> calc = [&](int i, int j) {
        if (dp[i][j] != -1) return dp[i][j];
        if (dist(i) >= dist(j) || tr[i].l == -1 && tr[i].r == -1) return dp[i][j] = 1;
        if (tr[i].l == -1) return dp[i][j] = calc(tr[i].r, j) + 1;
        if (tr[i].r == -1) return dp[i][j] = calc(tr[i].l, j) + 1;
        long double val1 = calc(tr[i].l, j), val2 = calc(tr[i].r, j);
        int mn1 = mn[tr[i].l], mn2 = mn[tr[i].r];
        int nj1 = j, nj2 = j;
        if (dist(mn1) < dist(nj1)) nj1 = mn1;
        if (dist(mn2) < dist(nj2)) nj2 = mn2;
        val1 += calc(tr[i].r, nj1);
        val2 += calc(tr[i].l, nj2);
        return dp[i][j] = (val1 + val2) / 2 + 1;
    };
    return calc(0, n);
}
