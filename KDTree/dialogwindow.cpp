#include "dialogwindow.h"
#include "ui_dialogwindow.h"

DialogWindow::DialogWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogWindow)
{
    ui->setupUi(this);
}

DialogWindow::~DialogWindow()
{
    delete ui;
}

void DialogWindow::on_enterButton_clicked()
{
    QString filename = ui->input->text();
    emit filename_signal(filename);
    close();
}
