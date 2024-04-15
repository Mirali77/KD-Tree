#include "mainwindow.h"

#include <QApplication>
#include <kdtree.h>
#include <QDebug>
#include <fstream>
#include <iomanip>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// /home/mirali7/KDTree/randtest100.txt
// /home/mirali7/KDTree/randtest500.txt
// /home/mirali7/KDTree/randtest1000.txt
// /home/mirali7/KDTree/randtest5000.txt
// /home/mirali7/KDTree/randtest10000.txt
// /home/mirali7/KDTree/randtest100000.txt
// /home/mirali7/KDTree/badtest.txt

