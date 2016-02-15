#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QComboBox>
#include <QFileDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QSpinBox>
#include <QString>
#include <QTextCharFormat>
#include <QtGui>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
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

public slots:
    void on_actionOpen_File_triggered();

};

#endif // MAINWINDOW_H
