#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setMinimumHeight(700);
    w.setMinimumWidth(1200);
    w.show();

    return a.exec();
}
