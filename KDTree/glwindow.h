#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>
#include <QMouseEvent>
#include <kdtree.h>

namespace Ui {
struct GLWindow;
}

struct GLWindow : public QGLWidget
{
    Q_OBJECT
public:
    GLWindow(QWidget* parent = nullptr);
    virtual ~GLWindow();
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent*);
    int type = 0, ev_type = 0;
    vector<Point> pnts;
    KdTree Tr;
    void rebuild();
    void flush();
    void flush_values();
    void add_point(Point p);
    void add_points(vector<Point> pnts);
    QPoint mpos1, mpos2;
    float scale_factor_x, scale_factor_y;
public slots:
    void change_type(int t);
    void change_ev_type();
signals:
    void change_number_of_points(int cnt);
    void change_region_number_of_points(int cnt);
    void change_number_of_visited_nodes(int cnt);
    void change_number_of_included_nodes(int cnt);
    void change_expected_value(long double value);
private:
    Ui::GLWindow *ui;
};


#endif // GLWINDOW_H
