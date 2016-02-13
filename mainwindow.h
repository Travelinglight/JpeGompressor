#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QToolButton>
#include <QTextCharFormat>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "matrixDsp.h"
#include "imagesDsp.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *canvas;
    MatrixDsp *matrixDsp0;
    ImagesDsp *imagesDsp0;
    ImagesDsp *imagesDsp1;

//    QToolBar *toolBar;
};

#endif // MAINWINDOW_H
