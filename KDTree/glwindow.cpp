#include "glwindow.h"
#include "ui_glwindow.h"

GLWindow::GLWindow(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::GLWindow)
{
    ui->setupUi(this);
}

GLWindow::~GLWindow()
{
    delete ui;
}

void GLWindow::initializeGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 5000, 5000, 0, 0, 1);
}

void GLWindow::add_point(Point p) {
    pnts.push_back(p);
}

void GLWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    scale_factor_x = 5000 / (float)w;
    scale_factor_y = 5000 / (float)h;
}

void GLWindow::paintGL()
{
    glLineWidth(2.0);
    qglClearColor(Qt::white);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto draw_circle = [&](double x, double y, double rad, int N, bool filled = true) {
        double pi = acos(-1);
        glBegin(filled ? GL_POLYGON : GL_LINE_LOOP);
            for(int i = 0; i < N; i++ ) glVertex2d(rad * cos(2 * pi / N * i) + x, rad * sin(2 * pi / N * i) + y);
        glEnd();
    };

    qglColor(Qt::red);
    for(auto& p: pnts) draw_circle(p.x, p.y, 20, 100);

    if (type == 1 && !pnts.empty()) {
        qglColor(Qt::blue);
        draw_circle(mpos1.x(), mpos1.y(), 20, 100);
        pair<pair<Point, double>, int> neighbor = Tr.closest_neighbor(Point(mpos1));
        qglColor(QColor().fromRgb(0, 219, 0));
        draw_circle(neighbor.first.first.x, neighbor.first.first.y, 20, 100);
        draw_circle(mpos1.x(), mpos1.y(), neighbor.first.second, 1000, false);
        emit change_number_of_visited_nodes(neighbor.second);
        if (ev_type == 1) {
            long double ev = Tr.calc_expected_value(Point(mpos1));
            emit change_expected_value(ev);
        }
    }

    auto draw_node = [&](Node nd) {
        glBegin(GL_LINE_LOOP);
            glVertex2d(nd.mn_x, nd.mn_y);
            glVertex2d(nd.mn_x, nd.mx_y);
            glVertex2d(nd.mx_x, nd.mx_y);
            glVertex2d(nd.mx_x, nd.mn_y);
        glEnd();
    };

    if (type == 2 && mpos2.x() != -100 && !pnts.empty()) {
        Point p1(mpos1), p2(mpos2);
        Node nd; nd.upd(p1), nd.upd(p2);
        qglColor(QColor().fromRgb(204, 0, 204));
        draw_node(nd);
        pair<int, pair<vector<Node>, int>> res = Tr.examine_region(nd);
        emit change_region_number_of_points(res.first);
        emit change_number_of_visited_nodes(res.second.second);
        emit change_number_of_included_nodes(res.second.first.size());
        qglColor(Qt::blue);
        for(auto& inc_nd: res.second.first) draw_node(inc_nd);
    }

    if (type != 2 || mpos2.x() != -100)
        mpos1 = mpos2 = QPoint(-100, -100);
}

void GLWindow::rebuild() {
    Tr.clear();
    Tr.build(pnts);
    emit change_number_of_points(pnts.size());
}

void GLWindow::flush_values() {
    emit change_region_number_of_points(-1);
    emit change_number_of_visited_nodes(-1);
    emit change_number_of_included_nodes(-1);
    emit change_expected_value(-1);
}

void GLWindow::mousePressEvent(QMouseEvent* apEv) {
    flush_values();
    QPoint mpos = apEv->pos();
    mpos.setX(mpos.x() * scale_factor_x);
    mpos.setY(mpos.y() * scale_factor_y);
    if (type == 0) {
        add_point(Point(mpos));
        rebuild();
    }
    else if (type == 1) {
        mpos1 = mpos;
    }
    else if (type == 2) {
        if (mpos1.x() == -100) mpos1 = mpos;
        else mpos2 = mpos;
    }
    update();
}

void GLWindow::add_points(vector<Point> pnts) {
    for(auto& p: pnts) add_point(p);
    rebuild();
    update();
}

void GLWindow::change_type(int t) {
    type = t;
}

void GLWindow::flush() {
    pnts.clear();
    rebuild();
    flush_values();
    update();
}

void GLWindow::change_ev_type() {
    ev_type ^= 1;
}
