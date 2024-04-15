#ifndef DIALOGWINDOW_H
#define DIALOGWINDOW_H

#include <QWidget>

namespace Ui {
class DialogWindow;
}

class DialogWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DialogWindow(QWidget *parent = nullptr);
    ~DialogWindow();

signals:
    void filename_signal(QString filename);

private slots:
    void on_enterButton_clicked();

private:
    Ui::DialogWindow *ui;
};

#endif // DIALOGWINDOW_H
