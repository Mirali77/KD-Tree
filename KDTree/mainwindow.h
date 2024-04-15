#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <glwindow.h>
#include <dialogwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_first_type_button_clicked();

    void on_second_type_button_clicked();

    void on_third_type_button_clicked();

    void number_of_points_changed(int cnt);

    void on_clearButton_clicked();

    void region_number_of_points_changed(int cnt);

    void number_of_visited_nodes_changed(int cnt);

    void number_of_included_nodes_changed(int cnt);

    void on_points_from_file_button_clicked();

    void filename_entered(QString filename);

    void on_checkBox_stateChanged(int arg1);

    void expected_value_changed(long double value);

    void on_guideButton_clicked();

signals:
    void change_type(int t);
    void change_ev_type();

private:
    Ui::MainWindow *ui;
    GLWindow* wnd;
    DialogWindow* dial_wnd;
};
#endif // MAINWINDOW_H
