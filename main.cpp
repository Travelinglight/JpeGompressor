#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumHeight(740);
    w.setMinimumWidth(1400);
    w.show();

    return a.exec();
}
