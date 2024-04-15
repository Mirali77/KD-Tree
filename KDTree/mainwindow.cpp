#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <string>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wnd = new GLWindow();
    wnd->resize(900, 900);
    connect(this, &MainWindow::change_type, wnd, &GLWindow::change_type);
    connect(wnd, &GLWindow::change_number_of_points, this, &MainWindow::number_of_points_changed);
    connect(wnd, &GLWindow::change_region_number_of_points, this, &MainWindow::region_number_of_points_changed);
    connect(wnd, &GLWindow::change_number_of_visited_nodes, this, &MainWindow::number_of_visited_nodes_changed);
    connect(wnd, &GLWindow::change_number_of_included_nodes, this, &MainWindow::number_of_included_nodes_changed);
    connect(this, &MainWindow::change_ev_type, wnd, &GLWindow::change_ev_type);
    connect(wnd, &GLWindow::change_expected_value, this, &MainWindow::expected_value_changed);
    wnd->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_first_type_button_clicked()
{
    emit change_type(0);
}

void MainWindow::on_second_type_button_clicked()
{
    emit change_type(1);
}

void MainWindow::on_third_type_button_clicked()
{
    emit change_type(2);
}

void MainWindow::number_of_points_changed(int cnt) {
    ui->number_of_points_label2->setText(QString::number(cnt));
}

void MainWindow::on_clearButton_clicked()
{
    wnd->flush();
}

void MainWindow::region_number_of_points_changed(int cnt) {
    ui->region_number_of_points_label2->setText(cnt == -1 ? "" : QString::number(cnt));
}

void MainWindow::number_of_visited_nodes_changed(int cnt) {
    ui->nodes_visited_label2->setText(cnt == -1 ? "" : QString::number(cnt));
}

void MainWindow::number_of_included_nodes_changed(int cnt) {
    ui->nodes_included_label2->setText(cnt == -1 ? "" : QString::number(cnt));
}

void MainWindow::on_points_from_file_button_clicked()
{
    dial_wnd = new DialogWindow();
    connect(dial_wnd, &DialogWindow::filename_signal, this, &MainWindow::filename_entered);
    dial_wnd->show();
}

void MainWindow::filename_entered(QString filename) {
    string s = filename.toStdString();
    ifstream fin(filename.toStdString());
    int n;
    fin >> n;
    vector<Point> pnts;
    for(int i = 1; i <= n; i++) {
        double x, y;
        fin >> x >> y;
        pnts.push_back(Point(x, y));
    }
    wnd->add_points(pnts);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    emit change_ev_type();
}

void MainWindow::expected_value_changed(long double value) {
    ui->expected_value_label2->setText(value == -1 ? "" : QString::number(value, 'f'));
}
void MainWindow::on_guideButton_clicked()
{
    QMessageBox::information(this, "Guide", "*В режиме добавления точек вы можете добавлять точки кликом на полотно.\n*В режиме поиска соседа вы можете указать точку на полотне, для которого нужно найти соседа.\n*Вы можете включить подсчёт матожидания количества посещённых узлов при поиске соседа, однако он трудоёмкий (O(n^2), где n - количество точек на полотне).\n*В режиме обследования региона вы можете отметить 2 точки, которые будут образовывать регион, количество точек в котором нужно посчитать.\n*При обследовании региона, синим цветом будут отмечаться bounding-box-ы узлов KD-дерева, полностью вошедших в регион.\n*При добавлении точек из файла, файл должен быть txt формата.\n*Формат ввода в файле: в первой строке количество точек, далее в каждой отдельной строке координаты очередной точки x и y через пробел.");
}
